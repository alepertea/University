package socialnetwork.service;

import socialnetwork.domain.FriendRequest;
import socialnetwork.domain.Friendship;
import socialnetwork.domain.Tuple;
import socialnetwork.domain.User;
import socialnetwork.domain.validators.Validator;
import socialnetwork.event.ChangeEventType;
import socialnetwork.event.FriendshipEvent;
import socialnetwork.observer.Observable;
import socialnetwork.observer.Observer;
import socialnetwork.repository.Repository;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class FriendshipService implements Observable<FriendshipEvent>
{
    private final Repository<Long, User> userRepository;
    private final Repository<Tuple<Long, Long>, FriendRequest> friendRequestRepository;
    private final Repository<Tuple<Long, Long>, Friendship> friendshipRepository;
    private final Validator<Friendship> friendshipValidator;

    private List<Observer<FriendshipEvent>> observers;

    public FriendshipService(Repository<Long, User> userRepository, Repository<Tuple<Long, Long>, FriendRequest> friendRequestRepository, Repository<Tuple<Long, Long>, Friendship> friendshipRepository, Validator<Friendship> friendshipValidator)
    {
        this.userRepository = userRepository;
        this.friendRequestRepository = friendRequestRepository;
        this.friendshipRepository = friendshipRepository;
        this.friendshipValidator = friendshipValidator;
        this.observers = new ArrayList<>();
    }

    public Friendship removeFriendship(Friendship friendship) throws ServiceException
    {
        this.friendshipValidator.validate(friendship);

        long firstID = friendship.getId().getLeft();
        long secondID = friendship.getId().getRight();

        User firstFriend = this.userRepository.findOne(firstID);
        User secondFriend = this.userRepository.findOne(secondID);

        String errorMessage = "";
        if(firstFriend == null)
            errorMessage += "Cannot find user with id " + firstID + "!\n";
        if(secondFriend == null)
            errorMessage += "Cannot find user with id " + secondID + "!\n";

        if(errorMessage.compareTo("") != 0)
            throw new ServiceException(errorMessage);

        Friendship f = this.friendshipRepository.findOne(new Tuple<>(firstID, secondID));
        if(f != null)
        {
            this.friendshipRepository.delete(f.getId());
            this.notifyObservers(new FriendshipEvent(ChangeEventType.DELETE, f));

            this.friendRequestRepository.delete(f.getId());
            this.friendRequestRepository.delete(new Tuple<>(secondID, firstID));
            return f;
        }
        return null;
    }

    private final Map<Long, Integer> visited = new HashMap<>();

    private void DFS(User node, int nr)
    {
        visited.put(node.getId(), nr);
        for(User it : node.getFriends())
            if(visited.get(it.getId()) == 0)
                this.DFS(it, nr);
    }

    public int numberOfCommunities()
    {
        int connectedComponents = 0;

        List<User> users = new ArrayList<>();
        for(User user : userRepository.findAll())
        {
            List<User> friends = new ArrayList<>();
            for(Friendship f : this.friendshipRepository.findAll())
            {
                if(f.getId().getLeft().equals(user.getId()))
                {
                    friends.add(this.userRepository.findOne(f.getId().getRight()));
                }
                if(f.getId().getRight().equals(user.getId()))
                {
                    friends.add(this.userRepository.findOne(f.getId().getLeft()));
                }
            }
            for(User friend : friends)
            {
                user.getFriends().add(friend);
            }
            users.add(user);
        }

        for(User user : users)
            visited.put(user.getId(), 0);

        for(User user : users)
            if(visited.get(user.getId()) == 0)
            {
                connectedComponents++;
                this.DFS(user, connectedComponents);
            }

        return connectedComponents;
    }

    public List<User> getMostFriendlyCommunity()
    {
        int x = this.numberOfCommunities();
        int[] freq = new int[x + 1];
        int maxFriends = -1;
        int connectedComponents = 0;
        List<User> community = new ArrayList<>();

        for(User user:this.userRepository.findAll())
            freq[visited.get(user.getId())]++;

        for(int i = 1; i <= x; i++)
            if(freq[i] > maxFriends)
            {
                maxFriends = freq[i];
                connectedComponents = i;
            }

        for(User user : this.userRepository.findAll())
            if(visited.get(user.getId()) == connectedComponents)
                community.add(user);

        return community;
    }

    @Override
    public void addObserver(Observer<FriendshipEvent> e) {
        observers.add(e);
    }

    @Override
    public void removeObserver(Observer<FriendshipEvent> e) {
        observers.remove(e);
    }

    @Override
    public void notifyObservers(FriendshipEvent t) {
        observers.forEach(x->x.update(t));
    }
}
