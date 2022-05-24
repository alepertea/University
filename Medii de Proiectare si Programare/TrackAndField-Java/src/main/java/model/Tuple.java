package model;

import java.util.Objects;

/**
 * Define a Tuple o generic type entities
 * @param <E1> - tuple first entity type
 * @param <E2> - tuple second entity type
 */
public class Tuple<E1 extends Comparable, E2 extends Comparable> {
    private E1 e1;
    private E2 e2;

    public Tuple(E1 e1, E2 e2) {
        this.e1 = e1;
        this.e2 = e2;
    }

    public E1 getLeft() {
        return e1;
    }

    public void setLeft(E1 e1) {
        this.e1 = e1;
    }

    public E2 getRight() {
        return e2;
    }

    public void setRight(E2 e2) {
        this.e2 = e2;
    }

    @Override
    public String toString() {
        return "" + e1 + "," + e2;
    }

    @Override
    public boolean equals(Object obj) {
        return (this.e1.equals(((Tuple) obj).e1) && this.e2.equals(((Tuple) obj).e2))
                || (this.e1.equals(((Tuple) obj).e2) && this.e2.equals(((Tuple) obj).e1));
    }

    @Override
    public int hashCode() {
        if (e1.compareTo(e2) < 0)
            return Objects.hash(e1, e2);
        else
            return Objects.hash(e2, e1);
    }
}
