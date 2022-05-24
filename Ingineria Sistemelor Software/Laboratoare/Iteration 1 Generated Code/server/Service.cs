
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

public class Service : IService {

    public Service() {
    }

    private IUserRepository userRepository;

    private IAccountRepository accountRepository;

    private void loggedUsers: IDictionary<String, IObserver>;






    /// <summary>
    /// @param account 
    /// @return
    /// </summary>
    public User FindUser(Account account) {
        // TODO implement here
        return null;
    }

    /// <summary>
    /// @param entity 
    /// @return
    /// </summary>
    public void UpdateUser(User entity) {
        // TODO implement here
        return null;
    }

    /// <summary>
    /// @return
    /// </summary>
    public IEnumerable<Account> FindAllAccounts() {
        // TODO implement here
        return null;
    }

    /// <summary>
    /// @param username 
    /// @param password 
    /// @return
    /// </summary>
    public Account FindAccount(String username, String password) {
        // TODO implement here
        return null;
    }

    /// <summary>
    /// @param entity 
    /// @return
    /// </summary>
    public void SaveAccount(Account entity) {
        // TODO implement here
        return null;
    }

    /// <summary>
    /// @param entity 
    /// @return
    /// </summary>
    public void UpdateAccount(Account entity) {
        // TODO implement here
        return null;
    }

    /// <summary>
    /// @param entity 
    /// @return
    /// </summary>
    public void DeleteAccount(Account entity) {
        // TODO implement here
        return null;
    }

    /// <summary>
    /// @param account 
    /// @param user 
    /// @return
    /// </summary>
    public void NotifyLoggedUsers(Account account, IObserver user) {
        // TODO implement here
        return null;
    }

}