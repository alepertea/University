package repository;

import model.Participant;
import model.Registration;
import model.Track;
import model.Tuple;
import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;
import utils.JdbcUtils;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.*;

public class RegistrationRepository implements IRegistrationRepository {
    private static final Logger logger= LogManager.getLogger();
    private JdbcUtils dbUtils;

    public RegistrationRepository(Properties props) {
        logger.info("Initializing RegistrationRepository with properties: {} ",props);
        dbUtils = new JdbcUtils(props);
    }

    @Override
    public Map<Participant, Integer> getParticipantsByTrackAndAgeGroup(Track track, String ageGroup) {
        logger.traceEntry();
        Connection con = dbUtils.getConnection();
        Map<Participant, Integer> participants = new HashMap<>();
        try(PreparedStatement preStmt = con.prepareStatement("select *, count(participantName) as [number] from Participant P " +
                "inner join Registration R on P.participantName = R.participantID " +
                "where trackID = ? and age >= ? and age <= ?")){

            preStmt.setString(1, track.getName());
            preStmt.setInt(2, Integer.parseInt(ageGroup.split("-")[0]));
            preStmt.setInt(3, Integer.parseInt(ageGroup.split("-")[1]));

            try(ResultSet result = preStmt.executeQuery()){
                while(result.next()){

                    String participantName = result.getString("participantName");
                    int age = result.getInt("age");
                    int number = result.getInt("number");

                    Participant participant = new Participant(participantName, age);

                    participants.put(participant, number);
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
    public Registration findOne(Tuple<Participant, Track> id) {
        logger.traceEntry();
        Connection con = dbUtils.getConnection();
        Registration registration = null;
        try(PreparedStatement preStmt = con.prepareStatement("select * from Participant P " +
                "inner join Registration R on P.participantName = R.participantID " +
                "inner join Track T on T.name = R.trackID " +
                "where participantID = (?) and trackID = (?)")){
            preStmt.setString(1, id.getLeft().getId());
            preStmt.setString(1, id.getRight().getId());
            try(ResultSet result = preStmt.executeQuery()){
                String participantName = result.getString("participantName");
                int age = result.getInt("age");
                String trackName = result.getString("name");
                int minimumAge = result.getInt("minimumAge");
                int maximumAge = result.getInt("maximumAge");

                Participant participant = new Participant(participantName, age);
                Track track = new Track(trackName, minimumAge, maximumAge);

                registration = new Registration(participant, track);
            }
        }catch (SQLException ex)
        {
            logger.error(ex);
            System.err.println("Error DB" + ex);
        }
        logger.traceExit();
        return registration;
    }

    @Override
    public Iterable<Registration> findAll() {
        logger.traceEntry();
        Connection con = dbUtils.getConnection();
        List<Registration> registrations = new ArrayList<>();
        try(PreparedStatement preStmt = con.prepareStatement("select * from Participant P " +
                "inner join Registration R on P.participantName = R.participantID " +
                "inner join Track T on T.name = R.trackID")){
            try(ResultSet result = preStmt.executeQuery()){
                while(result.next()){

                    String participantName = result.getString("participantName");
                    int age = result.getInt("age");
                    String trackName = result.getString("name");
                    int minimumAge = result.getInt("minimumAge");
                    int maximumAge = result.getInt("maximumAge");

                    Participant participant = new Participant(participantName, age);
                    Track track = new Track(trackName, minimumAge, maximumAge);

                    Registration registration = new Registration(participant, track);

                    registrations.add(registration);
                }
            }
        }catch (SQLException ex)
        {
            logger.error(ex);
            System.err.println("Error DB" + ex);
        }
        logger.traceExit();
        return registrations;
    }

    @Override
    public Registration save(Registration entity) {
        logger.traceEntry("Saving registration {}", entity);
        Connection connection = dbUtils.getConnection();
        try(PreparedStatement preparedStatement = connection.prepareStatement("insert into Registration(participantID, trackID) values (?, ?)")){
            preparedStatement.setString(1, entity.getParticipant().getId());
            preparedStatement.setString(2, entity.getTrack().getId());

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
