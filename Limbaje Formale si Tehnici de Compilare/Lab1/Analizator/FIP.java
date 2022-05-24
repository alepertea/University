package com.company;

public class FIP {
    private String atom;
    private int codAtom;
    private int codTS;

    public FIP(String atom, int codAtom, int codTS) {
        this.atom = atom;
        this.codAtom = codAtom;
        this.codTS = codTS;
    }

    @Override
    public String toString() {
        if (this.codTS == -1)
            return this.atom + "\t|\t" + this.codAtom + "\t|\t-";
        return this.atom + "\t|\t" + this.codAtom + "\t|\t" + this.codTS;
    }
}
