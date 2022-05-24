package com.company;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class Main {

    private static List<String> readFile() {
        List<String> reguliProductie = new ArrayList<>();
        try {
            File myObj = new File("input.txt");
            Scanner myReader = new Scanner(myObj);
            while (myReader.hasNextLine()) {
                String data = myReader.nextLine();
                reguliProductie.add(data);
            }
            myReader.close();
        } catch (FileNotFoundException e) {
            System.out.println("An error occurred.");
            e.printStackTrace();
        }
        return reguliProductie;
    }

    private static boolean find(String regulaProductie, String regex) {
        Pattern pattern = Pattern.compile(regex);
        Matcher matcher = pattern.matcher(regulaProductie);
        return matcher.find();
    }

    public static void main(String[] args) {
        List<String> reguliProductie = readFile();

        Scanner scanner = new Scanner(System.in);
        System.out.println("Ne-terminal:");
        String data = scanner.nextLine();

        if(data.matches("[A-H]")) {
            for (String regula : reguliProductie) {
                if (find(regula, data))
                    System.out.println(regula);
            }
        }
        else
            System.out.println("Inputul nu este neterminal");
    }
}
