package com.company.sort;

public class QuickSort extends AbstractSorter
{
    public QuickSort() { super(); }

    private int partition(int[] arr, int low, int high)
    {
        int pivot = arr[high];
        int i = low - 1;
        for (int j = low; j < high; j++)
        {
            if (arr[j] < pivot)
            {
                i++;
                int temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }

        int temp = arr[i + 1];
        arr[i + 1] = arr[high];
        arr[high] = temp;

        return i + 1;
    }

    private void sortRec(int[] arr, int low, int high)
    {
        if (low < high)
        {
            int pi = partition(arr, low, high);
            sortRec(arr, low, pi-1);
            sortRec(arr, pi+1, high);
        }
    }

    @Override
    public void sort(int[] numbers)
    {
        sortRec(numbers, 0, numbers.length - 1);
    }
}
