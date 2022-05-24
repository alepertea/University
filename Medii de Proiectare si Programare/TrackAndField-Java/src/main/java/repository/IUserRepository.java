package repository;

import model.User;

public interface IUserRepository extends ICrudRepository<String, User> {
    User findByUsernameAndPassword(String username, String password);
}
