package socialnetwork.repository.database;

import socialnetwork.domain.Friendship;
import socialnetwork.domain.Tuple;
import socialnetwork.repository.Repository;

import java.sql.*;
import java.time.LocalDateTime;
import java.util.HashSet;
import java.util.Set;

public class FriendshipDatabaseRepository implements Repository<Tuple<Long,Long>, Friendship>
{
    private Connection connection;

    public FriendshipDatabaseRepository(String url, String username, String password)
    {
        try
        {
            this.connection = DriverManager.getConnection(url, username, password);
        }catch (SQLException e)
        {
            e.printStackTrace();
        }
    }

    @Override
    public Friendship findOne(Tuple<Long, Long> id)
    {
        Friendship friendship = null;

        try
        {
            PreparedStatement statement = this.connection.prepareStatement("SELECT * from Prietenie WHERE id1 = (?) AND id2 = (?) OR id1 = (?) AND id2 = (?)");

            statement.setLong(1, id.getLeft());
            statement.setLong(2, id.getRight());
            statement.setLong(3, id.getRight());
            statement.setLong(4, id.getLeft());

            ResultSet resultSet = statement.executeQuery();

            if(!resultSet.next())
                return null;

            Long id1 = resultSet.getLong("id1");
            Long id2 = resultSet.getLong("id2");
            LocalDateTime date = resultSet.getTimestamp("dataPrietenie").toLocalDateTime();

            friendship = new Friendship();
            friendship.setDate(date);
            friendship.setId(new Tuple<>(id1, id2));
        }catch (SQLException e)
        {
            e.printStackTrace();
        }
        return friendship;
    }

    @Override
    public Iterable<Friendship> findAll()
    {
        Set<Friendship> friendships = new HashSet<>();
        try
        {
            PreparedStatement statement = this.connection.prepareStatement("SELECT * from Prietenie");
            ResultSet resultSet = statement.executeQuery();

            while (resultSet.next())
            {
                Long id1 = resultSet.getLong("id1");
                Long id2 = resultSet.getLong("id2");
                Tuple<Long,Long> id = new Tuple<>(id1, id2);
                LocalDateTime date = resultSet.getTimestamp("dataPrietenie").toLocalDateTime();

                Friendship friendship = new Friendship();
                friendship.setDate(date);
                friendship.setId(id);
                friendships.add(friendship);
            }
        } catch (SQLException e)
        {
            e.printStackTrace();
        }
        return friendships;
    }

    @Override
    public Friendship save(Friendship entity)
    {
        try
        {
            PreparedStatement statement = this.connection.prepareStatement("INSERT INTO Prietenie(id1, id2, dataPrietenie) VALUES (?, ?, ?)");

            statement.setLong(1, entity.getId().getLeft());
            statement.setLong(2, entity.getId().getRight());
            statement.setTimestamp(3, Timestamp.valueOf(entity.getDate()));

            statement.executeUpdate();
        }catch (SQLException e)
        {
            e.printStackTrace();
        }
        return entity;
    }

    @Override
    public Friendship delete(Tuple<Long,Long> id)
    {
        try
        {
            PreparedStatement statement = this.connection.prepareStatement("DELETE FROM Prietenie WHERE id1 = (?) AND id2 = (?) OR id1 = (?) AND id2 = (?)");

            statement.setLong(1, id.getLeft());
            statement.setLong(2, id.getRight());
            statement.setLong(3, id.getRight());
            statement.setLong(4, id.getLeft());

            statement.executeUpdate();
        }catch (SQLException e)
        {
            e.printStackTrace();
        }

        return null;
    }

    @Override
    public Friendship update(Friendship entity)
    {
        Friendship friendship = this.findOne(entity.getId());
        if(friendship == null)
            return entity;
        friendship = this.findOne(new Tuple<>(entity.getId().getRight(), entity.getId().getLeft()));
        if(friendship == null)
            return entity;

        try
        {
            PreparedStatement statement = this.connection.prepareStatement("UPDATE Prietenie SET dataPrietenie = (?) WHERE id1 = (?) AND id2 = (?) OR id1 = (?) AND id2 = (?)");

            statement.setLong(1, entity.getId().getLeft());
            statement.setLong(2, entity.getId().getRight());
            statement.setLong(3, entity.getId().getRight());
            statement.setLong(4, entity.getId().getLeft());

            statement.executeUpdate();
        }catch (SQLException e)
        {
            e.printStackTrace();
        }

        return null;
    }
}
