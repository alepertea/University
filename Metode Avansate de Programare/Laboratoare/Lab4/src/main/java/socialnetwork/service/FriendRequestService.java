package socialnetwork.service;

import socialnetwork.domain.*;
import socialnetwork.domain.validators.Validator;
import socialnetwork.repository.Repository;

import java.time.LocalDateTime;
import java.util.HashMap;
import java.util.Map;
import java.util.stream.StreamSupport;

public class FriendRequestService
{
    private final Repository<Tuple<Long,Long>, FriendRequest> friendRequestRepository;
    private final Repository<Tuple<Long,Long>, Friendship> friendshipRepository;
    private final Repository<Long, User> userRepository;
    private final Validator<FriendRequest> friendRequestValidator;


    public FriendRequestService(Repository<Tuple<Long,Long>, FriendRequest> friendRequestRepository, Repository<Long, User> userRepository, Repository<Tuple<Long,Long>, Friendship> friendshipRepository, Validator<FriendRequest> friendRequestValidator)
    {
        this.friendRequestRepository = friendRequestRepository;
        this.friendshipRepository = friendshipRepository;
        this.userRepository = userRepository;
        this.friendRequestValidator = friendRequestValidator;
    }

    public FriendRequest addFriendRequest(FriendRequest friendRequest)
    {
        this.friendRequestValidator.validate(friendRequest);

        long from = friendRequest.getFrom();
        long to = friendRequest.getTo();

        User secondFriend = this.userRepository.findOne(to);

        String errorMessage = "";
        if(secondFriend == null)
            errorMessage += ">> Cannot find user with id " + to + "!";

        FriendRequest f = this.friendRequestRepository.findOne(new Tuple<>(from, to));
        if(f != null && f.getStatus() != Status.REJECTED)
            errorMessage += ">> Cannot send friend request!";
        f = this.friendRequestRepository.findOne(new Tuple<>(to, from));
        if(f != null && f.getStatus() != Status.REJECTED)
            errorMessage += ">> Cannot send friend request!";

        if(errorMessage.compareTo("") != 0)
        {
            throw new ServiceException(errorMessage);
        }

        return this.friendRequestRepository.save(friendRequest);
    }

    public Map<User, LocalDateTime> getAll(long id)
    {
        Map<User, LocalDateTime> dto = new HashMap<>();

        Iterable<FriendRequest> iterable = this.friendRequestRepository.findAll();
        StreamSupport.stream(iterable.spliterator(), false)
                .filter(x -> (x.getId().getRight().equals(id)))
                .filter(x -> (x.getStatus() == Status.PENDING))
                .forEach( friendRequest -> {
                            User friend;
                            if(friendRequest.getId().getLeft().equals(id))
                                friend = this.userRepository.findOne(friendRequest.getId().getRight());
                            else
                                friend = this.userRepository.findOne(friendRequest.getId().getLeft());
                            dto.put(friend, friendRequest.getDate());
                        }
                );

        return dto;
    }

    public void accept(long from, long to)
    {
        FriendRequest friendRequest = this.friendRequestRepository.findOne(new Tuple<>(from, to));

        if(friendRequest == null)
            throw new ServiceException("There is no friend request from user with ID " + from + "!");
        if(friendRequest.getStatus() != Status.PENDING)
            throw new ServiceException("Can't accept this friend request!");

        friendRequest.setStatus(Status.APPROVED);
        friendRequest.setDate(LocalDateTime.now());

        this.friendRequestRepository.update(friendRequest);

        Friendship friendship = new Friendship();
        friendship.setId(new Tuple<>(from, to));

        this.friendshipRepository.save(friendship);
    }

    public void reject(long from, long to)
    {
        FriendRequest friendRequest = this.friendRequestRepository.findOne(new Tuple<>(from, to));

        if(friendRequest == null)
            throw new ServiceException("There is no friend request from user with ID " + from + "!");
        if(friendRequest.getStatus() != Status.PENDING)
            throw new ServiceException("Can't accept this friend request!");

        this.friendRequestRepository.delete(new Tuple<>(from, to));
    }

    public void remove(long from, long to)
    {
        FriendRequest friendRequest = this.friendRequestRepository.findOne(new Tuple<>(from, to));

        if(friendRequest == null)
            throw new ServiceException("You are not a friend to user with ID " + from + "!");
        if(friendRequest.getStatus() != Status.APPROVED)
            throw new ServiceException("Friendship does not exist!");

        this.friendRequestRepository.delete(new Tuple<>(from, to));
    }
}
