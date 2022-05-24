
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

public interface IService {

    /// <summary>
    /// @param user 
    /// @return
    /// </summary>
    public User Login(User user);

    /// <summary>
    /// @param user 
    /// @return
    /// </summary>
    public void Logout(User user);

    /// <summary>
    /// @param account 
    /// @return
    /// </summary>
    public User FindUser(Account account);

    /// <summary>
    /// @param entity 
    /// @return
    /// </summary>
    public User UpdateUser(User entity);

    /// <summary>
    /// @return
    /// </summary>
    public IEnumerable<Account> FindAllAccounts();

    /// <summary>
    /// @param username 
    /// @param password 
    /// @return
    /// </summary>
    public Account FindAccount(String username, String password);

    /// <summary>
    /// @param entity 
    /// @return
    /// </summary>
    public void SaveAccount(Account entity);

    /// <summary>
    /// @param entity 
    /// @return
    /// </summary>
    public void UpdateAccount(Account entity);

    /// <summary>
    /// @param entity 
    /// @return
    /// </summary>
    public void DeleteAccount(Account entity);

}