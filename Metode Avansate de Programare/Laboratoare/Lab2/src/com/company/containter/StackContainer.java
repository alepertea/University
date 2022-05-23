package com.company.containter;

import com.company.model.Task;

public class StackContainer extends AbstractContainer
{
    public StackContainer()
    {
        super();
    }

    @Override
    public Task remove()
    {
        if(!this.isEmpty())
        {
            this.size--;
            return this.tasks[this.size];
        }
        return null;
    }
}
