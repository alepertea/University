package socialnetwork.controller;

import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.control.TableColumn;
import javafx.scene.control.TableView;
import javafx.scene.control.cell.PropertyValueFactory;
import javafx.scene.paint.Color;
import socialnetwork.MyException;
import socialnetwork.config.ApplicationContext;
import socialnetwork.domain.FriendRequest;
import socialnetwork.domain.Friendship;
import socialnetwork.domain.Tuple;
import socialnetwork.domain.User;
import socialnetwork.domain.validators.FriendRequestValidator;
import socialnetwork.event.ChangeEventType;
import socialnetwork.event.FriendRequestEvent;
import socialnetwork.observer.Observer;
import socialnetwork.repository.Repository;
import socialnetwork.repository.database.FriendRequestDatabaseRepository;
import socialnetwork.repository.database.FriendshipDatabaseRepository;
import socialnetwork.repository.database.UserDatabaseRepository;
import socialnetwork.service.FriendRequestService;

import javax.crypto.BadPaddingException;
import javax.crypto.IllegalBlockSizeException;
import javax.crypto.NoSuchPaddingException;
import java.security.InvalidAlgorithmParameterException;
import java.security.InvalidKeyException;
import java.security.NoSuchAlgorithmException;
import java.time.LocalDateTime;
import java.util.List;
import java.util.stream.Collectors;
import java.util.stream.StreamSupport;

public class FriendRequestsController implements Observer<FriendRequestEvent>
{
    public TableView<FriendRequest> requestsSentTable;
    public TableColumn<FriendRequest, String> toColumnSent;
    public TableColumn<FriendRequest, String> statusColumnSent;
    public TableColumn<FriendRequest, LocalDateTime> dateColumnSent;

    public TableView<FriendRequest> requestsReceivedTable;
    public TableColumn<FriendRequest, String> fromColumnReceived;
    public TableColumn<FriendRequest, String> statusColumnReceived;
    public TableColumn<FriendRequest, LocalDateTime> dateColumnReceived;

    public Button buttonAccept;
    public Button buttonReject;
    public Label messageToUserForRequest;
    public Button buttonRemove;

    private FriendRequestService friendRequestService;

    ObservableList<FriendRequest> modelSent;
    ObservableList<FriendRequest> modelReceived;

    @FXML
    public void initialize()
    {
        final String url = ApplicationContext.getPROPERTIES().getProperty("database.socialnetwork.url");
        final String username= ApplicationContext.getPROPERTIES().getProperty("database.socialnetwork.username");
        final String password= ApplicationContext.getPROPERTIES().getProperty("database.socialnetwork.password");

        Repository<Tuple<Long, Long>, FriendRequest> friendRequestRepository = new FriendRequestDatabaseRepository(url, username, password);
        Repository<Tuple<Long, Long>, Friendship> friendshipRepository = new FriendshipDatabaseRepository(url, username, password);
        Repository<Long, User> userRepository = new UserDatabaseRepository(url, username, password);

        this.friendRequestService = new FriendRequestService(friendRequestRepository, userRepository, friendshipRepository, new FriendRequestValidator());

        this.modelSent = FXCollections.observableArrayList();
        this.modelReceived = FXCollections.observableArrayList();

        this.toColumnSent.setCellValueFactory(new PropertyValueFactory<FriendRequest, String>("to"));
        this.statusColumnSent.setCellValueFactory(new PropertyValueFactory<FriendRequest, String>("status"));
        this.dateColumnSent.setCellValueFactory(new PropertyValueFactory<FriendRequest, LocalDateTime>("date"));

        this.fromColumnReceived.setCellValueFactory(new PropertyValueFactory<FriendRequest, String>("from"));
        this.statusColumnReceived.setCellValueFactory(new PropertyValueFactory<FriendRequest, String>("status"));
        this.dateColumnReceived.setCellValueFactory(new PropertyValueFactory<FriendRequest, LocalDateTime>("date"));

        this.requestsSentTable.setItems(this.modelSent);
        this.initSent();

        this.requestsReceivedTable.setItems(this.modelReceived);
        this.initReceived();

        this.friendRequestService.addObserver(this);
    }

