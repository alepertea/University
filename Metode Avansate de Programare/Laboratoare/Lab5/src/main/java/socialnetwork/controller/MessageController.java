package socialnetwork.controller;

import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.event.ActionEvent;
import javafx.event.EventHandler;
import javafx.fxml.FXML;
import javafx.scene.control.*;
import javafx.scene.control.cell.PropertyValueFactory;
import javafx.scene.input.KeyCode;
import javafx.scene.input.KeyEvent;
import javafx.scene.input.MouseEvent;
import javafx.scene.paint.Color;
import socialnetwork.MyException;
import socialnetwork.config.ApplicationContext;
import socialnetwork.domain.*;
import socialnetwork.domain.validators.AccountValidator;
import socialnetwork.domain.validators.MessageValidator;
import socialnetwork.domain.validators.UserValidator;
import socialnetwork.event.MessageEvent;
import socialnetwork.observer.Observer;
import socialnetwork.repository.Repository;
import socialnetwork.repository.database.AccountDatabaseRepository;
import socialnetwork.repository.database.FriendshipDatabaseRepository;
import socialnetwork.repository.database.MessageDatabaseRepository;
import socialnetwork.repository.database.UserDatabaseRepository;
import socialnetwork.service.MessageService;
import socialnetwork.service.UserService;

import javax.crypto.BadPaddingException;
import javax.crypto.IllegalBlockSizeException;
import javax.crypto.NoSuchPaddingException;
import java.security.InvalidAlgorithmParameterException;
import java.security.InvalidKeyException;
import java.security.NoSuchAlgorithmException;
import java.time.LocalDateTime;
import java.util.ArrayList;
import java.util.List;
import java.util.Map;

public class MessageController implements Observer<MessageEvent>
{
    public TableView<User> friendsTable;
    public TableColumn<User, String> friendColumnFirstName;
    public TableColumn<User, String> friendColumnLastName;
    public ListView<String> messageList;
    public TextField messageField;
    public Label errorMessage;
    public TableView<String> groupchatTable;
    public TableColumn<String, String> friendListColumn;
    public ListView<String> groupchatList;
    public TextField groupMessageField;

    private MessageService messageService;
    private UserService userService;
    ObservableList<User> modelFriends = FXCollections.observableArrayList();
    ObservableList<String> messages = FXCollections.observableArrayList();
    ObservableList<String> groupchatFriends = FXCollections.observableArrayList();

    User friend;

    public void initFriends()
    {
        Map<User, LocalDateTime> allFriends = userService.getFriends(HomeController.activeUser.getId());
        List<User> friendsList = new ArrayList<>();
        for (Map.Entry<User,LocalDateTime> entry : allFriends.entrySet())
            friendsList.add(entry.getKey());
        modelFriends.setAll(friendsList);
    }

    public void initMessages(User friend)
    {
        List<Message> conversation = this.messageService.getConversation(HomeController.activeUser.getId(), friend.getId());
        List<String> list = new ArrayList<>();
        for (Message x : conversation)
        {
            if(x.getFrom().equals(HomeController.activeUser.getId()))
                list.add("Me: " + x.getMessage());
            else
                list.add(this.userService.findUser(x.getFrom()).getFirstName() + ": " + x.getMessage());
        }
        this.messages.setAll(list);
    }

    public void initGroupChatMessages(ArrayList<User> friends)
    {

    }

