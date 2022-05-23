package com.company;

public class AdditionExpression extends ComplexExpression
{
    // Constructor:
    public AdditionExpression(Operation op, Complex[] sir)
    {
        super(op,sir);
    }

    /*
        Creeaza un nou numar complex care reprezinta suma dintre c1 si c2
        Input: c1, c2 - numere complexe
        Output: noul numar complex
     */
    @Override
    protected Complex executeOneOperation(Complex c1, Complex c2)
    {
        double re = c1.add(c2).getRe();
        double im = c1.add(c2).getIm();
        return new Complex(re, im);
    }
}
