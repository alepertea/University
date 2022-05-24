
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

public class DatabaseContext {

    public DatabaseContext() {
    }

    public DbSet<User> Users;

    public DbSet<Account> Accounts;

    /// <summary>
    /// @return
    /// </summary>
    public DbConnection GetConnection() {
        // TODO implement here
        return null;
    }

    /// <summary>
    /// @param modelBuilder 
    /// @return
    /// </summary>
    public void OnModelCreating(DbModelBuilder modelBuilder) {
        // TODO implement here
        return null;
    }

}