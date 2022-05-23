package com.company;

public class DivExpression extends ComplexExpression
{
    public DivExpression(Operation op, Complex[] sir)
    {
        super(op, sir);
    }

    /*
        Creeaza un nou numar complex care reprezinta raportul dintre c1 si c2
        Input: c1, c2 - numere complex
        Output: noul numar complex
     */
    @Override
    public Complex executeOneOperation(Complex c1, Complex c2)
    {
        double re = c1.divide(c2).getRe();
        double im = c1.divide(c2).getIm();
        return new Complex(re, im);
    }
}
