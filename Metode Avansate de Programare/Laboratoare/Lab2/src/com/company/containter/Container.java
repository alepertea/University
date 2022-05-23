package com.company.containter;
import com.company.model.Task;

public interface Container
{
    Task remove();
    void add(Task task);
    int size();
    boolean isEmpty();
}
