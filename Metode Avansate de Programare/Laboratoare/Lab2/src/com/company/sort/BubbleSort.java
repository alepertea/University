package com.company.sort;

public class BubbleSort extends AbstractSorter
{
    public BubbleSort() { super(); }

    @Override
    public void sort(int[] numbers)
    {
        int i, j, temp;
        boolean swapped;
        int n = numbers.length;

        for (i = 0; i < n - 1; i++)
        {
            swapped = false;
            for (j = 0; j < n - i - 1; j++)
            {
                if (numbers[j] > numbers[j + 1])
                {
                    temp = numbers[j];
                    numbers[j] = numbers[j + 1];
                    numbers[j + 1] = temp;
                    swapped = true;
                }
            }
            if (!swapped)
                break;
        }
    }
}
