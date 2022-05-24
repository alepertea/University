using System;
using System.Collections.Generic;
using System.Data;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace TrackAndField.repository
{
    class DBUtils
    {
		private static IDbConnection instance = null;
		public static IDbConnection GetConnection()
		{
			if (instance == null || instance.State == ConnectionState.Closed)
			{
				instance = GetNewConnection();
				instance.Open();
			}
			return instance;
		}

		private static IDbConnection GetNewConnection()
		{
			return connectionUtils.ConnectionFactory.GetInstance().CreateConnection();
		}
	}
}
