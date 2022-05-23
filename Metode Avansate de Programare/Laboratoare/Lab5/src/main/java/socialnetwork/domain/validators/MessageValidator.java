package socialnetwork.domain.validators;

import socialnetwork.domain.Message;

public class MessageValidator implements Validator<Message>
{
    @Override
    public void validate(Message entity) throws ValidationException
    {
        String errorMessage = "";

        if(entity.getMessage().compareTo("") == 0)
            errorMessage += "Message cannot be empty!";

        for(Long recipient : entity.getTo())
        {
            if(recipient.equals(entity.getFrom()))
            {
                errorMessage += "You cannot send a message to yourself!";
                break;
            }
        }

        if(errorMessage.compareTo("") != 0)
            throw new ValidationException(errorMessage);
    }
}
