package socialnetwork.domain.console;

import socialnetwork.MyException;
import socialnetwork.config.ApplicationContext;
import socialnetwork.domain.Account;
import socialnetwork.domain.Friendship;
import socialnetwork.domain.Tuple;
import socialnetwork.domain.User;
import socialnetwork.domain.validators.AccountValidator;
import socialnetwork.domain.validators.FriendshipValidator;
import socialnetwork.domain.validators.UserValidator;
import socialnetwork.repository.Repository;
import socialnetwork.repository.database.AccountDatabaseRepository;
import socialnetwork.repository.database.FriendshipDatabaseRepository;
import socialnetwork.repository.database.UserDatabaseRepository;
import socialnetwork.service.FriendshipService;
import socialnetwork.service.UserService;

import java.time.LocalDateTime;
import java.util.List;
import java.util.Map;
import java.util.Scanner;

/*
public class Console
{
    private final UserService userService;
    private final FriendshipService friendshipService;

    private final Scanner scan;

    public Console()
    {
        final String url = ApplicationContext.getPROPERTIES().getProperty("database.socialnetwork.url");
        final String username= ApplicationContext.getPROPERTIES().getProperty("database.socialnetwork.username");
        final String password= ApplicationContext.getPROPERTIES().getProperty("database.socialnetwork.password");

        Repository<Long, User> userDatabaseRepository = new UserDatabaseRepository(url, username, password);
        Repository<Tuple<Long, Long>, Friendship> friendshipDatabaseRepository = new FriendshipDatabaseRepository(url, username, password);
        Repository<String, Account> accountDatabaseRepository = new AccountDatabaseRepository(url, username, password);

        this.userService = new UserService(userDatabaseRepository, friendshipDatabaseRepository, accountDatabaseRepository, new UserValidator(), new AccountValidator());
        this.friendshipService = new FriendshipService(userDatabaseRepository, friendshipDatabaseRepository, new FriendshipValidator());

        scan = new Scanner(System.in);
    }

    public void displayMenu()
    {
        System.out.println("Menu:");
        System.out.println("1: Add user.\n" +
                "2: Remove user.\n" +
                "3: Display number of communities.\n" +
                "4: Display the most friendly community.\n" +
                "5: Display all users.\n" +
                "6: Show all friends of a user.\n" +
                "7: Show all friends of a user by month.\n" +
                "8: Enter login menu.\n" +
                "0: Exit.");
    }

    public void addUser()
    {
        System.out.println("Enter ID:");
        String input = this.scan.nextLine();
        if(input.matches(".*\\D+.*"))
        {
            System.out.println("Invalid ID!");
            return;
        }
        long id = Long.parseLong(input);

        System.out.println("Enter first name:");
        String firstName = this.scan.nextLine();

        System.out.println("Enter last name:");
        String lastName = this.scan.nextLine();

        User user = new User(firstName, lastName);
        user.setId(id);

        try
        {
            if(this.userService.addUser(user) == null)
                System.out.println("User added successfully!");
        }catch (MyException e)
        {
            System.out.println(e.getMessage());
        }
    }

    public void removeUser()
    {
        System.out.println("Enter ID:");
        String input = this.scan.nextLine();
        if(input.matches(".*\\D+.*"))
        {
            System.out.println("Invalid ID!");
            return;
        }
        long id = Long.parseLong(input);

        try
        {
            User user = this.userService.deleteUser(id);
            System.out.println("User " + user.getFirstName() + " " + user.getLastName() + " deleted successfully!");
        }catch (MyException e)
        {
            System.out.println(e.getMessage());
        }
    }

    public void displayAllUsers()
    {
        this.userService.getAll().forEach(System.out::println);
    }

    public void displayNumberOfCommunities() { System.out.println("Number of communities: " + this.friendshipService.numberOfCommunities()); }

    public void displayTheMostFriendlyCommunity()
    {
        System.out.println("The most friendly community:");
        List<User> friends = this.friendshipService.getMostFriendlyCommunity();

        StringBuilder community = new StringBuilder("[ ");
        for(User friend : friends)
            community.append(friend.getFirstName()).append(" ");
        community.append("]");
        System.out.println(community.toString());
    }

    public void displayFriends()
    {
        System.out.println("Enter ID:");
        String input = this.scan.nextLine();
        if(input.matches(".*\\D+.*"))
        {
            System.out.println("Invalid ID!");
            return;
        }
        long id = Long.parseLong(input);

        Map<User, LocalDateTime> dto = this.userService.getFriends(id);
        if(dto.isEmpty())
            System.out.println("The given user has no friends :(");
        else
            dto.forEach((k, v) -> System.out.println(k.getFirstName() + " | " + k.getLastName() + " | " + v));
    }

    public void displayFriendsByMonth()
    {
        System.out.println("Enter ID:");
        String input = this.scan.nextLine();
        if(input.matches(".*\\D+.*"))
        {
            System.out.println("Invalid ID!");
            return;
        }
        long id = Long.parseLong(input);

        System.out.println("Enter the month (1-12):");
        input = this.scan.nextLine();
        if(!input.matches("1[0-2]|[1-9]"))
        {
            System.out.println("Invalid month!");
            return;
        }

        Map<User, LocalDateTime> dto = this.userService.getFriendsByMonth(id, Long.parseLong(input));
        if(dto.isEmpty())
            System.out.println("The given user has no friends :(");
        else
            dto.forEach((k, v) -> System.out.println(k.getFirstName() + " | " + k.getLastName() + " | " + v));
    }
}
*/