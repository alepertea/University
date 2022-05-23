package socialnetwork.event;

import socialnetwork.domain.FriendRequest;

public class FriendRequestEvent implements Event
{
    private ChangeEventType type;
    private FriendRequest friendRequest, oldFriendRequest;

    public FriendRequestEvent(ChangeEventType type, FriendRequest friendRequest)
    {
        this.type = type;
        this.friendRequest = friendRequest;
    }
    public FriendRequestEvent(ChangeEventType type, FriendRequest friendRequest, FriendRequest oldFriendRequest)
    {
        this.type = type;
        this.friendRequest = friendRequest;
        this.oldFriendRequest = oldFriendRequest;
    }

    public ChangeEventType getType() {
        return this.type;
    }

    public FriendRequest getFriendRequest() {
        return this.friendRequest;
    }

    public FriendRequest getOldFriendRequest() {
        return this.oldFriendRequest;
    }
}
