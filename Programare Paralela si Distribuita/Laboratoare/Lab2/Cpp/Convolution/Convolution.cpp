#include <iostream>
#include <fstream>
#include <vector>
#include <thread>
#include <chrono>
#include "MyBarrier.h"
#include <queue>

#define N 10
#define M 10000
#define n 5
#define m 5

int matrix[N + 4][M + 4];
int kernel[n][m];
int finalMatrix[N][M];

int p;
MyBarrier barrier(p);

using namespace std;
using namespace std::chrono;

void read(string path, int matrix[][M + 4], int kernel[][m])
{
    ifstream file(path);

    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            file >> matrix[i][j];

    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            file >> kernel[i][j];

    file.close();
}

void write(string path, int finalMatrix[][M])
{
    ofstream file(path);

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
            file << finalMatrix[i][j] << " ";
        file << endl;
    }

    file.close();
}

void addBorder(int matrix[][M + 4], int lineOffset, int columnOffset)
{
    int aux[N + 4][M + 4];
    for (int i = 0; i < N + 2 * lineOffset; i++)
    {
        for (int j = 0; j < M + 2 * columnOffset; j++)
        {
            int a;
            if (i < lineOffset) 
                a = 0;
            else if (i >= N + lineOffset) 
                a = N - 1;
            else
                a = i - lineOffset;

            int b;
            if (j < columnOffset) b = 0;
            else if (j >= M + columnOffset) b = M - 1;
            else b = j - columnOffset;

            aux[i][j] = matrix[a][b];
        }
    }
    copy(&aux[0][0], &aux[0][0] + (N + 4) * (M + 4), &matrix[0][0]);
}

int singlePixelConvolution(int x, int y, int lineOffset, int columnOffset, int matrix[][M + 4], int kernel[][m], int previousLines[][M + 4], int currentLine[])
{
    int output = 0;

    for (int i = 0; i < lineOffset; i++)
    {
        for (int j = 0; j < m; j++)
        {
            int b = y - columnOffset + j;
            output += kernel[i][j] * previousLines[2 - lineOffset + i][b];
        }
    }
    for (int j = 0; j < m; j++)
    {
        int b = y - columnOffset + j;
        output += kernel[lineOffset][j] * currentLine[b];
    }
    for (int i = lineOffset + 1; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            int a = x - lineOffset + i;
            int b = y - columnOffset + j;
            output += kernel[i][j] * matrix[a][b];
        }
    }

    return output;
}

void computeMatrix_Line(int start, int end, int lineOffset, int columnOffset)
{
    int previousLines[2][M + 4], currentLine[M + 4];
    copy(&matrix[start - 1][0], &matrix[start - 1][0] + M + 4, &previousLines[1][0]);
    if (lineOffset > 1)
        copy(&matrix[start - 2][0], &matrix[start - 2][0] + M + 4, &previousLines[0][0]);

    queue<int> frontierValues;

    for (int i = start; i < end; i++)
    {
        copy(&matrix[i][0], &matrix[i][0] + M + 4, &currentLine[0]);
        for (int j = columnOffset; j < M + columnOffset; j++)
        {
            int output = singlePixelConvolution(i, j, lineOffset, columnOffset, matrix, kernel, previousLines, currentLine);
            if ((i - start < lineOffset) || (end - i <= lineOffset))
                frontierValues.push(output);
            else
                matrix[i][j] = output;
        }
        copy(&previousLines[1][0], &previousLines[1][0] + M + 4, &previousLines[0][0]);
        copy(&currentLine[0], &currentLine[0] + M + 4, &previousLines[1][0]);
    }

    barrier.wait();

    for (int i = start; i < end; i++)
    {
        for (int j = columnOffset; j < M + columnOffset; j++)
        {
            if ((i - start < lineOffset) || (end - i <= lineOffset))
            {
                matrix[i][j] = frontierValues.front();
                frontierValues.pop();
            }
        }
    }
}

void computeMatrix_Column(int start, int end, int lineOffset, int columnOffset)
{
    int previousLines[2][M + 4], currentLine[M + 4];
    copy(&matrix[lineOffset - 1][0], &matrix[lineOffset - 1][0] + M + 4, &previousLines[1][0]);
    if (lineOffset > 1)
        copy(&matrix[lineOffset - 2][0], &matrix[lineOffset - 2][0] + M + 4, &previousLines[0][0]);

    queue<int> frontierValues;

    for (int i = lineOffset; i < N + lineOffset; i++)
    {
        copy(&matrix[i][0], &matrix[i][0] + M + 4, &currentLine[0]);
        for (int j = start; j < end; j++)
        {
            int output = singlePixelConvolution(i, j, lineOffset, columnOffset, matrix, kernel, previousLines, currentLine);
            if ((j - start < columnOffset) || (end - j <= columnOffset))
                frontierValues.push(output);
            else
                matrix[i][j] = output;
        }
        copy(&previousLines[1][0], &previousLines[1][0] + M + 4, &previousLines[0][0]);
        copy(&currentLine[0], &currentLine[0] + M + 4, &previousLines[1][0]);
    }

    barrier.wait();

    for (int i = lineOffset; i < columnOffset; i++)
    {
        for (int j = start; j < end; j++)
        {
            if ((j - start < columnOffset) || (end - j <= columnOffset))
            {
                matrix[i][j] = frontierValues.front();
                frontierValues.pop();
            }
        }
    }
}

void paralelC(int lineOffset, int columnOffset, int start, int end)
{
    if (N > M)
        computeMatrix_Line(start, end, lineOffset, columnOffset);
    else
        computeMatrix_Column(start, end, lineOffset, columnOffset);
}

void paralelConvolution(int lineOffset, int columnOffset, int p)
{
    vector<thread> t;

    int start = lineOffset, end;
    int chunk = N / p;
    int rest = N % p;

    auto startTime = high_resolution_clock::now();

    for (auto i = 0; i < p; i++)
    {
        end = start + chunk + (rest-- > 0);
        if (rest > 0)
        {
            end++;
            rest--;
        }
        thread thr = thread(paralelC, lineOffset, columnOffset, start, end);
        t.push_back(move(thr));
        start = end;
    }

    for (auto& th : t)
    {
        if (th.joinable())
            th.join();
    }

    auto endTime = high_resolution_clock::now();

    double difference = duration<double, milli>(endTime - startTime).count();

    cout << difference << endl;
}

int main(int argc, char** argv)
{
    read("D:\\Facultate\\Anul3\\Sem1\\PPD\\Laboratoare\\Lab2\\Cpp\\Convolution\\Convolution\\data.txt", matrix, kernel);
    
    int lineOffset = (N - 1) / 2;
    int columnOffset = (M - 1) / 2;
    addBorder(matrix, lineOffset, columnOffset);

//    int p = atoi(argv[1]);
    int p = 1;

    paralelConvolution(lineOffset, columnOffset, p);

    write("D:\\Facultate\\Anul3\\Sem1\\PPD\\Laboratoare\\Lab2\\Cpp\\Convolution\\Convolution\\output.txt", finalMatrix);

    return 0;
}