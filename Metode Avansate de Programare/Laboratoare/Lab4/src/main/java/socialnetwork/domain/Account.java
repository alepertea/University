package socialnetwork.domain;

public class Account extends Entity<String>
{
    private String username;
    private String password;
    private Long userID;

    public Account(String username, String password, Long userID)
    {
        this.username = username;
        this.password = password;
        this.userID = userID;
    }

    public String getUsername() { return this.username; }

    public void setUsername(String username) { this.username = username; }

    public String getPassword() { return this.password; }

    public void setPassword(String password) { this.password = password; }

    public Long getUserID() { return this.userID; }

    public void setUserID(Long userID) { this.userID = userID; }
}
