package socialnetwork.repository.database;

import socialnetwork.domain.User;
import socialnetwork.repository.Repository;
import socialnetwork.repository.RepositoryException;

import java.sql.*;
import java.util.HashSet;
import java.util.Set;

public class UserDatabaseRepository implements Repository<Long, User>
{
    private Connection connection;

    public UserDatabaseRepository(String url, String username, String password)
    {
        try
        {
            this.connection = DriverManager.getConnection(url, username, password);
        }
        catch (SQLException e)
        {
            e.printStackTrace();
        }
    }

    @Override
    public User findOne(Long id)
    {
        User user = null;

        try
        {
            PreparedStatement statement = this.connection.prepareStatement("SELECT * from Utilizator WHERE id = (?)");

            statement.setLong(1, id);

            ResultSet resultSet = statement.executeQuery();

            if(!resultSet.next())
                return null;

            Long idUser = resultSet.getLong("id");
            String firstName = resultSet.getString("first_name");
            String lastName = resultSet.getString("last_name");
            String email = resultSet.getString("email");

            user = new User(firstName, lastName, email);
            user.setId(idUser);
        }catch (SQLException e)
        {
            e.printStackTrace();
        }
        return user;
    }

    @Override
    public Iterable<User> findAll()
    {
        Set<User> users = new HashSet<>();
        try
        {
            PreparedStatement statement = this.connection.prepareStatement("SELECT * from Utilizator");
            ResultSet resultSet = statement.executeQuery();

            while (resultSet.next())
            {
                Long id = resultSet.getLong("id");
                String firstName = resultSet.getString("first_name");
                String lastName = resultSet.getString("last_name");
                String email = resultSet.getString("email");

                User user = new User(firstName, lastName, email);
                user.setId(id);
                users.add(user);
            }

            return users;
        } catch (SQLException e)
        {
            e.printStackTrace();
        }
        return users;
    }

    @Override
    public User save(User entity)
    {
        try
        {
            PreparedStatement statement = this.connection.prepareStatement("INSERT INTO Utilizator(id, first_name, last_name, email) VALUES (?, ?, ?, ?)");

            statement.setLong(1, entity.getId());
            statement.setString(2, entity.getFirstName());
            statement.setString(3, entity.getLastName());
            statement.setString(4, entity.getEmail());

            statement.executeUpdate();
        }catch (SQLException e)
        {
            e.printStackTrace();
        }
        return null;
    }

    @Override
    public User delete(Long id)
    {
        User user = this.findOne(id);
        if(user == null)
            return null;

        try
        {
            PreparedStatement statement = this.connection.prepareStatement("DELETE FROM Utilizator WHERE id = (?)");

            statement.setLong(1, id);

            statement.executeUpdate();
        }catch (SQLException e)
        {
            e.printStackTrace();
        }

        return user;
    }

    @Override
    public User update(User entity)
    {
        User user = this.findOne(entity.getId());
        if(user == null)
            return entity;

        try
        {
            PreparedStatement statement = this.connection.prepareStatement("UPDATE Utilizator SET first_name = (?), last_name = (?) WHERE id = (?)");

            statement.setString(1, entity.getFirstName());
            statement.setString(2, entity.getLastName());
            statement.setLong(3, entity.getId());

            statement.executeUpdate();
        }catch (SQLException e)
        {
            e.printStackTrace();
        }

        return null;
    }
}
