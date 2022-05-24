package com.company.automatfinit;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.*;

public class AF_ID {
    private Set<String> multimeStari = new HashSet<>();
    private Set<String> alfabetIntrare = new HashSet<>();
    private List<Tranzitie> tranzitii = new ArrayList<>();
    private String stareInitiala;
    private Set<String> stariFinale = new HashSet<>();

    private Set<String> letters = new HashSet<>();
    private Set<String> digits = new HashSet<>();

    public AF_ID() {
        Collections.addAll(letters, "a","b","c","d","e","f","g","h","i","j","k","l","m","n","o","p","q","r","s","t","u","v","w","x","y","z");
        Collections.addAll(digits, "0","1","2","3","4","5","6","7","8","9");

        try (BufferedReader bufferedReader = new BufferedReader(new FileReader("afID.txt"))) {
            String[] data = bufferedReader.readLine().split(" ");
            Collections.addAll(multimeStari, data);
            stareInitiala = bufferedReader.readLine();
            int num = Integer.parseInt(bufferedReader.readLine());
            for (int i = 0; i < num; i++) {
                data = bufferedReader.readLine().split(" ");
                tranzitii.add(new Tranzitie(data[0], data[1], data[2]));
                alfabetIntrare.add(data[2]);
                if (Objects.equals(data[3], "1")) {
                    stariFinale.add(data[0]);
                }
            }
        } catch (IOException e) {
            System.out.println("Error from AF():");
            e.printStackTrace();
        }
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

    public boolean isID(String sequence) {
        if (sequence.length() > 8)
            return false;

        String stareInitiala = this.stareInitiala;
        String stareFinala = "";
        boolean ok = true;

        for (int i = 0; i < sequence.length() && ok; i++) {
            String character = sequence.substring(i, i + 1);
            String nextCharacter = "";

            for (Tranzitie tranzitie : tranzitii) {
                if (tranzitie.getStareInitiala().equals(stareInitiala)) {
                    if (tranzitie.getValoare().equals("letter")) {
                        if (letters.contains(character)) {
                            nextCharacter = tranzitie.getStareFinala();
                            break;
                        }
                    }
                    if (!tranzitie.getStareInitiala().equals(this.stareInitiala) && (digits.contains(character))) {
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
