package com.company.runner;

import com.company.utils.Constanta;

import java.time.LocalDateTime;

public class DelayTaskRunner extends AbstractTaskRunner
{
    public DelayTaskRunner(TaskRunner runner)
    {
        super(runner);
    }

    @Override
    public void executeOneTask()
    {
        try
        {
            Thread.sleep(3000);
            runner.executeOneTask();
            this.decorateExecuteOneTask();
        } catch (InterruptedException e)
        {
            e.printStackTrace();
        }
    }

    private void decorateExecuteOneTask()
    {
        System.out.println("Task executat: " + LocalDateTime.now().format(Constanta.DATE_TIME_FORMATTER));
    }
}
