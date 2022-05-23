package socialnetwork.controller;

import javafx.beans.property.SimpleStringProperty;
import javafx.beans.property.StringProperty;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.control.*;
import javafx.scene.control.cell.PropertyValueFactory;
import javafx.scene.image.Image;
import javafx.scene.layout.GridPane;
import javafx.scene.paint.Color;
import javafx.stage.Stage;
import socialnetwork.MyException;
import socialnetwork.config.ApplicationContext;
import socialnetwork.domain.*;
import socialnetwork.domain.validators.AccountValidator;
import socialnetwork.domain.validators.FriendRequestValidator;
import socialnetwork.domain.validators.FriendshipValidator;
import socialnetwork.domain.validators.UserValidator;
import socialnetwork.event.UserEvent;
import socialnetwork.observer.Observer;
import socialnetwork.repository.Repository;
import socialnetwork.repository.database.AccountDatabaseRepository;
import socialnetwork.repository.database.FriendRequestDatabaseRepository;
import socialnetwork.repository.database.FriendshipDatabaseRepository;
import socialnetwork.repository.database.UserDatabaseRepository;
import socialnetwork.service.FriendRequestService;
import socialnetwork.service.FriendshipService;
import socialnetwork.service.UserService;

import javax.crypto.BadPaddingException;
import javax.crypto.IllegalBlockSizeException;
import javax.crypto.NoSuchPaddingException;
import java.io.IOException;
import java.security.InvalidAlgorithmParameterException;
import java.security.InvalidKeyException;
import java.security.NoSuchAlgorithmException;
import java.time.LocalDateTime;
import java.util.ArrayList;
import java.util.List;
import java.util.Map;
import java.util.stream.Collectors;
import java.util.stream.StreamSupport;

public class HomeController implements Observer<UserEvent> {

    static User activeUser;
    public Label welcomeMessage;
    public Button buttonSendFriendRequest;
    public Button buttonRemoveFriend;
    public Button buttonRequests;

    public TableView <User> friendsTable;
    public TableColumn <User, String> friendColumnFirstName;
    public TableColumn <User, String> friendColumnLastName;
    public TableView <User> usersTable;
    public TableColumn <User, String> userColumnFirstName;
    public TableColumn <User, String> userColumnLastName;
    public Label messageToUser;
    public Button buttonRefresh;
    public Button buttonMessage;

    private UserService userService;
    private FriendRequestService friendRequestService;
    private FriendshipService friendshipService;
    ObservableList<User> modelUsers = FXCollections.observableArrayList();
    ObservableList<User> modelFriends = FXCollections.observableArrayList();


    static void setActiveUser(User activeUser) {
        HomeController.activeUser = activeUser;
    }

    private void initUsers()
    {
        Iterable<User> allUsers = userService.getAll();
        List<User> userList = StreamSupport.stream(allUsers.spliterator() , false)
                .filter(x -> (!x.getId().equals(activeUser.getId())))
                .collect(Collectors.toList());
        modelUsers.setAll(userList);
    }

    public void initFriends()
    {
        Map<User, LocalDateTime> allFriends = userService.getFriends(activeUser.getId());
        List<User> friendsList = new ArrayList<>();
        for (Map.Entry<User,LocalDateTime> entry : allFriends.entrySet())
            friendsList.add(entry.getKey());
        modelFriends.setAll(friendsList);
    }


