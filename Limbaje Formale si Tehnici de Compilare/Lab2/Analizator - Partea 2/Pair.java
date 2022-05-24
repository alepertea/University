package com.company;

public class Pair {
    private String simbol;
    private int codTS;
    public static int codAtomTS = 0;

    public Pair(String simbol, int codTS) {
        this.simbol = simbol;
        this.codTS = codTS;
    }

    public String getSimbol() { return this.simbol; }

    public int getCodTS() { return this.codTS; }
}
