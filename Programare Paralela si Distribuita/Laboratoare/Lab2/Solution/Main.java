package com.company;

import java.io.*;
import java.util.LinkedList;
import java.util.Queue;
import java.util.Scanner;
import java.util.concurrent.BrokenBarrierException;
import java.util.concurrent.CyclicBarrier;

public class Main {
    private static int N, M, n, m, p, lineOffset, columnOffset;
    private static int[][] matrix, kernel, finalMatrix;

    private static CyclicBarrier barrier;

    public static void read(String path) {
        try {
            File myObj = new File(path);
            Scanner myReader = new Scanner(myObj);

            if (myReader.hasNextLine()) {
                N = Integer.parseInt(myReader.nextLine());
                M = Integer.parseInt(myReader.nextLine());
            }
            matrix = new int[N + 2 * lineOffset][M + 2 * columnOffset];
            if (myReader.hasNextLine()) {
                for (int i = 0; i < N; i++) {
                    String data = myReader.nextLine();
                    String[] line = data.split(" ");
                    for (int j = 0; j < M; j++) {
                        matrix[i][j] = Integer.parseInt(line[j]);
                    }
                }
            }

            if (myReader.hasNextLine()) {
                n = Integer.parseInt(myReader.nextLine());
                m = Integer.parseInt(myReader.nextLine());
            }
            kernel = new int[n][m];
            if (myReader.hasNextLine()) {
                for (int i = 0; i < n; i++) {
                    String data = myReader.nextLine();
                    String[] line = data.split(" ");
                    for (int j = 0; j < m; j++) {
                        kernel[i][j] = Integer.parseInt(line[j]);
                    }
                }
            }
            myReader.close();
        } catch (FileNotFoundException e) {
            System.out.println("An error occurred.");
            e.printStackTrace();
        }
    }

