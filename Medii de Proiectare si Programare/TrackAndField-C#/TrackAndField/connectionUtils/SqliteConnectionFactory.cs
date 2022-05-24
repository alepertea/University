using System;
using System.Collections.Generic;
using System.Data;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Configuration;
using System.Data.SQLite;

namespace TrackAndField.connectionUtils
{
    class SqliteConnectionFactory : ConnectionFactory
    {
        public override IDbConnection CreateConnection()
        {
            string connectionString = ConfigurationManager.ConnectionStrings["trackandfieldDB"].ConnectionString;
            return new SQLiteConnection(connectionString);
        }
    }
}
