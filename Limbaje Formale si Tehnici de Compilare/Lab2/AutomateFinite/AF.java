package com.company;

import java.util.*;

public class AF {
    private Set<String> multimeStari;
    private Set<String> alfabetIntrare;
    private List<Tranzitie> tranzitii;
    private String stareInitiala;
    private Set<String> stariFinale;

    private Set<String> letters = new HashSet<>();
    private Set<String> digits = new HashSet<>();

    public AF(Set<String> multimeStari, Set<String> alfabetIntrare, List<Tranzitie> tranzitii, String stareInitiala, Set<String> stariFinale) {
        this.multimeStari = multimeStari;
        this.alfabetIntrare = alfabetIntrare;
        this.tranzitii = tranzitii;
        this.stareInitiala = stareInitiala;
        this.stariFinale = stariFinale;

        Collections.addAll(letters, "a","b","c","d","e","f","g","h","i","j","k","l","m","n","o","p","q","r","s","t","u","v","w","x","y","z");
        Collections.addAll(digits, "0","1","2","3","4","5","6","7","8","9");
    }

    public boolean checkAFD() {
        List<String> stari = new ArrayList<>();
        for (Tranzitie t : this.tranzitii) {
            if (stari.contains(t.getStareInitiala()))
                return false;
            else
                stari.add(t.getStareInitiala());
        }
        return true;
    }

    /*
    CONST = [-], digit, {digit};
    digit = ‘0’ | ‘1’ | ‘2’ | ‘3’ | ‘4’ | ‘5’ | ‘6’ | ‘7’ | ‘8’ | ‘9’;
     */
    public boolean isCONST(String sequence) {
        String stareInitiala = this.stareInitiala;
        String stareFinala = "";
        boolean ok = true;

        for (int i = 0; i < sequence.length() && ok; i++) {
            String character = sequence.substring(i, i + 1);
            String nextCharacter = "";

            for (Tranzitie tranzitie : tranzitii) {
                if (tranzitie.getStareInitiala().equals(stareInitiala)) {
                    if (tranzitie.getValoare().equals("digit")) {
                        if (digits.contains(character)) {
                            nextCharacter = tranzitie.getStareFinala();
                            break;
                        }
                    }
                    if (character.equals("-") && tranzitie.getStareInitiala().equals(this.stareInitiala) && tranzitie.getValoare().equals("-")) {
                        nextCharacter = tranzitie.getStareFinala();
                        break;
                    }
                }
            }

            if (nextCharacter.equals(""))
                ok = false;

            if (stariFinale.contains(nextCharacter) && i == sequence.length() - 1) {
                ok = true;
                stareFinala = nextCharacter;
                break;
            }

            stareInitiala = nextCharacter;
            stareFinala = nextCharacter;
        }

        if (!stariFinale.contains(stareFinala))
            ok = false;
        return ok;
    }

    public boolean verifySequence(String sequence) {
        String stareInitiala = this.stareInitiala;
        String stareFinala = "";
        boolean ok = true;

        for (int i = 0; i < sequence.length() && ok; i++) {
            String character = sequence.substring(i, i + 1);
            String nextCharacter = "";

            for (Tranzitie tranzitie : tranzitii) {
                if (tranzitie.getStareInitiala().equals(stareInitiala) && tranzitie.getValoare().equals(character)) {
                    nextCharacter = tranzitie.getStareFinala();
                    break;
                }
            }

            if (nextCharacter.equals(""))
                ok = false;

            if (stariFinale.contains(nextCharacter) && i == sequence.length() - 1) {
                ok = true;
                stareFinala = nextCharacter;
                break;
            }

            stareInitiala = nextCharacter;
            stareFinala = nextCharacter;
        }

        if (!stariFinale.contains(stareFinala))
            ok = false;
        return ok;
    }

    public String findLongestPrefix(String sequence) {
        String stareInitiala = this.stareInitiala;
        String stareFinala = "";
        String prefix = "";
        String backup = "";

        for (int i = 0; i < sequence.length(); i++) {
            String character = sequence.substring(i, i + 1);
            String nextCharacter = "";
            for (Tranzitie tranzitie : tranzitii) {
                if (tranzitie.getStareInitiala().equals(stareInitiala) && tranzitie.getValoare().equals(character)) {
                    nextCharacter = tranzitie.getStareFinala();
                    prefix += tranzitie.getValoare();
                    break;
                }
            }
            if (nextCharacter.equals("")) {
                break;
            }
            if (stariFinale.contains(nextCharacter)) {
                backup = prefix;
            }

            if (stariFinale.contains(nextCharacter) && i == sequence.length() - 1) {
                stareFinala = nextCharacter;
                break;
            }
            stareInitiala = nextCharacter;
            stareFinala = nextCharacter;
        }
        if (!stariFinale.contains(stareFinala))
            return backup;
        return prefix;
    }

    public void printMultimeStari() {
        System.out.print("Multimea starilor: { ");
        for (String element : multimeStari) {
            System.out.print(element + " ");
        }
        System.out.println("}.");
    }

    public void printAlfabetIntrare() {
        System.out.print("Alfabetul de intrare: { ");
        for (String element : alfabetIntrare) {
            System.out.print(element + " ");
        }
        System.out.println("}.");
    }

    public void printTranzitii() {
        System.out.println("Tranzitiile:");
        tranzitii.forEach(System.out::println);
    }

    public void printStariFinale() {
        System.out.print("Starile finale: { ");
        for (String element : stariFinale) {
            System.out.print(element + " ");
        }
        System.out.println("}.");
    }

    public Set<String> getMultimeStari() { return multimeStari; }
    public void setMultimeStari(Set<String> multimeStari) { this.multimeStari = multimeStari; }
    public Set<String> getAlfabetIntrare() { return alfabetIntrare; }
    public void setAlfabetIntrare(Set<String> alfabetIntrare) { this.alfabetIntrare = alfabetIntrare; }
    public List<Tranzitie> getTranzitii() { return tranzitii; }
    public void setTranzitii(List<Tranzitie> tranzitii) { this.tranzitii = tranzitii; }
    public String getStareInitiala() { return stareInitiala; }
    public void setStareInitiala(String stareInitiala) { this.stareInitiala = stareInitiala; }
    public Set<String> getStariFinale() { return stariFinale; }
    public void setStariFinale(Set<String> stariFinale) { this.stariFinale = stariFinale; }
}