    @FXML
    public void initialize()
    {
        final String url = ApplicationContext.getPROPERTIES().getProperty("database.socialnetwork.url");
        final String username = ApplicationContext.getPROPERTIES().getProperty("database.socialnetwork.username");
        final String password = ApplicationContext.getPROPERTIES().getProperty("database.socialnetwork.password");

        Repository<Long, User> userDatabaseRepository = new UserDatabaseRepository(url, username, password);
        Repository<Tuple<Long, Long>, Friendship> friendshipDatabaseRepository = new FriendshipDatabaseRepository(url, username, password);
        Repository<String, Account> accountDatabaseRepository = new AccountDatabaseRepository(url, username, password);
        Repository<Long, Message> messageDatabaseRepository = new MessageDatabaseRepository(url, username, password);

        this.userService = new UserService(userDatabaseRepository, friendshipDatabaseRepository, accountDatabaseRepository, new UserValidator(), new AccountValidator());
        this.messageService = new MessageService(messageDatabaseRepository, friendshipDatabaseRepository, new MessageValidator());
        this.messageService.addObserver(this);

        this.friendColumnFirstName.setCellValueFactory(new PropertyValueFactory<User, String>("firstName"));
        this.friendColumnLastName.setCellValueFactory(new PropertyValueFactory<User, String>("lastName"));

        this.friendListColumn.setCellValueFactory(new PropertyValueFactory<String, String>("Friends"));

        this.groupchatTable.setItems(this.groupchatFriends);
        this.groupchatTable.setOnMouseClicked(new EventHandler<MouseEvent>()
        {
            @Override
            public void handle(MouseEvent event)
            {
                String friends = groupchatTable.getSelectionModel().getSelectedItem();
                String[] friendList = friends.split(" ");
                ArrayList<User> users = new ArrayList<>();
                for(String f : friendList)
                {
                    users.add(userService.findUserByName(f));
                }
                initGroupChatMessages(users);
            }
        });

        this.friendsTable.setItems(this.modelFriends);
        this.initFriends();

        this.errorMessage.setText("");

        this.friendsTable.getSelectionModel().setSelectionMode(SelectionMode.MULTIPLE);

        this.friendsTable.setOnMouseClicked(new EventHandler<MouseEvent>()
        {
            @Override
            public void handle(MouseEvent event)
            {
                friend = (User)friendsTable.getSelectionModel().getSelectedItem();
                if(friend != null)
                {
                    initMessages(friend);
                    messageList.setItems(messages);
                }
            }
        });

        this.messageField.setOnKeyPressed(new EventHandler<KeyEvent>()
        {
            @Override
            public void handle(KeyEvent event)
            {
                if(event.getCode().equals(KeyCode.ENTER))
                {
                    String text = messageField.getText();
                    ArrayList<Long> to = new ArrayList<>();
                    to.add(friend.getId());
                    Message message = new Message(HomeController.activeUser.getId(), to, text, LocalDateTime.now());
                    try
                    {
                        messageService.sendMessage(message);
                        errorMessage.setText("");
                    }catch (MyException e)
                    {
                        errorMessage.setText(e.getMessage());
                        errorMessage.setTextFill(Color.DARKRED);
                    } catch (NoSuchPaddingException | NoSuchAlgorithmException | InvalidKeyException | InvalidAlgorithmParameterException | IllegalBlockSizeException | BadPaddingException e) {
                        e.printStackTrace();
                    }
                    messageField.clear();
                }
            }
        });
    }

    @Override
    public void update(MessageEvent messageEvent)
    {
        this.initMessages(friend);
        this.initFriends();
    }


    public void handleSendToAll(ActionEvent actionEvent)
    {
        List<User> all = friendsTable.getSelectionModel().getSelectedItems();

        String text = messageField.getText();
        ArrayList<Long> to = new ArrayList<>();

        for(User it: all)
            to.add(it.getId());

        Message message = new Message(HomeController.activeUser.getId(), to, text, LocalDateTime.now());
        try
        {
            this.messageService.sendMessage(message);
            this.errorMessage.setText("");
        }catch (MyException e)
        {
            this.errorMessage.setText(e.getMessage());
            this.errorMessage.setTextFill(Color.DARKRED);
        } catch (NoSuchPaddingException | NoSuchAlgorithmException | InvalidKeyException | InvalidAlgorithmParameterException | IllegalBlockSizeException | BadPaddingException e) {
            e.printStackTrace();
        }
        this.messageField.clear();
    }
}
