package com.company.runner;

import com.company.utils.Constanta;

import java.time.LocalDateTime;

public class PrinterTaskRunner extends AbstractTaskRunner
{
    public PrinterTaskRunner(TaskRunner runner)
    {
        super(runner);
    }

    @Override
    public void executeOneTask()
    {
        runner.executeOneTask();
        this.decorateExecuteOneTask();
    }

    private void decorateExecuteOneTask()
    {
        System.out.println("Task executat: " + LocalDateTime.now().format(Constanta.DATE_TIME_FORMATTER));
    }
}
