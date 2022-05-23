using System.Collections.Generic;
using System.IO;

namespace Lab7.Repository
{
    class DataReader
    {
        public static List<T> ReadData<T>(string fileName, CreateEntity<T> createEntity)
        {
            List<T> list = new List<T>();
            using(StreamReader reader = new StreamReader(fileName))
            {
                string s;
                while((s = reader.ReadLine()) != null)
                {
                    T entity = createEntity(s);
                    list.Add(entity);
                }
            }
            return list;
        }
    }
}
