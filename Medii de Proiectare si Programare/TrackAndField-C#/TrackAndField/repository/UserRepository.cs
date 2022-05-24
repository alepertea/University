using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using TrackAndField.model;
using System.Data.SQLite;
using TrackAndField.connectionUtils;
using System.Data.SqlClient;
using Microsoft.Data.Sqlite;

namespace TrackAndField.repository
{
    class UserRepository : IUserRepository
    {
        public IEnumerable<User> FindAll()
        {
            IList<User> users = new List<User>();

            var connection = DBUtils.GetConnection();

            using (var command = connection.CreateCommand())
            {
                command.CommandText = "SELECT * FROM User";

                using (var dataReader = command.ExecuteReader())
                {
                    while (dataReader.Read())
                    {
                        string username = dataReader.GetString(0);
                        string password = dataReader.GetString(1);
                        User user = new User(username, password);
                        users.Add(user);
                    }
                }
            }

            return users;
        }

        public User FindByUsernameAndPassword(string username, string password)
        {
            User user = null;

            var connection = DBUtils.GetConnection();

            using (var command = connection.CreateCommand())
            {
                command.CommandText = "SELECT * FROM User WHERE username = @u AND password = @p";

                var usernameParameter = command.CreateParameter();
                usernameParameter.ParameterName = "@u";
                usernameParameter.Value = username;
                command.Parameters.Add(usernameParameter);

                var passwordParameter = command.CreateParameter();
                passwordParameter.ParameterName = "@p";
                passwordParameter.Value = password;
                command.Parameters.Add(passwordParameter);

                using (var dataReader = command.ExecuteReader())
                {
                    if (dataReader.Read())
                    {
                        string uName = dataReader.GetString(0);
                        string passwd = dataReader.GetString(1);
                        user = new User(username, password);
                    }
                }
            }

            return user;
        }

        public User FindOne(string id)
        {
            User user = null;

            var connection = DBUtils.GetConnection();

            using (var command = connection.CreateCommand())
            {
                command.CommandText = "SELECT * FROM User WHERE username = @id";

                var idParameter = command.CreateParameter();
                idParameter.ParameterName = "@id";
                idParameter.Value = id;
                command.Parameters.Add(idParameter);

                using (var dataReader = command.ExecuteReader())
                {
                    if (dataReader.Read())
                    {
                        string username = dataReader.GetString(0);
                        string password = dataReader.GetString(1);
                        user = new User(username, password);
                    }
                }
            }

            return user;
        }

        public User Save(User entity)
        {
            var connection = DBUtils.GetConnection();

            using (var command = connection.CreateCommand())
            {
                command.CommandText = "INSERT INTO User(username, password) VALUES (@u, @p)";

                var usernameParameter = command.CreateParameter();
                usernameParameter.ParameterName = "@u";
                usernameParameter.Value = entity.Username;
                command.Parameters.Add(usernameParameter);

                var passwordParameter = command.CreateParameter();
                passwordParameter.ParameterName = "@p";
                passwordParameter.Value = entity.Password;
                command.Parameters.Add(passwordParameter);

                var result = command.ExecuteNonQuery();

                return entity;
            }
        }
    }
}
