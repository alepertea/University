package com.company;

import java.util.*;

public class Lab1
{
    // Ex 1
    private static String lastWordOfSequence(String text)
    {
        String[] words = text.split(" ");
        String lastWord = "";

        for(String word : words) {
            if(lastWord.compareTo(word) < 0) {
                lastWord = word;
            }
        }

        return lastWord;
    }

    public static void testEx1()
    {
        assert lastWordOfSequence("Ana are mere rosii si galbene").equals("si");
        assert lastWordOfSequence("").equals("");
        assert lastWordOfSequence(" ").equals("");

        System.out.println("Ex 1: successful!");
    }

    // Ex 2
    private static double computeDistance(double[] firstPoint, double[] secondPoint)
    {
        return Math.sqrt(Math.pow(firstPoint[0] - secondPoint[0], 2) + Math.pow(firstPoint[1] - secondPoint[1], 2));
    }

    public static void testEx2()
    {
        assert computeDistance(new double[]{1, 5}, new double[]{4, 1}) == 5.0;
        System.out.println("Ex 2: successful!");
    }

    // Ex 3
    private static double computeScalarProduct(double[] firstVector, double[] secondVector)
    {
        double product = 0;
        for(int i = 0; i < firstVector.length; i++) {
            product += firstVector[i] * secondVector[i];
        }
        return product;
    }

    public static void testEx3()
    {
        assert computeScalarProduct(new double[]{1, 0, 2, 0, 3}, new double[]{1, 2, 0, 3, 1}) == 4;
        System.out.println("Ex 3: successful!");
    }

    // Ex 4
    private static List<String> oneTimeApparitions(String text)
    {
        String[] words = text.split(" ");
        List<String> result = new ArrayList<>();

        Map<String, Integer> freq = new HashMap<>();

        for(String word : words)
        {
            if(freq.containsKey(word))
            {
                int newFreq = freq.get(word) + 1;
                freq.replace(word, newFreq);
            }
            else {
                freq.put(word, 1);
            }
        }

        for(String word : freq.keySet()) {
            if(freq.get(word).equals(1)) {
                result.add(word);
            }
        }

        return result;
    }

    public static void testEx4()
    {
        String input = "ana are ana are mere rosii";
        assert oneTimeApparitions(input).size() == 2;
        assert oneTimeApparitions(input).get(0).equals("mere") && oneTimeApparitions(input).get(1).equals("rosii");
        assert oneTimeApparitions("ana ana").size() == 0;

        System.out.println("Ex 4: successful!");
    }

    // Ex 5
    private static int findRepeatingValue(int[] array)
    {
        int sum = 0;
        for(int element : array) {
            sum += element;
        }

        return sum - (array.length * (array.length - 1)) / 2;
    }

    public static void testEx5()
    {
        assert findRepeatingValue(new int[]{1, 2, 3, 4, 2}) == 2;
        System.out.println("Ex 5: successful!");
    }

    // Ex 6
    private static int findElement(int[] array)
    {
        Map<Integer, Integer> freq = new HashMap<>();

        for(int element : array)
        {
            if(freq.containsKey(element))
            {
                int newFreq = freq.get(element) + 1;
                freq.replace(element, newFreq);
            }
            else {
                freq.put(element, 1);
            }
        }

        for(Integer element : freq.keySet()) {
            if(freq.get(element) >= array.length / 2) {
                return element;
            }
        }

        return -1;
    }

    public static void testEx6()
    {
        assert findElement(new int[]{2,8,7,2,2,5,2,3,1,2,2}) == 2;
        System.out.println("Ex 6: successful!");
    }

    // Ex 7
    private static int findKthBiggestElement(ArrayList<Integer> array, int k)
    {
        array.sort(Comparator.reverseOrder());
        return array.get(k - 1);
    }

    public static void testEx7()
    {
        ArrayList<Integer> array = new ArrayList<>(Arrays.asList(7, 4, 6, 3, 9, 1));
        assert findKthBiggestElement(array, 2) == 7;
        System.out.println("Ex 7: successful!");
    }

    // Ex 8
    private static ArrayList<String> generateBinary(int n)
    {
        ArrayList<String> result = new ArrayList<>();

        Queue<String> queue = new LinkedList<>();
        queue.add("1");
        while(n > 0)
        {
            String s = queue.peek();
            queue.remove();
            result.add(s);

            queue.add(s + "0");
            queue.add(s + "1");

            n--;
        }

        return result;
    }

    public static void testEx8()
    {
        ArrayList<String> result = generateBinary(5);
        for(String s : result)
            System.out.println(s);
    }

    // Ex 9
    private static int computeMatrixSum(int[][] matrix, int[] firstPair, int[] secondPair)
    {
        int sum = 0;
        for(int i = firstPair[0]; i <= secondPair[0]; i++) {
            for(int j = firstPair[1]; j <= secondPair[1]; j++) {
                sum += matrix[i][j];
            }
        }
        return sum;
    }

    public static void testEx9()
    {
        int[][] matrix = new int[][]{{0,2,5,4,1}, {4,8,2,3,7}, {6,3,4,6,2}, {7,3,1,8,3}, {1,5,7,9,4}};
        assert computeMatrixSum(matrix, new int[]{1,1}, new int[]{3,3}) == 38;
        System.out.println("Ex 9: successful!");
    }

    // Ex 10
    private static int findArray(int[][] matrix)
    {
        int maxSum = 0;
        int line = -1;

        for(int i = 0; i < matrix.length; i++)
        {
            int sum = 0;
            for (int j = 0; j < matrix[i].length; j++) {
                sum += matrix[i][j];
            }
            if(sum > maxSum) {
                line = i;
            }
        }

        return line;
    }

    public static void testEx10()
    {
        int[][] matrix = new int[][]{{0, 0, 0, 1, 1}, {0, 1, 1, 1, 1}, {0, 0, 1, 1, 1}};
        assert findArray(matrix) == 2;
        System.out.println("Ex 10: successful!");
    }
}
