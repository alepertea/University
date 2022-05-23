package com.company.runner;

import com.company.model.Task;

public abstract class AbstractTaskRunner implements TaskRunner
{
    protected TaskRunner runner;

    public AbstractTaskRunner(TaskRunner runner)
    {
        this.runner = runner;
    }

    @Override
    public abstract void executeOneTask();

    @Override
    public void executeAll()
    {
        while(this.runner.hasTask())
            this.executeOneTask();
    }

    @Override
    public void addTask(Task t)
    {
        this.runner.addTask(t);
    }

    @Override
    public boolean hasTask()
    {
        return this.runner.hasTask();
    }
}
