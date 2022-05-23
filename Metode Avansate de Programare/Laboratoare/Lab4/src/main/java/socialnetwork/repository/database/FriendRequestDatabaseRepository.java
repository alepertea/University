package socialnetwork.repository.database;

import socialnetwork.domain.FriendRequest;
import socialnetwork.domain.Status;
import socialnetwork.domain.Tuple;
import socialnetwork.repository.Repository;

import java.sql.*;
import java.time.LocalDateTime;
import java.util.HashSet;
import java.util.Set;

public class FriendRequestDatabaseRepository implements Repository<Tuple<Long,Long>, FriendRequest>
{
    private Connection connection;

    public FriendRequestDatabaseRepository(String url, String username, String password)
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
    public FriendRequest findOne(Tuple<Long,Long> id)
    {
        FriendRequest friendRequest = null;

        try
        {
            PreparedStatement statement = this.connection.prepareStatement("SELECT * from Cerere WHERE idFrom = (?) AND idTo = (?)");

            statement.setLong(1, id.getLeft());
            statement.setLong(2, id.getRight());

            ResultSet resultSet = statement.executeQuery();

            if(!resultSet.next())
                return null;

            Long idFrom = resultSet.getLong("idFrom");
            Long idTo = resultSet.getLong("idTo");
            String status = resultSet.getString("status");
            LocalDateTime date = resultSet.getTimestamp("date").toLocalDateTime();

            Status finalStatus = null;
            switch(status)
            {
                case "PENDING": { finalStatus = Status.PENDING; break; }
                case "APPROVED": { finalStatus = Status.APPROVED; break; }
                case "REJECTED": { finalStatus = Status.REJECTED; break; }
            }

            friendRequest = new FriendRequest(idFrom, idTo);
            friendRequest.setId(new Tuple<>(idFrom, idTo));
            friendRequest.setDate(date);
            friendRequest.setStatus(finalStatus);
        }catch (SQLException e)
        {
            e.printStackTrace();
        }
        return friendRequest;
    }

    @Override
    public Iterable<FriendRequest> findAll()
    {
        Set<FriendRequest> friendRequests = new HashSet<>();
        try
        {
            PreparedStatement statement = this.connection.prepareStatement("SELECT * from Cerere");
            ResultSet resultSet = statement.executeQuery();

            while (resultSet.next())
            {
                Long idFrom = resultSet.getLong("idFrom");
                Long idTo = resultSet.getLong("idTo");
                String status = resultSet.getString("status");
                LocalDateTime date = resultSet.getTimestamp("date").toLocalDateTime();

                Status finalStatus = null;
                switch(status)
                {
                    case "PENDING": { finalStatus = Status.PENDING; break; }
                    case "APPROVED": { finalStatus = Status.APPROVED; break; }
                    case "REJECTED": { finalStatus = Status.REJECTED; break; }
                }

                FriendRequest friendRequest = new FriendRequest(idFrom, idTo);
                friendRequest.setStatus(finalStatus);
                friendRequest.setId(new Tuple<>(idFrom, idTo));
                friendRequest.setDate(date);
                friendRequests.add(friendRequest);
            }
        } catch (SQLException e)
        {
            e.printStackTrace();
        }
        return friendRequests;
    }

    @Override
    public FriendRequest save(FriendRequest entity)
    {
        try
        {
            PreparedStatement statement = this.connection.prepareStatement("INSERT INTO Cerere(idFrom, idTo, status, date) VALUES (?, ?, ?, ?)");

            statement.setLong(1, entity.getFrom());
            statement.setLong(2, entity.getTo());
            statement.setString(3, entity.getStatus().toString());
            statement.setTimestamp(4, Timestamp.valueOf(entity.getDate()));

            statement.executeUpdate();
        }catch (SQLException e)
        {
            e.printStackTrace();
        }
        return entity;
    }

    @Override
    public FriendRequest delete(Tuple<Long,Long> id)
    {
        try
        {
            PreparedStatement statement = this.connection.prepareStatement("DELETE FROM Cerere WHERE idFrom = (?) AND idTo = (?)");

            statement.setLong(1, id.getLeft());
            statement.setLong(2, id.getRight());

            statement.executeUpdate();
        }catch (SQLException e)
        {
            e.printStackTrace();
        }

        return null;
    }

    @Override
    public FriendRequest update(FriendRequest entity)
    {
        this.delete(new Tuple<>(entity.getFrom(), entity.getTo()));
        this.save(entity);
        return null;
    }
}