    public static void write(String path, int[][] matrix) {
        try {
            BufferedWriter bw = new BufferedWriter(new FileWriter(path));
            for (int[] elem : matrix) {
                for (int i : elem) {
                    bw.write(i + " ");
                }
                bw.newLine();
            }
            bw.flush();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static void main(String[] args) throws InterruptedException {
        read("D:\\Facultate\\Anul3\\Sem1\\PPD\\Laboratoare\\Lab2\\Solution\\date.txt");
//        p = Integer.parseInt(args[0]);
        p = 2;
        lineOffset = (n - 1) / 2;
        columnOffset = (m - 1) / 2;
        barrier = new CyclicBarrier(p);

        addBorders(lineOffset, columnOffset);

        parallelConvolution();

        write("D:\\Facultate\\Anul3\\Sem1\\PPD\\Laboratoare\\Lab2\\Solution\\output.txt", finalMatrix);
    }

    public static void addBorders(int lineOffset, int columnOffset) {
        int[][] aux = new int[N + 2 * lineOffset][M + 2 * columnOffset];
        for (int i = 0; i < N + 2 * lineOffset; i++) {
            for (int j = 0; j < M + 2 * columnOffset; j++) {
                int a, b;
                if (i < lineOffset)
                    a = 0;
                else if (i >= N + lineOffset)
                    a = N - 1;
                else
                    a = i - lineOffset;
                if (j < columnOffset)
                    b = 0;
                else if (j >= M + columnOffset)
                    b = M - 1;
                else
                    b = j - columnOffset;
                aux[i][j] = matrix[a][b];
            }
        }
        for (int i = 0; i < N + 2 * lineOffset; i++) {
            System.arraycopy(aux[i], 0, matrix[i], 0, M + 2 * columnOffset);
        }
    }

    public static int singlePixelConvolution(int x, int y, int[][] previousLines, int[] currentLine) {
        int output = 0;
        // Compute neighbours above
        for (int i = 0; i < lineOffset; i++) {
            for (int j = 0; j < m; j++) {
                int a = j - y - columnOffset + j;
                output += kernel[i][j] * previousLines[2 - lineOffset + i][a];
            }
        }
        // Compute current neighbours and element
        for (int i = 0; i < m; i++) {
            int a = y - columnOffset + i;
            output = kernel[lineOffset][i] * currentLine[a];
        }
        // Compute neighbours below
        for (int i = lineOffset + 1; i < n; i++) {
            for (int j = 0; j < m; j++) {
                int a = x - lineOffset + i;
                int b = y - columnOffset + j;
                output += kernel[i][j] * matrix[a][b];
            }
        }
        return output;
    }

    public static void parallelConvolution() throws InterruptedException {
        Thread[] t = new Worker[p];

        int start, end = 0;
        int chunk = N / p;
        int rest = N % p;

        long startTime = System.nanoTime();

        for (int i = 0; i < t.length; i++) {
            start = end;
            end = start + chunk;
            if (rest > 0) {
                end++;
                rest--;
            }
            t[i] = new Worker(M, start, end, finalMatrix);
            t[i].start();
        }

        for (Thread thread : t) {
            thread.join();
        }

        long stopTime = System.nanoTime();

        System.out.println((double)(stopTime - startTime) / 1E6);
    }

    public static class Worker extends Thread {
        int M, start, end;
        int[][] finalMatrix;

        public Worker(int M, int start, int end, int[][] finalMatrix) {
            this.M = M;
            this.start = start;
            this.end = end;
            this.finalMatrix = finalMatrix;
        }

        public void run() {
            int[][] previousLines = new int[2][M + 2 * columnOffset];
            int[] currentLine = new int[M + 2 * columnOffset];

            Queue<Integer> frontierValues = new LinkedList<>();

            if (N > M) {
                System.arraycopy(matrix[start - 1], 0, previousLines[1], 0, M + 2 * columnOffset);
                if (lineOffset > 1) {
                    System.arraycopy(matrix[start - 2], 0, previousLines[0], 0, M + 2 * columnOffset);
                }

                for (int i = start; i < end; i++) {
                    System.arraycopy(matrix[i], 0, currentLine, 0, M + 2 * columnOffset);
                    for (int j = columnOffset; j < M + columnOffset; j++) {
                        int number = singlePixelConvolution(i, j, previousLines, currentLine);
                        if ((i - start < lineOffset) || (end - i <= lineOffset))
                            frontierValues.add(number);
                        else
                            matrix[i][j] = number;
                    }
                    System.arraycopy(previousLines[1], 0, previousLines[0], 0, M + 2 * columnOffset);
                    System.arraycopy(currentLine, 0, previousLines[1], 0, M + 2 * columnOffset);
                }

                try{
                    barrier.await();
                    for(int i = start; i < end; i++){
                        for(int j = columnOffset; j < M + columnOffset; j++){
                            if ((i - start < lineOffset) || (end - i <= lineOffset)){
                                matrix[i][j] = frontierValues.element();
                                frontierValues.remove();
                            }
                        }
                    }
                }catch (BrokenBarrierException | InterruptedException e) {
                    e.printStackTrace();
                }

            }
            else {
                System.arraycopy(matrix[lineOffset - 1], 0, previousLines[1], 0, M + 2 * columnOffset);
                if (lineOffset > 1){
                    System.arraycopy(matrix[lineOffset - 2], 0, previousLines[0], 0, M + 2 * columnOffset);
                }

                for (int i = lineOffset; i < N + lineOffset; i++) {
                    System.arraycopy(matrix[i], 0, currentLine, 0, M + 2 * columnOffset);
                    for (int j = start; j < end; j++) {
                        int number = singlePixelConvolution(i, j, previousLines, currentLine);
                        if ((j - start < columnOffset) || (end - j <= columnOffset))
                            frontierValues.add(number);
                        else
                            matrix[i][j] = number;
                    }
                    System.arraycopy(previousLines[1], 0, previousLines[0], 0, M + 2 * columnOffset);
                    System.arraycopy(currentLine, 0, previousLines[1], 0, M + 2 * columnOffset);
                }

                try {
                    barrier.await();
                    for (int i = lineOffset; i < N + lineOffset; i++){
                        for(int j = start; j < end; j++) {
                            if ((j - start < columnOffset) || (end - j <= columnOffset)) {
                                matrix[i][j] = frontierValues.element();
                                frontierValues.remove();
                            }
                        }
                    }
                }catch (BrokenBarrierException | InterruptedException e) {
                    e.printStackTrace();
                }
            }

        }
    }
}
