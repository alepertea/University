package repository;

import model.Participant;
import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;
import utils.JdbcUtils;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;
import java.util.Properties;

public class ParticipantRepository implements IParticipantRepository {
    private static final Logger logger= LogManager.getLogger();
    private JdbcUtils dbUtils;

    public ParticipantRepository(Properties props) {
        logger.info("Initializing ParticipantRepository with properties: {} ",props);
        dbUtils = new JdbcUtils(props);
    }

    @Override
    public Participant findOne(String id) {
        logger.traceEntry();
        Connection con = dbUtils.getConnection();
        Participant participant = null;
        try(PreparedStatement preStmt = con.prepareStatement("select * from Participant where id = (?)")){
            preStmt.setString(1, id);
            try(ResultSet result = preStmt.executeQuery()){
                String name = result.getString("participantName");
                int age = result.getInt("age");
                participant = new Participant(name, age);
            }
        }catch (SQLException ex)
        {
            logger.error(ex);
            System.err.println("Error DB" + ex);
        }
        logger.traceExit();
        return participant;
    }

    @Override
    public Iterable<Participant> findAll() {
        logger.traceEntry();
        Connection con = dbUtils.getConnection();
        List<Participant> participants = new ArrayList<>();
        try(PreparedStatement preStmt = con.prepareStatement("select * from Participant")){
            try(ResultSet result = preStmt.executeQuery()){
                while(result.next()){
                    String name = result.getString("participantName");
                    int age = result.getInt("age");
                    Participant participant = new Participant(name, age);
                    participants.add(participant);
                }
            }
        }catch (SQLException ex)
        {
            logger.error(ex);
            System.err.println("Error DB" + ex);
        }
        logger.traceExit();
        return participants;
    }

    @Override
    public Participant save(Participant entity) {
        logger.traceEntry("Saving participant {}", entity);
        Connection connection = dbUtils.getConnection();
        try(PreparedStatement preparedStatement = connection.prepareStatement("insert into Participant(participantName, age) values (?, ?)")) {
            preparedStatement.setString(1, entity.getName());
            preparedStatement.setInt(2, entity.getAge());
            int result = preparedStatement.executeUpdate();
            logger.trace("Saved {} instances", result);
        }catch(SQLException ex)
        {
            logger.error(ex);
            System.err.print("Error DB" + ex);
        }
        logger.traceExit();
        return entity;
    }
}
