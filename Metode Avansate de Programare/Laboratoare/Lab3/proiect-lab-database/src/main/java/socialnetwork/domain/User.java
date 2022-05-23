package socialnetwork.domain;

import java.util.ArrayList;
import java.util.List;
import java.util.Objects;

public class User extends Entity<Long>
{
    private String firstName;
    private String lastName;
    private List<User> friends;

    public User(String firstName, String lastName)
    {
        this.firstName = firstName;
        this.lastName = lastName;
        this.friends = new ArrayList<>();
    }

    public String getFirstName() {
        return firstName;
    }

    public void setFirstName(String firstName) {
        this.firstName = firstName;
    }

    public String getLastName() {
        return lastName;
    }

    public void setLastName(String lastName) {
        this.lastName = lastName;
    }

    public List<User> getFriends() {
        return friends;
    }

    @Override
    public String toString() {
        return "Utilizator{" +
                "firstName='" + firstName + '\'' +
                ", lastName='" + lastName + '\'' +
                ", friends=" + this.getFriendList() +
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
    public boolean equals(Object o) {
        if (this == o) return true;
        if (!(o instanceof User)) return false;
        User that = (User) o;
        return getFirstName().equals(that.getFirstName()) &&
                getLastName().equals(that.getLastName()) &&
                getFriends().equals(that.getFriends());
    }

    @Override
    public int hashCode() {
        return Objects.hash(getFirstName(), getLastName(), getFriends());
    }
}