using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using TrackAndField.model;

namespace TrackAndField.repository
{
    interface IUserRepository : ICrudRepository<string, User> 
    {
        User FindByUsernameAndPassword(string username, string password);
    }
}
