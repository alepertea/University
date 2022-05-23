package socialnetwork.service;

import socialnetwork.domain.User;
import socialnetwork.repository.Repository;



import java.util.List;
import java.util.Optional;

import java.util.stream.Collectors;
import java.util.stream.StreamSupport;

public class UtilizatorService {
    private Repository<Long, User> repo;

    public UtilizatorService(Repository<Long, User> repo) {
        this.repo = repo;
    }

    public Optional<User> addUtilizator(User user) {
        return repo.save(user);
    }

    public List<User> getAllUsers() {
        Iterable<User> students = repo.findAll();
        return StreamSupport.stream(students.spliterator(), false).collect(Collectors.toList());
    }


    public List<User> filterUsersName(String s) {
        Iterable<User> students = repo.findAll();

        List<User> filteredUsers = StreamSupport.stream(students.spliterator(), false)
                .filter(user -> user.getFirstName().contains(s)).collect(Collectors.toList());


//        Set<Utilizator> filteredUsers1= new HashSet<>();
//        students.forEach(filteredUsers1::add);
//        filteredUsers1.removeIf(student -> !student.getFirstName().contains(s));

        return filteredUsers;
    }

    public Iterable<User> getAll(){
        return repo.findAll();
    }




    ///TO DO: add other methods
}
