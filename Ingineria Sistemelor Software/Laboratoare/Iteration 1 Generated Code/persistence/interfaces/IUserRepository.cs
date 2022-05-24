
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace interfaces{
    public interface IUserRepository : ICrudRepository {


        /// <summary>
        /// @param account 
        /// @return
        /// </summary>
        public User FindUser(Account account);

    }
}