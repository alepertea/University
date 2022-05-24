﻿using System;
using System.Collections.Generic;
using System.Data;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Threading.Tasks;

namespace TrackAndField.connectionUtils
{
    abstract class ConnectionFactory
    {
		protected ConnectionFactory() { }

		private static ConnectionFactory instance;

		public static ConnectionFactory GetInstance()
		{
			if (instance == null)
			{
				Assembly assem = Assembly.GetExecutingAssembly();
				Type[] types = assem.GetTypes();
				foreach (var type in types)
				{
					if (type.IsSubclassOf(typeof(ConnectionFactory)))
						instance = (ConnectionFactory)Activator.CreateInstance(type);
				}
			}
			return instance;
		}

		public abstract IDbConnection CreateConnection();
	}
}
