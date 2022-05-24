package com.company;

public class Main {
    public static void main(String[] args) throws InterruptedException {
        Cont cont = new Cont(0);
        System.out.println(cont.getSoldRON());

        int p = 10;
        Thread[] t = new Worker[p];

        for (int i = 0; i < p; i++) {
            t[i] = new Worker(cont);
            t[i].start();
        }
        for (int i = 0; i < p; i++) {
            t[i].join();
        }

        System.out.println(cont.getSoldRON());
    }
}
