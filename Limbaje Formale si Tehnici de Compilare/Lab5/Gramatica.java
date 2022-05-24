package com.company;

import java.util.List;

public class Gramatica {
    private List<String> terminale;
    private List<String> neterminale;
    List<String> reguliProductie;
    Character simbolInitial;

    public Gramatica(List<String> terminale, List<String> neterminale, List<String> reguliProductie) {
        this.terminale = terminale;
        this.neterminale = neterminale;
        this.reguliProductie = reguliProductie;
    }

    public List<String> getTerminale() {
        return terminale;
    }

    public void setTerminale(List<String> terminale) {
        this.terminale = terminale;
    }

    public List<String> getNeterminale() {
        return neterminale;
    }

    public void setNeterminale(List<String> neterminale) {
        this.neterminale = neterminale;
    }

    public List<String> getReguliProductie() {
        return this.reguliProductie;
    }

    public Character getSimbolInitial() {
        return this.simbolInitial;
    }
}
