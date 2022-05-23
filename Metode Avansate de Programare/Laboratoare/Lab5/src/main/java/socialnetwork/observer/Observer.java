package socialnetwork.observer;

import socialnetwork.event.Event;

public interface Observer<E extends Event> {
    void update(E e);
}
