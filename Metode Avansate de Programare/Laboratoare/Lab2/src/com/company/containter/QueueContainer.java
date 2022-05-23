package com.company.containter;

import com.company.model.Task;

public class QueueContainer extends AbstractContainer
{
    public QueueContainer()
    {
        super();
    }

    @Override
    public Task remove()
    {
        if(!this.isEmpty())
        {
            Task tsk = this.tasks[0];
            System.arraycopy(this.tasks, 1, this.tasks, 0, this.size - 1);
            this.size--;
            return tsk;
        }
        return null;
    }
}