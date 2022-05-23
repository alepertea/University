package socialnetwork;

public class MyException extends RuntimeException
{
    private String message;

    public MyException(String message)
    {
        this.message = message;
    }

    public String getMessage()
    {
        return this.message;
    }
}
