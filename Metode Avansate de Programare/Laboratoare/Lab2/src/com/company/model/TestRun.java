package com.company.model;

import com.company.runner.PrinterTaskRunner;
import com.company.utils.ContainerStrategy;
import com.company.runner.DelayTaskRunner;
import com.company.runner.StrategyTaskRunner;
import com.company.utils.SortingStrategy;

import java.time.LocalDateTime;

public class TestRun
{
    public static void main(String[] args)
    {
        MessageTask m1 = new MessageTask("1", "Feedback", "Ai obtinut nota 8", "Ale", "Prof", LocalDateTime.now());
        MessageTask m2 = new MessageTask("2", "Raport", "Frum", "Ale", ":)", LocalDateTime.now());
        MessageTask m3 = new MessageTask("3", "Idk", "lalallaa", "Ale", "bla bla", LocalDateTime.now());

        MessageTask[] msgs = new MessageTask[]{m1, m2, m3};

        ContainerStrategy containerStrategy = ContainerStrategy.valueOf(args[0]);
        StrategyTaskRunner runner = new StrategyTaskRunner(containerStrategy);
        System.out.println("Strategy Task Runner:");
        runner.addTask(msgs[0]);
        runner.addTask(msgs[1]);
        runner.addTask(msgs[2]);
        runner.executeAll();
        System.out.println('\n');

        System.out.println("Delay Task Runner:");
        DelayTaskRunner delay2 = new DelayTaskRunner(runner);
        DelayTaskRunner delay3 = new DelayTaskRunner(delay2);

        DelayTaskRunner delayTaskRunner = new DelayTaskRunner(delay2);
        delayTaskRunner.addTask(msgs[0]);
        delayTaskRunner.addTask(msgs[1]);
        delayTaskRunner.addTask(msgs[2]);
        delayTaskRunner.executeAll();
        System.out.println('\n');

        System.out.println("Printer Task Runner:");
        PrinterTaskRunner printerTaskRunner = new PrinterTaskRunner(runner);
        printerTaskRunner.addTask(msgs[0]);
        printerTaskRunner.addTask(msgs[1]);
        printerTaskRunner.addTask(msgs[2]);
        printerTaskRunner.executeAll();
        System.out.println('\n');

        System.out.println("Sorting Task:");
        int[] numbers = {3, 1, 4, 64, 1, 45, -2, -1, 5, 7};
        SortingTask sortingTask = new SortingTask(numbers, SortingStrategy.valueOf(args[1]));
        runner.addTask(sortingTask);
        runner.executeAll();
        System.out.println(sortingTask.toString());
    }
}
