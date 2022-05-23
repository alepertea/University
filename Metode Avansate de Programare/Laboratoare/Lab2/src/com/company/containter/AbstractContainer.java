package com.company.containter;

import com.company.model.Task;
import com.company.utils.Constanta;

public abstract class AbstractContainer implements Container
{
    protected Task[] tasks;
    protected int size;

    public AbstractContainer()
    {
        this.tasks = new Task[Constanta.INITIAL_SIZE_CONTAINER];
        this.size = 0;
    }

    @Override
    public void add(Task task)
    {
        if(this.tasks.length == this.size)
        {
            Task[] t = new Task[this.tasks.length * 2];
            System.arraycopy(this.tasks,0,t,0, this.tasks.length);
            this.tasks = t;
        }
        this.tasks[this.size++] = task;
    }

    @Override
    public int size()
    {
        return this.size;
    }

    @Override
    public boolean isEmpty()
    {
        return this.size == 0;
    }
}
