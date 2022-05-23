package socialnetwork.repository.database;

import socialnetwork.domain.Message;
import socialnetwork.repository.Repository;
import socialnetwork.repository.RepositoryException;

import java.sql.*;
import java.time.LocalDateTime;
import java.util.ArrayList;
import java.util.HashSet;
import java.util.List;
import java.util.Set;

public class MessageDatabaseRepository implements Repository<Long, Message>
{
    private Connection connection;

    public MessageDatabaseRepository(String url, String username, String password)
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
    public Message findOne(Long id)
    {
        try
        {
            PreparedStatement statement = this.connection.prepareStatement("SELECT * FROM Mesaj WHERE idMesaj = (?)");
            statement.setLong(1, id);
            ResultSet resultSet = statement.executeQuery();

            if(!resultSet.next())
                return null;

            long idMesaj = resultSet.getLong("idMesaj");
            String text = resultSet.getString("text");
            LocalDateTime date = resultSet.getTimestamp("date").toLocalDateTime();
            Long idFrom = resultSet.getLong("idFrom");

            PreparedStatement statement2 = this.connection.prepareStatement("SELECT * FROM Recipient WHERE idMesaj = (?)");
            statement2.setLong(1, idMesaj);
            resultSet = statement2.executeQuery();

            ArrayList<Long> recipients = new ArrayList<>();
            while(resultSet.next())
            {
                recipients.add(resultSet.getLong("idUser"));
            }

            Message message = new Message(idFrom, recipients, text, date);
            message.setId(idMesaj);
            return message;

        }catch (SQLException e)
        {
            e.printStackTrace();
        }
        return null;
    }

    @Override
    public Iterable<Message> findAll()
    {
        Set<Message> messages = new HashSet<>();
        try
        {
            PreparedStatement statement = this.connection.prepareStatement("SELECT * FROM Mesaj");
            ResultSet resultSet = statement.executeQuery();

            while(resultSet.next())
            {
                long idMesaj = resultSet.getLong("idMesaj");
                String text = resultSet.getString("text");
                LocalDateTime date = resultSet.getTimestamp("date").toLocalDateTime();
                Long idFrom = resultSet.getLong("idFrom");

                PreparedStatement statement2 = this.connection.prepareStatement("SELECT * FROM Recipient WHERE idMesaj = (?)");
                statement2.setLong(1, idMesaj);
                ResultSet resultSet2 = statement2.executeQuery();

                ArrayList<Long> recipients = new ArrayList<>();
                while(resultSet2.next())
                {
                    recipients.add(resultSet2.getLong("idUser"));
                }

                Message message = new Message(idFrom, recipients, text, date);
                message.setId(idMesaj);

                messages.add(message);
            }
        }catch (SQLException e)
        {
            e.printStackTrace();
        }

        return messages;
    }

    @Override
    public Message save(Message entity)
    {
        if(this.findOne(entity.getId()) != null)
        {
            throw new RepositoryException("ID already exists!");
        }

        try
        {
            PreparedStatement statement1 = this.connection.prepareStatement("INSERT INTO Mesaj(idMesaj, text, date, idFrom, originalMessageId) VALUES (?, ?, ?, ?, ?)");

            statement1.setLong(1, entity.getId());
            statement1.setString(2, entity.getMessage());
            statement1.setTimestamp(3, Timestamp.valueOf(entity.getDate()));
            statement1.setLong(4, entity.getFrom());
            statement1.setLong(5, entity.getOriginalMessageId());

            statement1.executeUpdate();

            List<Long> recipients = entity.getTo();
            PreparedStatement statement2 = this.connection.prepareStatement("INSERT INTO Recipient(idUser, idMesaj) VALUES (?, ?)");
            for(Long recipient : recipients)
            {
                statement2.setLong(1, recipient);
                statement2.setLong(2, entity.getId());

                statement2.executeUpdate();
            }
        }catch (SQLException e)
        {
            e.printStackTrace();
        }
        return entity;
    }

    @Override
    public Message delete(Long aLong)
    {
        return null;
    }

    @Override
    public Message update(Message entity)
    {
        return null;
    }
}
