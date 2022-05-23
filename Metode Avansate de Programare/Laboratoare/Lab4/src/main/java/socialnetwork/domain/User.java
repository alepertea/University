package socialnetwork.domain;

import java.util.ArrayList;
import java.util.List;
import java.util.Objects;

public class User extends Entity<Long>
{
    private String firstName;
    private String lastName;
    private String email;
    private List<User> friends;

    public User(String firstName, String lastName, String email)
    {
        this.firstName = firstName;
        this.lastName = lastName;
        this.email = email;
        this.friends = new ArrayList<>();
    }

    public String getFirstName()
    {
        return this.firstName;
    }

    public void setFirstName(String firstName)
    {
        this.firstName = firstName;
    }

    public String getLastName()
    {
        return this.lastName;
    }

    public void setLastName(String lastName)
    {
        this.lastName = lastName;
    }

    public String getEmail() { return this.email; }

    public void setEmail(String email) { this.email = email; }

    public List<User> getFriends()
    {
        return this.friends;
    }

    public void addFriend(User friend) { this.friends.add(friend); }

    public void removeFriend(User friend) { this.friends.remove(friend); }

    @Override
    public String toString()
    {
        return "Utilizator{" +
                "ID=" + getId() +
                ", firstName='" + firstName + '\'' +
                ", lastName='" + lastName + '\'' +
                ", email=" + email + '\'' +
                ", friends=" + getFriendList() +
                '}';
    }

    public String getFriendList()
    {
        String line = "[ ";

        if(this.friends.size() == 0)
        {
            line += "none ]";
            return line;
        }

        for(User user : this.friends)
        {
            line += user.getFirstName() + ";";
        }

        line += " ]";
        return line;
    }

    @Override
    public boolean equals(Object o)
    {
        if (this == o)
            return true;
        if (!(o instanceof User))
            return false;
        User that = (User) o;
        return getFirstName().equals(that.getFirstName()) &&
                getLastName().equals(that.getLastName()) &&
                getEmail().equals(that.getEmail()) &&
                getFriends().equals(that.getFriends());
    }

    @Override
    public int hashCode()
    {
        return Objects.hash(getFirstName(), getLastName(), getEmail(), getFriends());
    }
}