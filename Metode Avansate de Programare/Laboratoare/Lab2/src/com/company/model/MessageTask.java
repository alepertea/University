package com.company.model;

import com.company.utils.Constanta;

import java.time.LocalDateTime;

public class MessageTask extends Task
{
    private String message, to, from;
    private LocalDateTime date;

    public MessageTask(String taskID, String description, String message, String to, String from, LocalDateTime date)
    {
        super(taskID, description);
        this.message = message;
        this.to = to;
        this.from = from;
        this.date = date;
    }

    @Override
    public String toString()
    {
        return super.toString() + " | Message = " + this.message + " | From =  " + this.from + " | To = " + this.to + " | Date = " + this.date.format(Constanta.DATE_TIME_FORMATTER);
    }

    @Override
    public void execute()
    {
        System.out.println(this.toString());
    }
}
