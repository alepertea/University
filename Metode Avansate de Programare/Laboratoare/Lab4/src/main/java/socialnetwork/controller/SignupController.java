package socialnetwork.controller;

import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.Alert;
import javafx.scene.control.PasswordField;
import javafx.scene.control.TextField;
import socialnetwork.MyException;
import socialnetwork.config.ApplicationContext;
import socialnetwork.domain.Account;
import socialnetwork.domain.Friendship;
import socialnetwork.domain.Tuple;
import socialnetwork.domain.User;
import socialnetwork.domain.validators.AccountValidator;
import socialnetwork.domain.validators.UserValidator;
import socialnetwork.repository.Repository;
import socialnetwork.repository.database.AccountDatabaseRepository;
import socialnetwork.repository.database.FriendshipDatabaseRepository;
import socialnetwork.repository.database.UserDatabaseRepository;
import socialnetwork.service.UserService;

public class SignupController
{
    public TextField usernameField;
    public PasswordField passwordField1;
    public PasswordField passwordField2;
    public UserService userService;
    public TextField firstNameField;
    public TextField lastNameField;

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

        this.usernameField.setText("");
        this.passwordField1.setText("");
        this.passwordField2.setText("");
        this.firstNameField.setText("");
        this.lastNameField.setText("");
    }

    public void handleSubmitButtonAction(ActionEvent actionEvent)
    {
        String username = this.usernameField.getText();
        String password1 = this.passwordField1.getText();
        String password2 = this.passwordField2.getText();
        String firstName = this.firstNameField.getText();
        String lastName = this.lastNameField.getText();

        if(password1.compareTo(password2) != 0)
        {
            MessageAlert.showErrorMessage(null, "Passwords do not match!");
            this.passwordField1.setText("");
            this.passwordField2.setText("");
        }

        try
        {
            User user = new User(firstName, lastName, username);
            user.setId(this.userService.generateUserID());
            Account account = new Account(username, password1, user.getId());
            account.setId(username);

            this.userService.addUser(user, account);

            MessageAlert.showMessage(null, Alert.AlertType.CONFIRMATION, "Success", "Account created successfully!");
        }catch (MyException e)
        {
            MessageAlert.showMessage(null, Alert.AlertType.WARNING, "Something went wrong", e.getMessage());
            this.firstNameField.setText("");
            this.lastNameField.setText("");
            this.usernameField.setText("");
            this.passwordField1.setText("");
            this.passwordField2.setText("");
        }
    }
}
