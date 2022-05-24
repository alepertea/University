package model;

public class Participant extends Entity<String> implements Comparable {
    private String name;
    private int age;

    public Participant(String name, int age) {
        this.setId(name);
        this.name = name;
        this.age = age;
    }

    public String getName() { return name; }

    public void setName(String name) {
        this.name = name;
    }

    public int getAge() {
        return age;
    }

    public void setAge(int age) {
        this.age = age;
    }

    @Override
    public int compareTo(Object o) {
        Participant other = (Participant)o;
        return Integer.compare(this.age, other.age);
    }

    @Override
    public String toString() {
        return this.name + " | " + this.age;
    }
}
