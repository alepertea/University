package com.company;

import java.io.*;
import java.util.*;

/*
Structura fisierului de intrare (EBNF):
    lista_stari
    stare_initiala
    CONST
    lista_tranzitii

lista_stari = stare, {' ', stare}
stare = 'q', CONST

stare_initiala = stare

CONST = '0' | '1' | '2' | '3' | '4' | '5' | '6' | '7' | '8' | '9'

lista_tranzitii = tranzitie, {'\n', tranzitie}
tranzitie = stare, ' ', stare, ' ', ID, ' ', bit
ID = ‘a’ | ‘b’ | ‘c’ | ‘d’ | ‘e’ | ‘f’ | ‘g’ | ‘h’ | ‘i’ | ‘j’ | ‘k’ | ‘l’ | ‘m’ | ‘n’ | ‘o’ | ‘p’ | ‘q’ | ‘r’ | ‘s’ | ‘t’ | ‘u’ | ‘v’ | ‘w’ | ‘x’ | ‘y’ | ‘z’
bit = '0' | '1'
 */

public class Main {

    private static Set<String> multimeStari = new HashSet<>();
    private static Set<String> alfabetIntrare = new HashSet<>();
    private static List<Tranzitie> tranzitii = new ArrayList<>();
    private static String stareInitiala = "";
    private static Set<String> stariFinale = new HashSet<>();
    private static AF af;

    private static void findLongestPrefix(String sequence) {
//        if (!af.checkAFD()) {
//            System.out.println("Automatul finit nu este determinist.");
//            return;
//        }
        String prefix = af.findLongestPrefix(sequence);
        System.out.println("Cel mai lung prefix acceptat: " + prefix);
    }

    private static void checkSequence(String sequence) {
//        if (!af.checkAFD()) {
//            System.out.println("Automatul finit nu este determinist.");
//            return;
//        }
        if (af.isCONST(sequence))
            System.out.println("Secventa e acceptata de automat.");
        else
            System.out.println("Secventa nu e acceptata de automat.");
    }

    private static void printElementsOfAF() {
        Scanner scanner = new Scanner(System.in);
        String cmd = "";
        while (true) {
            System.out.println("1. Multimea starilor.\n2. Alfabetul de intrare.\n3. Tranzitiile.\n4. Starile finale.\n0. Exit.\nComanda:");
            cmd = scanner.nextLine();
            switch (cmd) {
                case "1" -> { af.printMultimeStari(); }
                case "2" -> { af.printAlfabetIntrare(); }
                case "3" -> { af.printTranzitii(); }
                case "4" -> { af.printStariFinale(); }
                case "0" -> { return; }
                default -> { System.out.println("Comanda invalida!"); }
            }
        }
    }

    private static void menu(String cmd) {
        Scanner scanner = new Scanner(System.in);
        System.out.println("-------------");
        System.out.println("|   MENIU   |");
        System.out.println("-------------");
        while (true) {
            System.out.println("1. Afisarea elementelor automatului finit.\n2. Verifica daca o secventa e acceptata de automatul finit.\n3. Determina cel mai lung prefix dintr-o secventa data care este acceptata de automat.\n0. Exit.");
            System.out.println("Comanda:");
            cmd = scanner.nextLine();
            switch (cmd) {
                case "1" -> { printElementsOfAF(); }
                case "2" -> {
                    System.out.println("Introduceti secventa:");
                    String sequence = scanner.nextLine();
                    checkSequence(sequence);
                }
                case "3" -> {
                    System.out.println("Introduceti secventa:");
                    String sequence = scanner.nextLine();
                    findLongestPrefix(sequence);
                }
                case "0" -> { return; }
                default -> { System.out.println("Comanda invalida!"); }
            }
        }
    }

    private static void start(String cmd) throws Exception {
        System.out.println("Alegeti metoda de citire:\n\t1. Din fisier.\n\t2. De la tastatura.\n\t0. Exit.\nComanda:");
        Scanner scanner = new Scanner(System.in);
        cmd = scanner.nextLine();
        switch (cmd) {
            case "1" -> { readFromFile(); }
            case "2" -> { readFromKeyboard(); }
            case "0" -> {}
            default -> {
                System.out.println("Comanda invalida!");
                start(cmd);
            }
        }
    }

    private static void readFromFile() {
        try (BufferedReader bufferedReader = new BufferedReader(new FileReader("input.txt"))) {

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
            af = new AF(multimeStari, alfabetIntrare, tranzitii, stareInitiala, stariFinale);
            System.out.println("Datele s-au citit cu succes!");
        } catch (IOException e) {
            System.out.println("Error from readFromFile():");
            e.printStackTrace();
        }
    }

    private static void readFromKeyboard() throws Exception {
        Scanner scanner = new Scanner(System.in);

        System.out.println("Multimea starilor (separate printr-un spatiu pls):");
        Collections.addAll(multimeStari, scanner.nextLine().split(" "));

        do{
            System.out.println("Starea initiala:");
            stareInitiala = scanner.nextLine();
            boolean find = multimeStari.contains(stareInitiala);
            if (!find) {
                System.out.println("Starea initiala trebuie sa se afle printre starile existente!");
            }
        }while (!multimeStari.contains(stareInitiala));

        boolean ok;
        do{
            ok = true;
            System.out.println("Starile finale:");
            String[] data = scanner.nextLine().split(" ");
            for (String element: data) {
                if (!multimeStari.contains(element)) {
                    System.out.println("Starile finale trebuie sa se afle printre starile existente!");
                    ok = false;
                    break;
                }
            }
            if (ok) {
                Collections.addAll(stariFinale, data);
            }
        }while (!ok);

        System.out.println("Numarul tranzitiilor:");
        int num = Integer.parseInt(scanner.nextLine());
        System.out.println("Tranzitiile (stareInitiala, stareFinala, valoare):");
        for(int i = 0; i < num; i++) {
            String[] data = scanner.nextLine().split(" ");
            alfabetIntrare.add(data[2]);
            if (!multimeStari.contains(data[0]) || !multimeStari.contains(data[1])) {
                throw new Exception("Starile trebuie sa fie printre cele existente in multime!");
            }
            tranzitii.add(new Tranzitie(data[0], data[1], data[2]));
        }

        af = new AF(multimeStari, alfabetIntrare, tranzitii, stareInitiala, stariFinale);
        System.out.println("Datele s-au citit cu succes!");
    }

    public static void main(String[] args) {
        String cmd = "";
        try {
            start(cmd);
            menu(cmd);
        }catch (Exception e) {
            System.out.println(e.getMessage());
        }
    }
}
