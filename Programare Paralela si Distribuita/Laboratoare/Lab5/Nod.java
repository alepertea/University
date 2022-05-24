import java.util.Objects;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class Nod {
    int coeficient;
    int grad;
    volatile Nod nextNode;
    private Lock lock = new ReentrantLock();

    public Nod(int coeficient, int grad) {
        this.coeficient = coeficient;
        this.grad = grad;
        this.nextNode = null;
    }

    public int getCoeficient() {
        return coeficient;
    }

    public int getGrad() {
        return grad;
    }

    public void lock() {
        this.lock.lock();
    }

    public void unlock() {
        this.lock.unlock();
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (!(o instanceof Nod)) return false;
        Nod nod = (Nod) o;
        return coeficient == nod.coeficient && grad == nod.grad;
    }

    @Override
    public int hashCode() {
        return Objects.hash(coeficient, grad);
    }
}