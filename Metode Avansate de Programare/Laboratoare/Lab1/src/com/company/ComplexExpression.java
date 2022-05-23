package com.company;

public abstract class ComplexExpression
{
    private Operation operation;
    private Complex[] args;

    public ComplexExpression(Operation op, Complex[] sir)
    {
        this.operation = op;
        this.args = sir;
    }

    /*
        Executa o operatie intre doua numere complexe.
        Poate fi accesat doar din clasele care fac override.
     */
    protected abstract Complex executeOneOperation(Complex c1, Complex c2);

    /*
        Executa operatiile pe sirul de numere complexe
     */
    public final void execute()
    {
        Complex temporary = this.args[0];
        for(int i = 1; i < this.args.length; i++)
            temporary = this.executeOneOperation(temporary, this.args[i]);
        System.out.println(temporary);
    }
}