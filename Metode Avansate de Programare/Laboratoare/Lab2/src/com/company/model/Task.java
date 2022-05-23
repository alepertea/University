package com.company.model;

import java.util.Objects;

public abstract class Task
{
    private String taskID, description;

    public Task() {}

    public Task(String taskID, String description)
    {
        this.taskID = taskID;
        this.description = description;
    }

    public String getTaskID() { return this.taskID; }
    public String getDescription() { return this.description; }
    public void setTaskID(String value) { this.taskID = value; }
    public void setDescription(String value) { this.description = value; }

    public abstract void execute();

    @Override
    public String toString()
    {
        return "ID = " + this.taskID + " | Description = " + this.description;
    }

    @Override
    public boolean equals(Object obj)
    {
        if(obj == this)
            return true;
        if(!(obj instanceof Task))
            return false;
        Task t = (Task)obj;
        return Objects.equals(this.getTaskID(), t.getTaskID()) && Objects.equals(this.getDescription(), t.getDescription());
    }

    @Override
    public int hashCode()
    {
        return Objects.hash(this.getTaskID(), this.getDescription());
    }
}
