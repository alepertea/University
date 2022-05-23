package socialnetwork.service;

import socialnetwork.MyException;

public class ServiceException extends MyException
{
    public ServiceException(String message)
    {
        super(message);
    }
}