    public void initSent()
    {
        Iterable<FriendRequest> friendRequests = this.friendRequestService.getAll();
        List<FriendRequest> friendRequestList = StreamSupport.stream(friendRequests.spliterator() , false)
                .filter(x -> (x.getId().getLeft().equals(HomeController.activeUser.getId())))
                .collect(Collectors.toList());
        this.modelSent.setAll(friendRequestList);
    }

    public void initReceived()
    {
        Iterable<FriendRequest> friendRequests = this.friendRequestService.getAll();
        List<FriendRequest> friendRequestList = StreamSupport.stream(friendRequests.spliterator() , false)
                .filter(x -> (x.getId().getRight().equals(HomeController.activeUser.getId())))
                .collect(Collectors.toList());
        this.modelReceived.setAll(friendRequestList);
    }

    @Override
    public void update(FriendRequestEvent friendRequestEvent)
    {
        this.initSent();
        this.initReceived();
    }

    public void handleAcceptFriendRequest(ActionEvent actionEvent)
    {
        FriendRequest selected = (FriendRequest) this.requestsReceivedTable.getSelectionModel().getSelectedItem();
        if (selected != null)
        {
            try
            {
                this.friendRequestService.accept(selected.getFrom(), HomeController.activeUser.getId());
                this.messageToUserForRequest.setText("Friend request accepted!");
                this.messageToUserForRequest.setTextFill(Color.DARKGREEN);
            } catch (MyException e)
            {
                this.messageToUserForRequest.setText(e.getMessage());
                this.messageToUserForRequest.setTextFill(Color.DARKRED);
            } catch (NoSuchPaddingException | NoSuchAlgorithmException | InvalidKeyException | InvalidAlgorithmParameterException | IllegalBlockSizeException | BadPaddingException e) {
                e.printStackTrace();
            }
        }
        else
        {
            this.messageToUserForRequest.setText("No request selected!");
            this.messageToUserForRequest.setTextFill(Color.DARKRED);
        }
    }

    public void handleRejectFriendRequest(ActionEvent actionEvent)
    {
        FriendRequest selected = (FriendRequest) this.requestsReceivedTable.getSelectionModel().getSelectedItem();
        if(selected != null)
        {
            try
            {
                this.friendRequestService.reject(selected.getFrom(), HomeController.activeUser.getId());
                this.messageToUserForRequest.setText("Friend request rejected!");
                this.messageToUserForRequest.setTextFill(Color.DARKGREEN);
            } catch (MyException e)
            {
                this.messageToUserForRequest.setText(e.getMessage());
                this.messageToUserForRequest.setTextFill(Color.DARKRED);
            }
        }
        else
        {
            this.messageToUserForRequest.setText("No request selected!");
            this.messageToUserForRequest.setTextFill(Color.DARKRED);
        }
    }

    public void handleRemove(ActionEvent actionEvent)
    {
        FriendRequest selected = (FriendRequest) this.requestsSentTable.getSelectionModel().getSelectedItem();
        if(selected != null)
        {
            try
            {
                this.friendRequestService.remove(HomeController.activeUser.getId(), selected.getTo());
                this.messageToUserForRequest.setText("Friend request removed!");
                this.messageToUserForRequest.setTextFill(Color.DARKGREEN);
            } catch (MyException e)
            {
                this.messageToUserForRequest.setText(e.getMessage());
                this.messageToUserForRequest.setTextFill(Color.DARKRED);
            }
        }
        else
        {
            this.messageToUserForRequest.setText("No request selected!");
            this.messageToUserForRequest.setTextFill(Color.DARKRED);
        }
    }
}
