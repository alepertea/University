package model;

public class Track extends Entity<String> implements Comparable {
    private String name;
    private int minimumAge;
    private int maximumAge;

    public Track(String name, int minimumAge, int maximumAge) {
        this.setId(name);
        this.name = name;
        this.minimumAge = minimumAge;
        this.maximumAge = maximumAge;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) { this.name = name; }

    public int getMinimumAge() {
        return minimumAge;
    }

    public void setMinimumAge(int minimumAge) {
        this.minimumAge = minimumAge;
    }

    public int getMaximumAge() {
        return maximumAge;
    }

    public void setMaximumAge(int maximumAge) {
        this.maximumAge = maximumAge;
    }

    @Override
    public int compareTo(Object o) {
        Track other = (Track)o;
        if(this.name.equals(other.name))
            return 0;
        if(this.name.compareTo(other.name) < 0)
            return -1;
        return 1;
    }

    @Override
    public String toString() {
        return this.name + " | min age: " + this.minimumAge + " | max age: " + this.maximumAge;
    }
}
