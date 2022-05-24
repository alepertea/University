package com.company;

public class Tranzitie {
    private String stareInitiala;
    private String stareFinala;
    private String valoare;

    public Tranzitie(String stareInitiala, String stareFinala, String valoare) {
        this.stareInitiala = stareInitiala;
        this.stareFinala = stareFinala;
        this.valoare = valoare;
    }

    public String getStareInitiala() {
        return stareInitiala;
    }

    public void setStareInitiala(String stareInitiala) {
        this.stareInitiala = stareInitiala;
    }

    public String getStareFinala() {
        return stareFinala;
    }

    public void setStareFinala(String stareFinala) {
        this.stareFinala = stareFinala;
    }

    public String getValoare() {
        return valoare;
    }

    public void setValoare(String valoare) {
        this.valoare = valoare;
    }

    @Override
    public String toString() {
        return this.stareInitiala + "   ->(" + this.valoare + ")    " + this.stareFinala;
    }
}
