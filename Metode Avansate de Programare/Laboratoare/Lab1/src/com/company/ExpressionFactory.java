package com.company;

public class ExpressionFactory
{
    private static ExpressionFactory instance = null;
    private ExpressionFactory() {};

    public static ExpressionFactory getInstance()
    {
        if(instance == null)
            instance = new ExpressionFactory();
        return instance;
    }

    public ComplexExpression createExpression(Operation operation, Complex[] args)
    {
        switch(operation)
        {
            case ADDITION: return new AdditionExpression(operation, args);
            case SUBTRACTION: return new SubtractExpression(operation, args);
            case MULTIPLICATION: return new MultiplyExpression(operation, args);
            case DIVISION: return new DivExpression(operation, args);
        }
        return null;
    }
}
