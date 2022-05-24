package com.company;

public class TS {
    private int size;
    private int maxSize;
    private Pair[] dict;

    public TS(int maxSize) {
        this.size = 0;
        this.maxSize = maxSize;
        this.dict = new Pair[maxSize];
    }

    public int size() {
        return this.size;
    }

    public Pair get(int index) {
        return this.dict[index];
    }

    public Pair find(String atom) {
        for(int i = 0; i < this.size; i++){
            if (this.dict[i].getSimbol().equals(atom))
                return this.dict[i];
        }
        return null;
    }

    private void resize() {
        Pair[] newDict = new Pair[2 * this.maxSize];
        if (this.maxSize >= 0)
            System.arraycopy(this.dict, 0, newDict, 0, this.maxSize);
        this.maxSize = 2 * this.maxSize;
        this.dict = newDict;
    }

    void add(Pair element, int position) {
        if (size == maxSize) {
            resize();
        }
        for (int i = this.size; i > position; i--) {
            this.dict[i] = this.dict[i - 1];
        }
        this.dict[position] = element;
        this.size++;
    }
}
