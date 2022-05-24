#include <iostream>
#include <fstream>
#include <vector>
#include <thread>
#include <chrono>
#define N 10
#define M 10000
#define n 5
#define m 5

int matrix[N][M];
int kernel[n][m];
int finalMatrix[N][M];

using namespace std;
using namespace std::chrono;

void read(string path, int matrix[][M], int kernel[][m])
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

int singlePixelConvolution(int x, int y, int lineOffset, int columnOffset, int matrix[][M], int kernel[][m])
{
    int output = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            // Compute neighbours
            int ii = x - lineOffset + i;
            int jj = y - columnOffset + j;

            // Out of bounds - line:
            if (ii < 0) ii = 0;
            else if (ii >= N) ii = N - 1;
            // Out of bounds - column:
            if (jj < 0) jj = 0;
            else if (jj >= M) jj = M - 1;

            output += matrix[ii][jj] * kernel[i][j];
        }
    }
    return output;
}

void secventialConvolution(int lineOffset, int columnOffset)
{
    auto startTime = high_resolution_clock::now();

    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            finalMatrix[i][j] = singlePixelConvolution(i, j, lineOffset, columnOffset, matrix, kernel);

    auto endTime = high_resolution_clock::now();
    
    double difference = duration<double, milli>(endTime - startTime).count();

    cout << difference << endl;
}

void paralelC(int lineOffset, int columnOffset, int start, int end)
{
    if (N > M)
    {
        for (int i = start; i < end; i++)
            for (int j = 0; j < M; j++)
                finalMatrix[i][j] = singlePixelConvolution(i, j, lineOffset, columnOffset, matrix, kernel);
    }
    else
    {
        for (int i = 0; i < N; i++)
            for (int j = start; j < end; j++)
                finalMatrix[i][j] = singlePixelConvolution(i, j, lineOffset, columnOffset, matrix, kernel);
    }
}

void paralelConvolution(int lineOffset, int columnOffset, int p)
{
    vector<thread> t;

    int start = 0, end = 0;
    int chunk = N / p;
    int rest = N % p;
    
    auto startTime = high_resolution_clock::now();

    for (size_t i = 0; i < p; i++)
    {
    	start = end;
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
    read("D:\\Facultate\\Anul3\\Sem1\\PPD\\Laboratoare\\Lab1\\Convolution_Cpp\\Convolution\\Convolution\\data.txt", matrix, kernel);

    int lineOffset = (N - 1) / 2;
    int columnOffset = (M - 1) / 2;

    int p = atoi(argv[1]);
//    int p = 1;

    if (p == 1)
        secventialConvolution(lineOffset, columnOffset);
    else
        paralelConvolution(lineOffset, columnOffset, p);

    write("D:\\Facultate\\Anul3\\Sem1\\PPD\\Laboratoare\\Lab1\\Convolution_Cpp\\Convolution\\Convolution\\output.txt", finalMatrix);

    return 0;
}