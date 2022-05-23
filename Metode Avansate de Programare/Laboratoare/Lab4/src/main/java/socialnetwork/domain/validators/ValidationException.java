package socialnetwork.domain.validators;

import socialnetwork.MyException;

public class ValidationException extends MyException
{
    public ValidationException(String message)
    {
        super(message);
    }
}
