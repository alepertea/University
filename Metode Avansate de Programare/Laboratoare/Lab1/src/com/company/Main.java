package com.company;

public class Main
{
    public static void main(String[] args)
    {
        ExpressionParser parser = new ExpressionParser();
        ComplexExpression exp = parser.parseExpression(args);
        if(exp != null)
            exp.execute();
    }
}
