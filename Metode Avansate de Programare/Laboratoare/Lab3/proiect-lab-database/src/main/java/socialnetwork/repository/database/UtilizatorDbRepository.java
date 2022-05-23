package socialnetwork.repository.database;

import socialnetwork.domain.User;
import socialnetwork.domain.validators.Validator;
import socialnetwork.repository.Repository;

import java.sql.*;
import java.util.HashSet;
import java.util.Optional;
import java.util.Set;

public class UtilizatorDbRepository implements Repository<Long, User>
{
    private String url;
    private String username;
    private String password;
    private Validator<User> validator;

    public UtilizatorDbRepository(String url, String username, String password, Validator<User> validator)
    {
        this.url = url;
        this.username = username;
        this.password = password;
        this.validator = validator;
    }

    @Override
    public Optional<User> findOne(Long aLong)
    {
        User user = null;

        try(Connection connection = DriverManager.getConnection(url, username, password);
        PreparedStatement statement = connection.prepareStatement("SELECT * from Utilizator WHERE id = " + aLong);
        ResultSet resultSet = statement.executeQuery())
        {
            resultSet.next();
            Long id = resultSet.getLong("id");
            String firstName = resultSet.getString("first_name");
            String lastName = resultSet.getString("last_name");

            user = new User(firstName, lastName);
            user.setId(id);
        }catch (SQLException e)
        {
            e.printStackTrace();
        }
        return Optional.ofNullable(user);
    }

    @Override
    public Iterable<User> findAll()
    {
        Set<User> users = new HashSet<>();
        try (Connection connection = DriverManager.getConnection(url, username, password);
             PreparedStatement statement = connection.prepareStatement("SELECT * from Utilizator");
             ResultSet resultSet = statement.executeQuery())
        {
            while (resultSet.next())
            {
                Long id = resultSet.getLong("id");
                String firstName = resultSet.getString("first_name");
                String lastName = resultSet.getString("last_name");

                User user = new User(firstName, lastName);
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
    public Optional<User> save(User entity)
    {
        if(!this.findOne(entity.getId()).isPresent())
        {
            try(Connection connection = DriverManager.getConnection(url, username, password);
                PreparedStatement statement = connection.prepareStatement("INSERT INTO Utilizator(id, first_name, last_name) VALUES (" + entity.getId() + "," + entity.getFirstName() + "," + entity.getLastName() + ")");
                )
            {
                ResultSet resultSet = null;
                resultSet = statement.executeQuery();
                
            }catch(SQLException e)
            {
                e.printStackTrace();
            }
        }
        return Optional.ofNullable(entity);
    }

    @Override
    public Optional<User> delete(Long aLong) {
        return Optional.empty();
    }

    @Override
    public Optional<User> update(User entity) {
        return Optional.empty();
    }
}
