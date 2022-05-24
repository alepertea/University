import java.io.*;
import java.util.*;

public class Main {
    static int p;
    static int p1;
    static int nrPolinoame;
    static int gradMaxim;
    static int nrMonoame;

    static List<Integer> generateRandomGrades() {
        Random rand = new Random();
        List<Integer> randomNumbers = new ArrayList<>();
        for (int i = 0; i < nrMonoame; i++) {
            int val = rand.nextInt(gradMaxim);
            while (randomNumbers.contains(val))
                val = rand.nextInt(gradMaxim);
            randomNumbers.add(val);
        }
        Collections.sort(randomNumbers);
        return randomNumbers;
    }

    static List<Integer> generateRandomCoeficienti() {
        Random rand = new Random();
        List<Integer> randomNumbers = new ArrayList<>();
        for (int i = 0; i < nrMonoame; i++) {
            int val = rand.nextInt(100 + 100) - 100;
            while (val == 0) {
                val = rand.nextInt(100 + 100) - 100;
            }
            randomNumbers.add(val);
        }
        return randomNumbers;
    }

    static void generateData() {
        for (int i = 1; i <= nrPolinoame; i++) {
            try (BufferedWriter bw = new BufferedWriter(new FileWriter("C:\\Users\\miamu\\OneDrive\\Desktop\\Facultate\\Semestrul5\\PPD\\Labs\\Lab5\\Lab5\\src\\data\\polinoame\\polinom" + i + ".txt"))) {
                List<Integer> grade = generateRandomGrades();
                List<Integer> coeficienti = generateRandomCoeficienti();
                for (int j = 0; j < nrMonoame; j++) {
                    bw.write(grade.get(j) + " " + coeficienti.get(j));
                    bw.newLine();
                }
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
    }

    static void writeData(Lista lista, String filename) {
        try (BufferedWriter bw = new BufferedWriter(new FileWriter(filename))) {
            Nod currentNode = lista.head.nextNode;
            while (currentNode.grad != Integer.MAX_VALUE) {
                bw.write(currentNode.getGrad() + " " + currentNode.getCoeficient());
                bw.newLine();
                currentNode = currentNode.nextNode;
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static void fisiereEgale(String path1, String path2) {
        List<Nod> lista1 = new ArrayList<>();
        List<Nod> lista2 = new ArrayList<>();
        try {
            File myObj = new File(path1);
            Scanner myReader = new Scanner(myObj);
            while (myReader.hasNext()) {
                String[] linie = myReader.nextLine().split(" ");
                int grad = Integer.parseInt(linie[0]);
                int coef = Integer.parseInt(linie[1]);
                lista1.add(new Nod(coef, grad));
            }
            myReader.close();
        } catch (FileNotFoundException e) {
            System.out.println("An error occurred.");
            e.printStackTrace();
        }

        try {
            File myObj = new File(path2);
            Scanner myReader = new Scanner(myObj);
            while (myReader.hasNext()) {
                String[] linie = myReader.nextLine().split(" ");
                int grad = Integer.parseInt(linie[0]);
                int coef = Integer.parseInt(linie[1]);
                lista2.add(new Nod(coef, grad));
            }
            myReader.close();
        } catch (FileNotFoundException e) {
            System.out.println("An error occurred.");
            e.printStackTrace();
        }

        assert lista1.equals(lista2);
    }

    public static void secvential() {
        Lista polinomSuma = new Lista();
        long startTime = System.nanoTime();
        for (int i = 1; i <= nrPolinoame; i++) {
            try {
                File myObj = new File("C:\\Users\\miamu\\OneDrive\\Desktop\\Facultate\\Semestrul5\\PPD\\Labs\\Lab5\\Lab5\\src\\data\\polinoame\\polinom" + i + ".txt");
                Scanner myReader = new Scanner(myObj);
                while (myReader.hasNext()) {
                    String[] linie = myReader.nextLine().split(" ");
                    int grad = Integer.parseInt(linie[0]);
                    int coef = Integer.parseInt(linie[1]);
                    polinomSuma.insert(coef, grad);
                }

            } catch (FileNotFoundException e) {
                System.out.println("An error occurred.");
                e.printStackTrace();
            }
        }
        long endTime = System.nanoTime();
        System.out.println((double) (endTime - startTime) / 1E6);
        writeData(polinomSuma, "C:\\Users\\miamu\\OneDrive\\Desktop\\Facultate\\Semestrul5\\PPD\\Labs\\Lab5\\Lab5\\src\\data\\rezultat.txt");
    }

    public static class PC {
        final Queue<Nod> coada = new LinkedList<>();
        int threadsDone = 0;

        public void readMonoms(int start, int end) {
            for (int i = start; i < end; i++) {
                try {
                    File myObj = new File("C:\\Users\\miamu\\OneDrive\\Desktop\\Facultate\\Semestrul5\\PPD\\Labs\\Lab5\\Lab5\\src\\data\\polinoame\\polinom" + i + ".txt");
                    Scanner myReader = new Scanner(myObj);
                    while (myReader.hasNext()) {
                        String[] linie = myReader.nextLine().split(" ");
                        int grad = Integer.parseInt(linie[0]);
                        int coef = Integer.parseInt(linie[1]);
                        Nod monom = new Nod(coef, grad);
                        synchronized (coada) {
                            coada.add(monom);
                            coada.notify();
                        }
                    }
                } catch (FileNotFoundException e) {
                    System.out.println("An error occurred.");
                    e.printStackTrace();
                }
            }
            synchronized (this) {
                synchronized (coada) {
                    threadsDone++;
                    if (threadsDone == p1) {
                        coada.notifyAll();
                    }
                }
            }
        }

        public void calculate(Lista polinomSuma) throws InterruptedException {
            while (true) {
                synchronized (coada) {
                    while (coada.isEmpty() && threadsDone < p1) {
                        coada.wait();
                    }
                    if(coada.isEmpty() && threadsDone == p1){
                        break;
                    } else{
                        if (!coada.isEmpty()) {
                            Nod monom = coada.poll();
                            polinomSuma.insert(monom.getCoeficient(), monom.getGrad());
                        }
                    }
                }
            }
        }
    }

    public static void threads() throws InterruptedException {
        Lista polinomSuma = new Lista();

        PC pc = new PC();
        long startTime = System.nanoTime();
        Thread[] t = new Thread[p];
        int start = 1, end;
        int cat = nrPolinoame / p1, rest = nrPolinoame % p1;
        for (int i = 0; i < p1; i++) {
            if (rest > 0) {
                end = start + cat + 1;
                rest--;
            } else {
                end = start + cat;
            }
            int finalStart = start;
            int finalEnd = end;
            t[i] = new Thread(() -> pc.readMonoms(finalStart, finalEnd));
            start = end;
        }

        for (int i = p1; i < p; i++) {
            t[i] = new Thread(() -> {
                try {
                    pc.calculate(polinomSuma);
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            });
        }

        for (int i = 0; i < p; i++) {
            t[i].start();
        }
        for (int i = 0; i < p; i++) {
            t[i].join();
        }
        long endTime = System.nanoTime();
        System.out.println((double) (endTime - startTime) / 1E6);
        String path1 = "C:\\Users\\miamu\\OneDrive\\Desktop\\Facultate\\Semestrul5\\PPD\\Labs\\Lab5\\Lab5\\src\\data\\rezultat.txt";
        String path2 = "C:\\Users\\miamu\\OneDrive\\Desktop\\Facultate\\Semestrul5\\PPD\\Labs\\Lab5\\Lab5\\src\\data\\rezultat2.txt";
        writeData(polinomSuma, path2);
        fisiereEgale(path1, path2);
    }

    public static void main(String[] args) throws InterruptedException {
        p = Integer.parseInt(args[0]);
        p1 = Integer.parseInt(args[1]);
        nrPolinoame = Integer.parseInt(args[2]);
        gradMaxim = Integer.parseInt(args[3]);
        nrMonoame = Integer.parseInt(args[4]);
        int mod = Integer.parseInt(args[5]);
        boolean generate = Boolean.parseBoolean(args[6]);

        if (generate) {
            generateData();
        }

        switch (mod) {
            case 1 -> secvential();
            case 2 -> threads();
        }
    }
}
