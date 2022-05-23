package socialnetwork.service;

import socialnetwork.domain.User;
import socialnetwork.repository.Repository0;

public class UtilizatorService0 {
    private Repository0<Long, User> repo;

    public UtilizatorService0(Repository0<Long, User> repo) {
        this.repo = repo;
    }

    public User addUtilizator(User messageTask) {
        User task = repo.save(messageTask);
        return task;
    }

    public Iterable<User> getAll(){
        return repo.findAll();
    }

    ///TO DO: add other methods
}
