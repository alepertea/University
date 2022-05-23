package com.company;

public class MultiplyExpression extends ComplexExpression
{
    public MultiplyExpression(Operation op, Complex[] sir)
    {
        super(op, sir);
    }

    /*
        Creeaza un nou numar complex care reprezinta produsul dintre c1 si c2
        Input: c1, c2 - numere complexe
        Output: noul numar complex
     */
    @Override
    public Complex executeOneOperation(Complex c1, Complex c2)
    {
        double re = c1.multiply(c2).getRe();
        double im = c1.multiply(c2).getIm();
        return new Complex(re, im);
    }
}
