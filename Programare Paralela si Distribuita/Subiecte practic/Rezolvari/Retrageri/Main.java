package com.company;

import java.util.ArrayList;
import java.util.List;
import java.util.Random;
import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

enum Transaction {
    EUR_DEPOSIT, EUR_WITHDRAW, RON_DEPOSIT, RON_WITHDRAW;

    public String toString() {
        if (this == EUR_DEPOSIT) {
            return "Euro Deposit";
        }
        if (this == EUR_WITHDRAW) {
            return "Euro Withdraw";
        }
        if (this == RON_DEPOSIT) {
            return "RON Deposit";
        }
        if (this == RON_WITHDRAW) {
            return "RON Withdraw";
        }
        return "";
    }
}

enum Currency {
    EUR, RON;

    public String toString() {
        if (this == EUR) {
            return "EUR";
        }
        if (this == RON) {
            return "RON";
        }
        return "";
    }
}

class Node {
    private final String userIndex;
    private final Currency currency;
    private final Transaction transaction;
    private final Integer tradedAmount;
    private final Integer currentAmount;

    public Node(String userIndex, Currency currency, Transaction transaction, Integer tradedAmount, Integer currentAmount) {
        this.userIndex = userIndex;
        this.currency = currency;
        this.transaction = transaction;
        this.tradedAmount = tradedAmount;
        this.currentAmount = currentAmount;
    }

    @Override
    public String toString() {
        return "Nod {" +
                "user = " + userIndex +
                ", currency = '" + currency.toString() + '\'' +
                ", transaction = '" + transaction.toString() + '\'' +
                ", tradedAmount = " + tradedAmount +
                ", currentAmount = " + currentAmount +
                '}';
    }
}

class FamilyMember extends Thread {
    private final Random rand;
    private final Lock lockEUR;
    private final Lock lockRON;
    private final Bank bank;
    private final Condition notFullRON;
    private final Condition notEmptyRON;
    private final Condition notFullEUR;
    private final Condition notEmptyEUR;

    public FamilyMember(Lock lockEUR, Condition notFullEUR, Condition notEmptyEUR, Lock lockRON, Condition notFullRON, Condition notEmptyRON, Bank bank) {
        this.lockEUR = lockEUR;
        this.lockRON = lockRON;
        this.bank = bank;
        this.notFullRON = notFullRON;
        this.notEmptyRON = notEmptyRON;
        this.notFullEUR = notFullEUR;
        this.notEmptyEUR = notEmptyEUR;
        this.rand = new Random();
    }

