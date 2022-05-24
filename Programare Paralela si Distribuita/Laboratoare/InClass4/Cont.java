package com.company;

import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class Cont {
    final Lock lockRON = new ReentrantLock();
//    final Lock lockEUR = new ReentrantLock();
//    final Object lR = new Object();
//    final Object lE = new Object();
    private int soldRON = 0;
//    private int soldEUR = 0;

    Cont(int sold) {
        this.soldRON = sold;
    }

//    synchronized void addRON() {  // solutia 1, simpla, dar cu granularitatea cea mai mare - secventializeaza intregul cod
    void addRON() {
        // synchronized - cand thread-ul vede acest keyword, seteaza mutex-ul, astfel incat urmatorul sa nu mai poata intra
        synchronized(lockRON) {          // solutia 2, mai granulara
            for (int i = 0; i < 1000; i++) {
//                synchronized (this) { soldRON++; }  // e costisitor sa tot facem synchronized in for
                soldRON++;
            }
        }
//        lockRON.lock();
////        lockEUR.lock();
//        for (int i = 0; i < 1000; i++) {
//            soldRON++;
//        }
//        lockRON.unlock();
    }

    void decreaseRON() {
//        lockRON.lock();
//        lockEUR.lock();
//        synchronized (this) {
            for (int i = 0; i < 1000; i++) {
                soldRON -= 1;
            }
//        }
    }

    public int getSoldRON() {
        return soldRON;
    }
}