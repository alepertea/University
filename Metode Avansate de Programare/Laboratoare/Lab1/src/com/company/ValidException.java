package com.company;

public class ValidException extends Exception
{
    private String message;

    public ValidException(String msg) { this.message = msg; }

    @Override
    public String getMessage() { return this.message; }
}
