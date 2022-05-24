
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace interfaces{
    public interface IAccountRepository : ICrudRepository {


        /// <summary>
        /// @param username 
        /// @param password 
        /// @return
        /// </summary>
        public Account FindAccount(String username, String password);

    }
}