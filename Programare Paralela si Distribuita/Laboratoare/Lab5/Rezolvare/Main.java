package com.company;

import java.io.*;
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

class Node {

    private int coeff, exp;
    private Node next;

    private Lock lock = new ReentrantLock();

    public Node(int coeff, int exp) {
        this.coeff = coeff;
        this.exp = exp;
        this.next = null;
    }

    public void lock() {
        this.lock.lock();
    }

    public void unlock() {
        this.lock.unlock();
    }

    public int getCoeff() { return coeff; }

    public void setCoeff(int coeff) { this.coeff = coeff; }

    public int getExp() { return exp; }

    public void setExp(int exp) { this.exp = exp; }

    public Node getNext() { return next; }

    public void setNext(Node next) { this.next = next; }

    @Override
    public String toString() {
        return this.coeff + "x^" + this.exp;
    }
}

class MyQueue {

    private List<Node> elements;
    private Node front;
    private Node rear;
    private int size;

    /**
     * Constructor to initialize a queue.
     */
    public MyQueue() {
        this.elements = new ArrayList<>();
        this.front = null;
        this.rear = null;
        this.size = 0;
    }

    /**
     * Utility function to return the front element of the queue.
     * @return the front element of the queue
     */
    public Node peek() {
        return this.front;
    }

    /**
     * Utility function to add a node to the queue.
     * @param element node to be added to the queue
     */
    public void enqueue(Node element) {
        while (isEmpty()) {
            this.front = element;
        }
        this.elements.add(element);
        notify();
        this.rear = element;
        this.size++;
    }

    /**
     * Utility function to dequeue the front element.
     */
    public synchronized void dequeue() {
        if (isEmpty()) {
            return;
        }
        if (this.size == 1) {
            this.front = null;
        }
        else {
            this.front = this.elements.get(1);
        }
        this.elements.remove(0);
        this.size--;
    }

    /**
     * Utility function to check if the queue is empty or not.
     * @return true, if the queue is empty, false otherwise
     */
    public boolean isEmpty() {
        return (this.size == 0);
    }
}

class MyLinkedList {

    private final Node head;

    /**
     * Constructor that initializes the head node to null.
     */
    public MyLinkedList() {
        Node min = new Node(-1, Integer.MIN_VALUE);
        Node max = new Node(-1, Integer.MAX_VALUE);
        min.setNext(max);
        this.head = min;
    }

    /**
     * Utility function to add a node to the linked list.
     * The element is added so that the list remains ordered.
     * @param node the element to be inserted.
     */
    public void insert(Node node) {

        Node precedent, current;

        precedent = this.head;
        precedent.lock();
        current = precedent.getNext();
        current.lock();

        try {
            while (current.getExp() < node.getExp()) {
                precedent.unlock();
                precedent = current;
                current = current.getNext();
                current.lock();
            }
            if (current.getExp() == node.getExp()) {
                current.setCoeff(current.getCoeff() + node.getCoeff());
                if (current.getCoeff() == 0) {
                    this.remove(current);
                }
            }
            else {
                node.setNext(current);
                precedent.setNext(node);
            }
        } finally {
            current.unlock();
            precedent.unlock();
        }
    }

    /**
     * Utility function that removes a node from the list.
     * @param node the node to be removed.
     */
    public void remove(Node node) {
        Node precedent, current;

        precedent = this.head;
        precedent.lock();
        current = precedent.getNext();
        current.lock();
        try {
            while (current.getExp() < node.getExp()) {
                precedent.unlock();
                precedent = current;
                current = current.getNext();
                current.lock();
            }
            if (current.getExp() == node.getExp()) {
                precedent.setNext(current.getNext());
            }
        } finally {
            current.unlock();
            precedent.unlock();
        }
    }

