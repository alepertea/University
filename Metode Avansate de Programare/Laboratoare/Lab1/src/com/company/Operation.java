package com.company;

public enum Operation
{
    ADDITION("+"),
    SUBTRACTION("-"),
    MULTIPLICATION("*"),
    DIVISION("/");

    private String symbol;

    Operation(String s) { this.symbol = s; }

    public static Operation getBySymbol(String s)
    {
        for(Operation op : Operation.values())
            if(op.symbol.equals(s))
                return op;
        return null;
    }
}
