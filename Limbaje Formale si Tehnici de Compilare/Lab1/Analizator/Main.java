package com.company;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.*;

public class Main {
    private static Pair pair;
    private static TS ts;
    private static List<FIP> fip;
    private static Map<String, Integer> atoms;

    private static void initiateMap() {
        atoms = new HashMap<>();
        atoms.put("ID", 0); atoms.put("CONST", 1); atoms.put("program", 2); atoms.put("begin", 3); atoms.put("var", 4);
        atoms.put("type", 5); atoms.put("end", 6); atoms.put("integer", 7); atoms.put("real", 8); atoms.put("if", 9); atoms.put("while", 10);
        atoms.put("readln", 11); atoms.put("writeln", 12); atoms.put(".", 13); atoms.put(",", 14); atoms.put(";", 15); atoms.put("+", 16);
        atoms.put("-", 17); atoms.put("*", 18); atoms.put(":=", 19); atoms.put("<", 20); atoms.put(">", 21); atoms.put("<>", 22);
        atoms.put(":", 23); atoms.put("(", 24); atoms.put(")", 25);
    }

    private static boolean isID(String atom) {
        return atom.matches("^[a-z][a-z0-9]{0,7}");
    }

    private static boolean isCONST(String atom) {
        return atom.matches("^[0-9]\\.*[0-9]*");
    }

    private static void processLine(String line, int lineNumber) {
        List<String> elements = List.of(line.split(" "));
        int cod = -1;
        for (String e: elements) {
            if(isCONST(e)) {
                cod = addToTS(e);
                FIP f = new FIP(e, atoms.get("CONST"), cod);
                fip.add(f);
            }
            else if (atoms.get(e) != null) {
                FIP f = new FIP(e, atoms.get(e), -1);
                fip.add(f);
            }
            else if (isID(e)) {
                cod = addToTS(e);
                FIP f = new FIP(e, atoms.get("ID"), cod);
                fip.add(f);
            }
            else {
                System.out.println("Error on line " + lineNumber + " for atom " + e + "!");
            }
        }
    }

    private static int addToTS(String element) {
        if (ts.find(element) != null){
            return Pair.codAtom;
        }
        if (ts.size() == 0) {
            ts.add(new Pair(element, Pair.codAtom), 0);
            Pair.codAtom++;
        }
        else if (element.compareTo(ts.get(0).getSimbol()) < 0) {
            ts.add(new Pair(element, Pair.codAtom), 0);
            Pair.codAtom++;
        }
        else if (element.compareTo(ts.get(ts.size() - 1).getSimbol()) > 0) {
            ts.add(new Pair(element, Pair.codAtom), ts.size());
            Pair.codAtom++;
        }
        else {
            int i = 0;
            while (element.compareTo(ts.get(i).getSimbol()) > 0) i++;
            ts.add(new Pair(element, Pair.codAtom), i);
            Pair.codAtom++;
        }
        return ts.size();
    }

    public static void main(String[] args) {
        int lineNumber = 1;
        ts = new TS(20);
        fip = new ArrayList<>();
        initiateMap();

        try {
            File myObj = new File("program.txt");
            Scanner myReader = new Scanner(myObj);
            while (myReader.hasNextLine()) {
                String data = myReader.nextLine();
                processLine(data, lineNumber);
                lineNumber++;
            }
            myReader.close();
        } catch (FileNotFoundException e) {
            System.out.println("An error occurred.");
            e.printStackTrace();
        }

        System.out.println("TABELA DE SIMBOLURI:");
        for(int i = 0; i < ts.size(); i++) {
            System.out.println(ts.get(i).getSimbol() + "\t|\t" + ts.get(i).getCodTS());
        }
        System.out.println("\nFORMA INTERNA A PROGRAMULUI:");
        for (FIP f: fip) {
            System.out.println(f.toString());
        }
    }
}