    /**
     * Utility function to write the list to the output file.
     * Output file: D:\Facultate\Anul3\Sem1\PPD\Laboratoare\Lab4\Rezolvare\Secvential\src\data\output.txt
     */
    public void writeToFile() {
        Node iterator = this.head;
        StringBuilder result = new StringBuilder();
        while(iterator.getNext() != null) {
            if (iterator.getCoeff() != 0) {
                result.append(iterator.getCoeff()).append("x^").append(iterator.getExp()).append(" + ");
            }
            iterator = iterator.getNext();
        }
        result.append(iterator.getCoeff()).append("x^").append(iterator.getExp());

        try {
            BufferedWriter writer = new BufferedWriter(new FileWriter("D:\\Facultate\\Anul3\\Sem1\\PPD\\Laboratoare\\Lab5\\Rezolvare\\src\\data\\output.txt"));
            writer.write(String.valueOf(result));
            writer.close();
        }catch (IOException e) {
            e.printStackTrace();
        }
    }
}

class Producer_Consumer {
    private static final MyQueue queue = new MyQueue();
    private static final int threadsDone = 0;
    private static int p1 = 0;
    private static int p2 = 0;


    public Producer_Consumer(int p1, int p2) {
        Producer_Consumer.p1 = p1;
        Producer_Consumer.p2 = p2;
    }

    public void readPolynomials(int start, int end) {
        File myObj;
        Scanner myReader;
        int threadsDone = 0;

        String templateFilename = "D:\\Facultate\\Anul3\\Sem1\\PPD\\Laboratoare\\Lab5\\Rezolvare\\src\\data\\P?.txt";
        try{
            for (int i = start; i < end; i++) {
                String tmpFilename = templateFilename.replace('?', String.valueOf(i).charAt(0));
                myObj = new File(tmpFilename);
                myReader = new Scanner(myObj);

                while (myReader.hasNextLine()) {
                    String data = myReader.nextLine();
                    int coeff = Integer.parseInt(data.split(" ")[0]);
                    int exp = Integer.parseInt(data.split(" ")[1]);
                    Node node = new Node(coeff, exp);

                    synchronized (queue) {
                        queue.enqueue(node);
                        queue.notify();
                    }
                }
            }
        }catch (FileNotFoundException e){
            System.out.println("An error occurred while reading: ");
            e.printStackTrace();
        }
        synchronized (this) {
            synchronized (queue) {
                threadsDone++;
                if (threadsDone == p1) {
                    queue.notifyAll();
                }
            }
        }
    }

    public void addPolynomials(MyLinkedList list) throws InterruptedException {

        while (true) {
            synchronized (queue) {
                while (queue.isEmpty() && threadsDone < p1) {
                    queue.wait();
                }
            }
            if (queue.isEmpty() && threadsDone == p1) {
                break;
            }
            else
                if (!queue.isEmpty()) {
                    Node node = queue.peek();
                    queue.dequeue();
                    list.insert(node);

                }
        }
    }
}

public class Main {

    public static void main(String[] args) throws InterruptedException {

        long startTime = System.nanoTime();

        int noPolynomials = 5;
        int p = 4;
        int p1 = 2;
        int p2 = 3;

        Thread [] threads = new Thread[p];
        MyLinkedList list = new MyLinkedList();
        Producer_Consumer pc = new Producer_Consumer(p1, p2);
        int start = 1, end;
        int chunk = noPolynomials / p1, rest = noPolynomials % p1;

        for (int i = 0; i < p1; i++) {
            if (rest > 0) {
                end = start + chunk + 1;
                rest--;
            }
            else {
                end = start + chunk;
            }
            int finalStart = start;
            int finalEnd = end;
            threads[i] = new Thread(() -> pc.readPolynomials(finalStart, finalEnd));
            start = end;
        }

        for (int i = p1; i < p; i++) {
            threads[i] = new Thread(() -> {
                try {
                    pc.addPolynomials(list);
                }catch (InterruptedException e) {
                    e.printStackTrace();
                }
            });
        }

        for(int i = 0; i < p; i++) {
            threads[i].start();
        }

        for(int i = 0; i < p; i++) {
            threads[i].join();
        }

        list.writeToFile();

        long endTime = System.nanoTime();

        System.out.println((double)(endTime - startTime) / 1E6);
    }
}
