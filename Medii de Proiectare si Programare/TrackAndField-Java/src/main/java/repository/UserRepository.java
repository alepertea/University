package repository;

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

public class UserRepository implements IUserRepository {
    private static final Logger logger= LogManager.getLogger();
    private JdbcUtils dbUtils;

    public UserRepository(Properties props) {
        logger.info("Initializing UserRepository with properties: {} ",props);
        dbUtils = new JdbcUtils(props);
    }

    @Override
    public User findOne(String s) {
        logger.traceEntry();
        Connection con = dbUtils.getConnection();
        User user = null;
        try(PreparedStatement preStmt = con.prepareStatement("select * from User where username = (?)")){
            preStmt.setString(1, s);
            try(ResultSet result = preStmt.executeQuery()){
                String username = result.getString("username");
                String password = result.getString("password");
                user = new User(username, password);
            }
        }catch (SQLException ex)
        {
            logger.error(ex);
            System.err.println("Error DB" + ex);
        }
        logger.traceExit();
        return user;
    }

    @Override
    public Iterable<User> findAll() {
        logger.traceEntry();
        Connection con = dbUtils.getConnection();
        List<User> users = new ArrayList<>();
        try(PreparedStatement preStmt = con.prepareStatement("select * from User")){
            try(ResultSet result = preStmt.executeQuery()){
                while(result.next()){
                    String username = result.getString("username");
                    String password = result.getString("password");
                    User user = new User(username, password);
                    users.add(user);
                }
            }
        }catch (SQLException ex)
        {
            logger.error(ex);
            System.err.println("Error DB" + ex);
        }
        logger.traceExit();
        return users;
    }

    @Override
    public User save(User entity) {
        logger.traceEntry("Saving user {}", entity);
        Connection connection = dbUtils.getConnection();
        try(PreparedStatement preparedStatement = connection.prepareStatement("insert into User(username, password) values (?, ?)")){
            preparedStatement.setString(1, entity.getUsername());
            preparedStatement.setString(2, entity.getPassword());
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

    @Override
    public User findByUsernameAndPassword(String username, String password) {
        logger.traceEntry();
        Connection con = dbUtils.getConnection();
        User user = null;
        try(PreparedStatement preStmt = con.prepareStatement("select * from User where username = (?) and password = (?)")){
            preStmt.setString(1, username);
            preStmt.setString(1, password);
            try(ResultSet result = preStmt.executeQuery()){
                String username1 = result.getString("username");
                String password1 = result.getString("password");
                user = new User(username1, password1);
            }
        }catch (SQLException ex)
        {
            logger.error(ex);
            System.err.println("Error DB" + ex);
        }
        logger.traceExit();
        return user;
    }
}
