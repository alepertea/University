package repository;

import model.Track;
import model.User;
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

public class TrackRepository implements ITrackRepository {
    private static final Logger logger= LogManager.getLogger();
    private JdbcUtils dbUtils;

    public TrackRepository(Properties props) {
        logger.info("Initializing TrackRepository with properties: {} ",props);
        dbUtils = new JdbcUtils(props);
    }

    @Override
    public Track findOne(String s) {
        logger.traceEntry();
        Connection con = dbUtils.getConnection();
        Track track = null;
        try(PreparedStatement preStmt = con.prepareStatement("select * from Track where name = (?)")){
            preStmt.setString(1, s);
            try(ResultSet result = preStmt.executeQuery()){
                int minimumAge = result.getInt("minimumAge");
                int maximumAge = result.getInt("maximumAge");
                track = new Track(s, minimumAge, maximumAge);
            }
        }catch (SQLException ex)
        {
            logger.error(ex);
            System.err.println("Error DB" + ex);
        }
        logger.traceExit();
        return track;
    }

    @Override
    public Iterable<Track> findAll() {
        logger.traceEntry();
        Connection con = dbUtils.getConnection();
        List<Track> tracks = new ArrayList<>();
        try(PreparedStatement preStmt = con.prepareStatement("select * from Track")){
            try(ResultSet result = preStmt.executeQuery()){
                while(result.next()){
                    String name = result.getString("name");
                    int minimumAge = result.getInt("minimumAge");
                    int maximumAge = result.getInt("maximumAge");
                    Track track = new Track(name, minimumAge, maximumAge);
                    tracks.add(track);
                }
            }
        }catch (SQLException ex)
        {
            logger.error(ex);
            System.err.println("Error DB" + ex);
        }
        logger.traceExit();
        return tracks;
    }

    @Override
    public Track save(Track entity) {
        logger.traceEntry("Saving track {}", entity);
        Connection connection = dbUtils.getConnection();
        try(PreparedStatement preparedStatement = connection.prepareStatement("insert into Track(name, minimumAge, maximumAge) values (?, ?, ?)")){
            preparedStatement.setString(1, entity.getName());
            preparedStatement.setInt(2, entity.getMinimumAge());
            preparedStatement.setInt(3, entity.getMaximumAge());
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
