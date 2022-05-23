package com.company.runner;

import com.company.containter.Container;
import com.company.utils.ContainerStrategy;
import com.company.factory.TaskContainerFactory;
import com.company.model.Task;

public class StrategyTaskRunner implements TaskRunner
{
    private Container container;

    public StrategyTaskRunner(ContainerStrategy strategy)
    {
        this.container = TaskContainerFactory.getInstance().createContainer(strategy);
    }

    @Override
    public void executeOneTask()
    {
        if(!container.isEmpty())
            this.container.remove().execute();
    }

    @Override
    public void executeAll()
    {
        while(!this.container.isEmpty())
            this.executeOneTask();
    }

    @Override
    public void addTask(Task t)
    {
        this.container.add(t);
    }

    @Override
    public boolean hasTask()
    {
        return !this.container.isEmpty();
    }
}