    @FXML
    public void initialize()
    {
        final String url = ApplicationContext.getPROPERTIES().getProperty("database.socialnetwork.url");
        final String username= ApplicationContext.getPROPERTIES().getProperty("database.socialnetwork.username");
        final String password= ApplicationContext.getPROPERTIES().getProperty("database.socialnetwork.password");

        Repository<Long, User> userDatabaseRepository = new UserDatabaseRepository(url, username, password);
        Repository<Tuple<Long, Long>, Friendship> friendshipDatabaseRepository = new FriendshipDatabaseRepository(url, username, password);
        Repository<String, Account> accountDatabaseRepository = new AccountDatabaseRepository(url, username, password);
        Repository<Tuple<Long, Long>, FriendRequest> friendRequestDatabaseRepository = new FriendRequestDatabaseRepository(url, username, password);

        this.userService = new UserService(userDatabaseRepository, friendshipDatabaseRepository, accountDatabaseRepository, new UserValidator(), new AccountValidator());
        this.friendRequestService = new FriendRequestService(friendRequestDatabaseRepository, userDatabaseRepository, friendshipDatabaseRepository, new FriendRequestValidator());
        this.friendshipService = new FriendshipService(userDatabaseRepository, friendRequestDatabaseRepository,friendshipDatabaseRepository, new FriendshipValidator());
        userService.addObserver(this);

        friendColumnFirstName.setCellValueFactory(new PropertyValueFactory<User, String>("firstName"));
        friendColumnLastName.setCellValueFactory(new PropertyValueFactory<User, String>("lastName"));
        userColumnFirstName.setCellValueFactory(new PropertyValueFactory<User, String>("firstName"));
        userColumnLastName.setCellValueFactory(new PropertyValueFactory<User, String>("lastName"));

        usersTable.setItems(modelUsers);
        initUsers();

        friendsTable.setItems(modelFriends);
        initFriends();

        welcomeMessage.setText("Welcome, " + activeUser.getFirstName() + " " + activeUser.getLastName());
        welcomeMessage.setWrapText(true);
    }

    public void handleSendFriendRequest(ActionEvent actionEvent)
    {
        User selected = (User) usersTable.getSelectionModel().getSelectedItem();
        if (selected != null)
        {
            FriendRequest friendRequest = new FriendRequest(activeUser.getId(), selected.getId());
            try
            {
                this.friendRequestService.addFriendRequest(friendRequest);
                this.messageToUser.setText("Friend request sent successfully!");
                this.messageToUser.setTextFill(Color.DARKGREEN);
            }catch (MyException e)
            {
                this.messageToUser.setText(e.getMessage());
                this.messageToUser.setTextFill(Color.DARKRED);
            } catch (NoSuchPaddingException | NoSuchAlgorithmException | InvalidKeyException | InvalidAlgorithmParameterException | IllegalBlockSizeException | BadPaddingException e) {
                e.printStackTrace();
            }
        }
        else
        {
            this.messageToUser.setText("No item selected!");
            this.messageToUser.setTextFill(Color.DARKRED);
        }
    }

    public void handleRemoveFriend(ActionEvent actionEvent)
    {
        User selected = (User) friendsTable.getSelectionModel().getSelectedItem();
        if (selected != null)
        {
            Friendship friendship = new Friendship();
            friendship.setId(new Tuple<>(activeUser.getId(), selected.getId()));
            try
            {
                Friendship deleted = friendshipService.removeFriendship(friendship);
                initFriends();
                this.messageToUser.setText("Friend removed successfully!");
                this.messageToUser.setTextFill(Color.DARKGREEN);
            }catch (MyException e)
            {
                this.messageToUser.setText(e.getMessage());
                this.messageToUser.setTextFill(Color.DARKRED);
            }
        }
        else
        {
            this.messageToUser.setText("No item selected!");
            this.messageToUser.setTextFill(Color.DARKRED);
        }
    }

    public void handleRequests(ActionEvent actionEvent)
    {
        try
        {
            FXMLLoader loader = new FXMLLoader();
            loader.setLocation(getClass().getResource("/view/FriendRequests.fxml"));
            GridPane root = loader.load();
            FriendRequestsController controller = loader.getController();
            this.friendRequestService.addObserver(controller);
            Scene scene = new Scene(root, 600, 500);
            Stage stage = new Stage();
            stage.setTitle("Friend requests");
            stage.setResizable(false);
            stage.getIcons().add(new Image("/images/request.png"));
            stage.setScene(scene);
            stage.show();
        } catch (IOException e)
        {
            e.printStackTrace();
        }
    }

    @Override
    public void update(UserEvent userEvent)
    {
        initUsers();
        initFriends();
    }

    public void handleRefresh(ActionEvent actionEvent)
    {
        initFriends();
        initUsers();
    }

    public void handleMessage(ActionEvent actionEvent)
    {
        try
        {
            FXMLLoader loader = new FXMLLoader();
            loader.setLocation(getClass().getResource("/view/Messages.fxml"));
            GridPane root = loader.load();
            Scene scene = new Scene(root, 600, 500);
            Stage stage = new Stage();
            stage.setTitle("Messages");
            stage.setResizable(false);
            stage.getIcons().add(new Image("/images/message.png"));
            stage.setScene(scene);
            stage.show();
        } catch (IOException e)
        {
            e.printStackTrace();
        }
    }
}
