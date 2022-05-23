package socialnetwork.domain.validators;

import socialnetwork.domain.FriendRequest;

public class FriendRequestValidator implements Validator<FriendRequest>
{
    @Override
    public void validate(FriendRequest entity) throws ValidationException
    {
        long firstFriend = entity.getFrom();
        long secondFriend = entity.getTo();
        if(secondFriend == firstFriend)
        {
            throw new ValidationException("ID's cannot be the same!");
        }
    }
}
