using System.Collections.Generic;
using Lab7.Domain;

namespace Lab7.Repository
{
    public delegate E CreateEntity<E>(string line);
    abstract class InFileRepository<ID, E> : InMemoryRepository<ID, E> where E : Entity<ID>
    {
        protected string fileName;
        protected CreateEntity<E> createEntity;

        public InFileRepository(string fileName, CreateEntity<E> createEntity)
        {
            this.fileName = fileName;
            this.createEntity = createEntity;
            if (this.createEntity != null)
                this.LoadFromFile();
        }

        protected virtual void LoadFromFile()
        {
            List<E> list = DataReader.ReadData(this.fileName, this.createEntity);
            list.ForEach(x => entities[x.ID] = x);
        }
    }
}
