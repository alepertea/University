package com.company;

import java.io.*;
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

class Node {

    private int coeff, exp;
    private Node next;

    public Node(int coeff, int exp) {
        this.coeff = coeff;
        this.exp = exp;
        this.next = null;
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
        if (isEmpty()) {
            this.front = element;
        }
        this.elements.add(element);
        this.rear = element;
        this.size++;
    }

    /**
     * Utility function to dequeue the front element.
     */
    public void dequeue() {
        if (isEmpty()) {
            System.out.println("Queue is already empty!");
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

    private Node head;
    private int size;

    /**
     * Constructor that initializes the head node to null.
     */
    public MyLinkedList() {
        this.head = null;
        this.size = 0;
    }

    /**
     * Utility function to add a node to the linked list.
     * The element is added so that the list remains ordered.
     * @param node the element to be inserted.
     */
    public void insert(Node node) {
        Node iterator = this.head;
        if(this.head == null) {
            this.head = node;
            return;
        }
        if (this.head.getExp() < node.getExp()) {
            node.setNext(this.head);
            this.head = node;
            this.size++;
            return;
        }
        while (iterator.getNext() != null && iterator.getNext().getExp() > node.getExp()) {
            iterator = iterator.getNext();
        }
        node.setNext(iterator.getNext());
        iterator.setNext(node);
        this.size++;
    }

    /**
     * Utility function to add a value to the coefficient of an existing node.
     * @param node the element to be added
     */
    public void add(Node node) {
        if (this.get(node.getExp()) == null) {
            this.insert(node);
            return;
        }
        Node iterator = this.head;
        if (this.head == null) {
            return;
        }
        while (iterator.getNext() != null && iterator.getExp() != node.getExp()){
            iterator = iterator.getNext();
        }
        iterator.setCoeff(iterator.getCoeff() + node.getCoeff());
    }

    /**
     * Utility function that returns the node by its exponent.
     * @param exponent a positive number, the exponent of the node we are searching for.
     * @return the node to be retrieved.
     */
    public Node get(int exponent) {
        if (this.head == null) {
            return null;
        }
        Node iterator = this.head;
        while (iterator != null && iterator.getExp() != exponent){
            iterator = iterator.getNext();
        }
        return iterator;
    }

    /**
     * Utility function to return the size of the list.
     * @return the number of elements in the linked list.
     */
    public int size() {
        return this.size;
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
            BufferedWriter writer = new BufferedWriter(new FileWriter("D:\\Facultate\\Anul3\\Sem1\\PPD\\Laboratoare\\Lab4\\Rezolvare\\Secvential\\src\\data\\output.txt"));
            writer.write(String.valueOf(result));
            writer.close();
        }catch (IOException e) {
            e.printStackTrace();
        }
    }
}

public class Main {

    private static void readPolynomials(MyQueue queue, int numberOfFiles) {
        File myObj;
        Scanner myReader;
        String templateFilename = "D:\\Facultate\\Anul3\\Sem1\\PPD\\Laboratoare\\Lab4\\Rezolvare\\Secvential\\src\\data\\P?.txt";
        try{
            for (int i = 1; i <= numberOfFiles; i++) {
                String tmpFilename = templateFilename.replace('?', String.valueOf(i).charAt(0));
                myObj = new File(tmpFilename);
                myReader = new Scanner(myObj);

                while (myReader.hasNextLine()) {
                    String data = myReader.nextLine();
                    int coeff = Integer.parseInt(data.split(" ")[0]);
                    int exp = Integer.parseInt(data.split(" ")[1]);
                    Node node = new Node(coeff, exp);
                    queue.enqueue(node);
                }
            }
        }catch (FileNotFoundException e){
            System.out.println("An error occurred while reading: ");
            e.printStackTrace();
        }
    }

    public static void main(String[] args) {

        long startTime = System.nanoTime();

        MyLinkedList list = new MyLinkedList();
        MyQueue queue = new MyQueue();
        readPolynomials(queue, 5);

        while (!queue.isEmpty()) {
            Node node = queue.peek();
            list.add(node);
            queue.dequeue();
        }

        list.writeToFile();

        long endTime = System.nanoTime();

        System.out.println((double)(endTime - startTime) / 1E6);
    }
}
