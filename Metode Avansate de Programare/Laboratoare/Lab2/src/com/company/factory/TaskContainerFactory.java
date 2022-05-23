package com.company.factory;

import com.company.containter.Container;
import com.company.containter.QueueContainer;
import com.company.containter.StackContainer;
import com.company.utils.ContainerStrategy;

public class TaskContainerFactory implements Factory
{
    private static TaskContainerFactory instance = null;

    private TaskContainerFactory() {}

    @Override
    public Container createContainer(ContainerStrategy strategy)
    {
        if(strategy == ContainerStrategy.LIFO)
            return new StackContainer();

        if(strategy == ContainerStrategy.FIFO)
            return new QueueContainer();

        return null;
    }

    public static TaskContainerFactory getInstance()
    {
        if(instance == null)
            instance = new TaskContainerFactory();

        return instance;
    }
}
