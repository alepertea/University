package socialnetwork.event;

import socialnetwork.domain.User;

public class UserEvent implements Event {

    private ChangeEventType type;
    private User user, oldUser;

    public UserEvent(ChangeEventType type, User user) {
        this.type = type;
        this.user = user;
    }
    public UserEvent(ChangeEventType type, User user, User oldUser) {
        this.type = type;
        this.user = user;
        this.oldUser = oldUser;
    }

    public ChangeEventType getType() {
        return type;
    }

    public User getUser() {
        return user;
    }

    public User getOldUser() {
        return oldUser;
    }

}
