package socialnetwork.domain.console;

import socialnetwork.MyException;
import socialnetwork.config.ApplicationContext;
import socialnetwork.domain.*;
import socialnetwork.domain.validators.*;
import socialnetwork.repository.Repository;
import socialnetwork.repository.database.FriendRequestDatabaseRepository;
import socialnetwork.repository.database.FriendshipDatabaseRepository;
import socialnetwork.repository.database.MessageDatabaseRepository;
import socialnetwork.repository.database.UserDatabaseRepository;
import socialnetwork.service.FriendRequestService;
import socialnetwork.service.FriendshipService;
import socialnetwork.service.MessageService;
import socialnetwork.service.UserService;

import java.time.LocalDateTime;
import java.util.ArrayList;
import java.util.Map;
import java.util.Scanner;

/*
public class LoginConsole
{
    private final FriendRequestService friendRequestService;
    private final FriendshipService friendshipService;
    private final UserService userService;
    private final MessageService messageService;

    private Long username;

    private final Scanner scan;

    public LoginConsole()
    {
        final String url = ApplicationContext.getPROPERTIES().getProperty("database.socialnetwork.url");
        final String username= ApplicationContext.getPROPERTIES().getProperty("database.socialnetwork.username");
        final String password= ApplicationContext.getPROPERTIES().getProperty("database.socialnetwork.password");

        Repository<Tuple<Long,Long>, FriendRequest> friendRequestRepository = new FriendRequestDatabaseRepository(url, username, password);
        Repository<Tuple<Long,Long>, Friendship> friendshipRepository = new FriendshipDatabaseRepository(url, username, password);
        Repository<Long, User> userRepository = new UserDatabaseRepository(url, username, password);
        Repository<Long, Message> messageRepository = new MessageDatabaseRepository(url, username, password);

        this.friendRequestService = new FriendRequestService(friendRequestRepository, userRepository, friendshipRepository, new FriendRequestValidator());
        this.userService = new UserService(userRepository, friendshipRepository, new UserValidator(), new AccountValidator());
        this.messageService = new MessageService(messageRepository, friendshipRepository, new MessageValidator());
        this.friendshipService = new FriendshipService(userRepository, friendshipRepository, new FriendshipValidator());

        this.scan = new Scanner(System.in);

        this.username = null;
    }

    public void displayMenu()
    {
        System.out.println("Menu:");
        System.out.println(">> 1: Log in.\n" +
                ">> 2: Log out.\n" +
                ">> 3: Send friend request.\n" +
                ">> 4: Show all friend requests.\n" +
                ">> 5: Accept a friend request.\n" +
                ">> 6: Reject a friend request.\n" +
                ">> 7: Remove a friend.\n" +
                ">> 8: Send a message.\n" +
                ">> 9: Reply to a message\n" +
                ">> 0: Exit");
    }

    public void menu()
    {
        String command;
        this.displayMenu();
        while(true)
        {
            System.out.println(">> Command:");
            command = this.scan.nextLine();
            switch (command)
            {
                case "0": { this.userLogout(); System.out.println(">> Menu exited successfully!"); return; }
                case "1": { this.userLogin(); break; }
                case "2": { this.userLogout(); break; }
                case "3": { this.sendFriendRequest(); break; }
                case "4": { this.showAll(); break; }
                case "5": { this.acceptFriendRequest(); break; }
                case "6": { this.rejectFriendRequest(); break; }
                case "7": { this.removeFriend(); break; }
                case "8": { this.sendMessage(); break; }
                case "9": { this.replyActions(); break; }
                default: { System.out.println(">> Invalid command!"); break; }
            }
        }
    }

    private void replyActions()
    {
        if(this.username == null)
        {
            System.out.println(">> You were not logged in!");
            return;
        }

        System.out.println(">>> 1: Reply to one user.\n" +
                ">>> 2: Reply to all.\n" +
                ">>> 0: Exit.");
        String command;
        while(true)
        {
            System.out.println(">>> Command:");
            command = this.scan.nextLine();

            switch (command)
            {
                case "0": { return; }
                case "1": { this.replyToOne(); break; }
                case "2": { this.replyToAll(); break; }
                default: { System.out.println(">>> Invalid command!"); break; }
            }
        }
    }

    private void replyToAll()
    {
        System.out.println(">>> Enter ID of message you wish to reply to:");
        String input = this.scan.nextLine();
        if(input.matches(".*\\D+.*"))
        {
            System.out.println(">>> Invalid ID!");
            return;
        }
        long originalMessageId = Long.parseLong(input);

        System.out.println(">>> Enter the text:");
        String text = this.scan.nextLine();

        LocalDateTime date = LocalDateTime.now();

        Message originalMessage = this.messageService.getMessage(originalMessageId);
        if(originalMessage == null)
        {
            System.out.println(">>> Cannot find the message!");
            return;
        }

        ArrayList<Long> recipients = new ArrayList<>();

        originalMessage.getTo().add(originalMessage.getFrom());

        Message message = new Message(this.username, recipients, text, date);
        message.setOriginalMessageId(originalMessageId);
        message.setId(this.messageService.generateMessageID());
        try
        {
            this.messageService.replyToAll(message, originalMessage.getTo(), this.username);
        }catch (MyException e)
        {
            System.out.println(e.getMessage());
        }
    }

    private void replyToOne()
    {
        System.out.println(">>> Enter ID of message you wish to reply to:");
        String input = this.scan.nextLine();
        if(input.matches(".*\\D+.*"))
        {
            System.out.println(">>> Invalid ID!");
            return;
        }
        long originalMessageId = Long.parseLong(input);

        System.out.println(">>> Enter the text:");
        String text = this.scan.nextLine();

        LocalDateTime date = LocalDateTime.now();

        Message originalMessage = this.messageService.getMessage(originalMessageId);
        if(originalMessage == null)
        {
            System.out.println(">>> Cannot find the message!");
            return;
        }

        ArrayList<Long> recipients = new ArrayList<>();

        Message message = new Message(this.username, recipients, text, date);
        message.setOriginalMessageId(originalMessageId);
        message.setId(this.messageService.generateMessageID());

        try
        {
            this.messageService.replyToOne(message, originalMessage.getFrom());
        }catch (MyException e)
        {
            System.out.println(e.getMessage());
        }
    }

    private void removeFriend()
    {
        if(this.username == null)
        {
            System.out.println(">> You are not logged in!");
            return;
        }

        System.out.println(">> Enter ID:");
        String input = this.scan.nextLine();
        if(input.matches(".*\\D+.*"))
        {
            System.out.println(">> Invalid ID!");
            return;
        }
        long from = Long.parseLong(input);

        try
        {
            Friendship friendship = new Friendship();
            friendship.setId(new Tuple<>(from, this.username));

            this.friendshipService.removeFriendship(friendship);
            this.friendRequestService.remove(from, this.username);
            System.out.println("Friendship removed successfully!");
        }catch (MyException e)
        {
            System.out.println(e.getMessage());
        }
    }

    public void userLogin()
    {
        System.out.println(">> Enter username:");
        String input = this.scan.nextLine();
        if(input.matches(".*\\D+.*"))
        {
            System.out.println(">> Invalid username!");
            return;
        }
        this.username = Long.parseLong(input);

        boolean found = false;
        Iterable<User> users = this.userService.getAll();
        for(User user : users)
        {
            if (user.getId().equals(username))
            {
                found = true;
                break;
            }
        }
        if(!found)
        {
            System.out.println(">> Invalid username!");
            return;
        }

        System.out.println(">> Login successful!");
    }

    public void userLogout()
    {
        if(this.username == null)
        {
            System.out.println(">> You were not logged in!");
            return;
        }
        this.username = null;
        System.out.println(">> Logout successful!");
    }

    public void sendFriendRequest()
    {
        if(this.username == null)
        {
            System.out.println(">> You are not logged in!");
            return;
        }

        System.out.println(">> Enter ID:");
        String input = this.scan.nextLine();
        if(input.matches(".*\\D+.*"))
        {
            System.out.println(">> Invalid ID!");
            return;
        }
        long to = Long.parseLong(input);

        FriendRequest friendRequest = new FriendRequest(this.username, to);
        friendRequest.setId(new Tuple<>(this.username, to));
        try
        {
            this.friendRequestService.addFriendRequest(friendRequest);
            System.out.println(">> Friend request sent successfully!");
        }catch (MyException e)
        {
            System.out.println(e.getMessage());
        }
    }

    public void showAll()
    {
        if(this.username == null)
        {
            System.out.println(">> You are not logged in!");
            return;
        }
        Map<User, LocalDateTime> dto = this.friendRequestService.getAll(this.username);
        dto.forEach((k, v) -> System.out.println(">> ID = " + k.getId() + " | First name = " + k.getFirstName() + " | Last name = " + k.getLastName() + " | Date = " + v));
    }

    public void acceptFriendRequest()
    {
        if(this.username == null)
        {
            System.out.println(">> You are not logged in!");
            return;
        }

        System.out.println(">> Enter ID:");
        String input = this.scan.nextLine();
        if(input.matches(".*\\D+.*"))
        {
            System.out.println(">> Invalid ID!");
            return;
        }
        long from = Long.parseLong(input);

        try
        {
            this.friendRequestService.accept(from, this.username);
            System.out.println(">> Friendship formed successfully!");
        }catch (MyException e)
        {
            System.out.println(e.getMessage());
        }
    }

    public void rejectFriendRequest()
    {
        if(this.username == null)
        {
            System.out.println(">> You are not logged in!");
            return;
        }

        System.out.println(">> Enter ID:");
        String input = this.scan.nextLine();
        if(input.matches(".*\\D+.*"))
        {
            System.out.println(">> Invalid ID!");
            return;
        }
        long from = Long.parseLong(input);

        try
        {
            this.friendRequestService.reject(from, this.username);
            System.out.println(">> Friend request deleted successfully!");
        }catch (MyException e)
        {
            System.out.println(e.getMessage());
        }
    }

    public void sendMessage()
    {
        if(this.username == null)
        {
            System.out.println(">> You are not logged in!");
            return;
        }

        System.out.println("Enter the recipient/s:");
        String input = this.scan.nextLine();
        String[] arguments = input.split(" ");
        ArrayList<Long> recipients = new ArrayList<>();
        for(String arg : arguments)
        {
            User user = this.userService.findUser(Long.parseLong(arg));
            if(user != null)
            {
                recipients.add(Long.parseLong(arg));
            }
        }

        System.out.println("Enter the message:");
        String text = this.scan.nextLine();
        LocalDateTime date = LocalDateTime.now();

        Message message = new Message(this.username, recipients, text, date);
        message.setId(this.messageService.generateMessageID());

        try
        {
            this.messageService.sendMessage(message);
            System.out.println(">> Message sent successfully!");
        }catch (MyException e)
        {
            System.out.println(e.getMessage());
        }
    }
}
*/