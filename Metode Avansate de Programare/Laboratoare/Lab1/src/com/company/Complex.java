package com.company;

public class Complex
{
    private double re;
    private double im;

    /*
        Constructor:
     */
    public Complex(double real, double imag)
    {
        this.re = real;
        this.im = imag;
    }

    /*
        Getters si setters
     */
    public double getRe() { return this.re; }
    public double getIm() { return this.im; }
    public void setRe(double value) { this.re = value; }
    public void setIm(double value) { this.im = value; }

    /*
        Returneaza suma a doua numere complexe
        Input: nr - numar complex
        Output: noul numar complex, suma (this + nr)
     */
    public Complex add(Complex nr)
    {
        double real = this.re + nr.getRe();
        double imag = this.im + nr.getIm();
        return new Complex(real, imag);
    }

    /*
        Returneaza diferenta a doua numere complexe
        Input: nr - numar complex
        Output: noul numar complex, diferenta (this - nr)
     */
    public Complex subtract(Complex nr)
    {
        double real = this.re - nr.getRe();
        double imag = this.im - nr.getIm();
        return new Complex(real, imag);
    }

    /*
        Returneaza produsul a doua numere complexe
        Input: nr - numar complex
        Output: noul numar complex, produsul (this * nr)
     */
    public Complex multiply(Complex nr)
    {
        double real = this.re * nr.getRe() - this.im * nr.getIm();
        double imag = this.re * nr.getIm() + nr.getRe() * this.im;
        return new Complex(real, imag);
    }

    /*
        Returneaza impartirea a doua numere complexe
        Input: nr - numar complex
        Output: noul numar complex, impartirea (this / nr)
     */
    public Complex divide(Complex nr)
    {
        double real = this.multiply(nr.conjugate()).re / (Math.pow(nr.re, 2) + Math.pow(nr.im, 2));
        double imag = this.multiply(nr.conjugate()).im / (Math.pow(nr.re, 2) + Math.pow(nr.im, 2));
        return new Complex(real, imag);
    }

    /*
        Returneaza conjugatul numarului complex
     */
    public Complex conjugate()
    {
        return new Complex(this.re, -this.im);
    }

    /*
        Afiseaza numarul complex ca un string
     */
    @Override
    public String toString()
    {
        if(this.re == 0)
            return this.im + "i";
        if(this.im == 0)
            return "" + this.re;
        if (this.im < 0)
            return this.re + " - " + this.im + "*i ";
        else
            return this.re + " + " + this.im + "*i ";
    }
}