    @Override
    public void run() {
        for(int iteration = 0 ; iteration < 10; iteration++) {
            int randomTransaction = rand.nextInt(4);
            int tradedAmount = rand.nextInt(1000);

            switch (randomTransaction) {
                case 0: {
                    // Withdraw Euro
                    lockEUR.lock();
                    try {
                        while (bank.getEuroAmount() < tradedAmount) {
                            notEmptyEUR.await();
                        }
                        bank.withdrawEUR(tradedAmount);
                        notFullEUR.signal();
                    } catch (InterruptedException e) {
                        e.printStackTrace();
                    } finally {
                        lockEUR.unlock();
                    }
                    break;
                }
                case 1: {
                    // Deposit Euro
                    lockEUR.lock();
                    try {
                        while (bank.getEuroAmount() < 0) {
                            notFullEUR.await();
                        }
                        bank.depositEUR(tradedAmount);
                        notEmptyEUR.signal();
                    } catch (InterruptedException e) {
                        e.printStackTrace();
                    } finally {
                        lockEUR.unlock();
                    }
                    break;
                }
                case 2: {
                    // Withdraw RON
                    lockRON.lock();
                    try {
                        while (bank.getRONAmount() < tradedAmount) {
                            notEmptyRON.await();
                        }
                        bank.withdrawRON(tradedAmount);
                        notFullRON.signal();
                    } catch (InterruptedException e) {
                        e.printStackTrace();
                    } finally {
                        lockRON.unlock();
                    }
                    break;
                }
                case 3: {
                    // Deposit RON
                    lockRON.lock();
                    try {
                        while (bank.getRONAmount() < 0) {
                            notFullRON.await();
                        }
                        bank.depositRON(tradedAmount);
                        notEmptyRON.signal();
                    } catch (InterruptedException e) {
                        e.printStackTrace();
                    } finally {
                        lockRON.unlock();
                    }
                    break;
                }
                default: break;
            }

            try {
                Thread.sleep(10);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }
}

class IteratorThread extends Thread {
    private final Random rand;
    private final Lock lockEUR;
    private final Lock lockRON;
    private final Bank bank;
    private final Condition notFullRON;
    private final Condition notEmptyRON;
    private final Condition notFullEUR;
    private final Condition notEmptyEUR;

    public IteratorThread(Lock lockEUR, Condition notFullEUR, Condition notEmptyEUR, Lock lockRON, Condition notFullRON, Condition notEmptyRON, Bank bank) {
        this.lockEUR = lockEUR;
        this.lockRON = lockRON;
        this.bank = bank;
        this.notFullRON = notFullRON;
        this.notEmptyRON = notEmptyRON;
        this.notFullEUR = notFullEUR;
        this.notEmptyEUR = notEmptyEUR;
        this.rand = new Random();
    }

    @Override
    public void run() {
        while(true) {
            lockEUR.lock();
            lockRON.lock();

            for (int i = Math.max(0, bank.getTransactions().size()-5); i < bank.getTransactions().size(); i++) {
                System.out.println(bank.getTransactions().get(i));
                System.out.println("Thread: " + i);
            }

            lockEUR.unlock();
            lockRON.unlock();

            try {
                Thread.sleep(300);
            } catch (InterruptedException e) {
                System.out.println("Interruption caught!");
                break;
            }
        }
    }
}

class Bank {
    private final List<Node> transactions = new ArrayList<>();
    private Integer eurAmount;
    private Integer ronAmount;

    public Bank() {
        this.eurAmount = 99990;
        this.ronAmount = 99990;
    }

    public List<Node> getTransactions() {
        return this.transactions;
    }

    public void withdrawEUR(Integer euroAmount) {
        this.eurAmount -= euroAmount;
        this.transactions.add(new Node(Thread.currentThread().getName(), Currency.EUR, Transaction.EUR_WITHDRAW, euroAmount, this.eurAmount));
    }

    public void depositEUR(Integer amount) {
        this.eurAmount += amount;
        this.transactions.add(new Node(Thread.currentThread().getName(), Currency.EUR, Transaction.EUR_DEPOSIT, amount, this.eurAmount));
    }

    public Integer getEuroAmount() {
        return this.eurAmount;
    }

    public void withdrawRON(Integer amount) {
        this.ronAmount -= amount;
        this.transactions.add(new Node(Thread.currentThread().getName(), Currency.RON, Transaction.RON_WITHDRAW, amount, this.ronAmount));
    }

    public void depositRON(Integer amount) {
        this.ronAmount += amount;
        this.transactions.add(new Node(Thread.currentThread().getName(), Currency.RON, Transaction.RON_DEPOSIT, amount, this.ronAmount));
    }

    public Integer getRONAmount() {
        return this.ronAmount;
    }
}

public class Main {
    private static final Lock lockEUR = new ReentrantLock();
    private static final Lock lockRON = new ReentrantLock();
    private static final Condition notFullRON = lockRON.newCondition();
    private static final Condition notEmptyRON = lockRON.newCondition();
    private static final Condition notFullEUR = lockEUR.newCondition();
    private static final Condition notEmptyEUR = lockEUR.newCondition();
    private static final Bank bank = new Bank();

    public static void main(String[] args) {
        int familyMembersNo = 3;

        List<FamilyMember> familyMembers = new ArrayList<>();

        for (int i = 0; i < familyMembersNo; i++) {
            FamilyMember familyMember = new FamilyMember(lockEUR, notFullEUR, notEmptyEUR, lockRON, notFullRON, notEmptyRON, bank);
            familyMember.setName("Thread " + i);
            familyMembers.add(familyMember);
            System.out.println("Starting thread " + i + "...");
            familyMember.start();
        }

        IteratorThread it = new IteratorThread(lockEUR, notFullEUR, notEmptyEUR, lockRON, notFullRON, notEmptyRON, bank);
        it.start();

        for (int i = 0; i < familyMembersNo; i++) {
            try {
                familyMembers.get(i).join();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }

        try {
            System.out.println("Interrupting the iterator thread...");
            it.interrupt();
            it.join();
        } catch (InterruptedException e) {
            System.out.println("Iterator thread interrupted successfully!");
        }
    }
}
