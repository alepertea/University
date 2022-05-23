package socialnetwork.controller;

import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.control.Label;
import javafx.scene.control.PasswordField;
import javafx.scene.control.TextField;
import javafx.scene.image.Image;
import javafx.scene.layout.GridPane;
import javafx.scene.paint.Color;
import javafx.stage.Stage;
import socialnetwork.MyException;
import socialnetwork.config.ApplicationContext;
import socialnetwork.domain.Account;
import socialnetwork.domain.Friendship;
import socialnetwork.domain.Tuple;
import socialnetwork.domain.User;
import socialnetwork.domain.validators.AccountValidator;
import socialnetwork.domain.validators.UserValidator;
import socialnetwork.domain.validators.ValidationException;
import socialnetwork.repository.Repository;
import socialnetwork.repository.database.AccountDatabaseRepository;
import socialnetwork.repository.database.FriendshipDatabaseRepository;
import socialnetwork.repository.database.UserDatabaseRepository;
import socialnetwork.service.UserService;

import java.io.IOException;

public class LoginController
{
    public TextField usernameField;
    public PasswordField passwordField;
    public Label messageToUser;
    private UserService userService;

    @FXML
    public void initialize()
    {
        final String url = ApplicationContext.getPROPERTIES().getProperty("database.socialnetwork.url");
        final String username= ApplicationContext.getPROPERTIES().getProperty("database.socialnetwork.username");
        final String password= ApplicationContext.getPROPERTIES().getProperty("database.socialnetwork.password");

        Repository<Long, User> userDatabaseRepository = new UserDatabaseRepository(url, username, password);
        Repository<Tuple<Long, Long>, Friendship> friendshipDatabaseRepository = new FriendshipDatabaseRepository(url, username, password);
        Repository<String, Account> accountDatabaseRepository = new AccountDatabaseRepository(url, username, password);

        this.userService = new UserService(userDatabaseRepository, friendshipDatabaseRepository, accountDatabaseRepository, new UserValidator(), new AccountValidator());

        usernameField.setText("");
        passwordField.setText("");
    }

    public void handleSubmitButtonAction(ActionEvent event)
    {
        try{
            Account account = userService.findAccount(usernameField.getText());
            if(!account.getPassword().equals(passwordField.getText()))
                throw new ValidationException("Invalid password!");

            HomeController.setActiveUser(userService.findUser(account.getUserID()));

            FXMLLoader loader = new FXMLLoader();
            loader.setLocation(getClass().getResource("/view/Home.fxml"));
            GridPane root = loader.load();
            HomeController controller = loader.getController();
            Scene scene = new Scene(root, 650, 500);
            Stage stage = new Stage();
            stage.setTitle("Home");
            stage.setResizable(false);
            stage.getIcons().add(new Image("/images/home.png"));
            stage.setScene(scene);
            stage.show();
        }
        catch (MyException e) {
            messageToUser.setText(e.getMessage());
            messageToUser.setTextFill(Color.DARKRED);

            usernameField.setText("");
            passwordField.setText("");
        }
        catch (IOException e)
        {
            e.printStackTrace();
        }
    }

    public void handleSignUpAction(ActionEvent actionEvent)
    {
        try
        {
            FXMLLoader loader = new FXMLLoader();
            loader.setLocation(getClass().getResource("/view/Signup.fxml"));
            GridPane root = loader.load();
            SignupController controller = loader.getController();
            Scene scene = new Scene(root, 493, 600);
            Stage stage = new Stage();
            stage.setTitle("Sign up");
            stage.setResizable(false);
            stage.getIcons().add(new Image("/images/login.png"));
            stage.setScene(scene);
            stage.show();
        }catch (IOException e)
        {
            e.printStackTrace();
        }
    }
}
