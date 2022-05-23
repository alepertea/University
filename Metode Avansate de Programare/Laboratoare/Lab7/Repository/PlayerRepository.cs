using Lab7.Domain;

namespace Lab7.Repository
{
    class PlayerRepository : InFileRepository<int, Player>
    {
        public PlayerRepository(string fileName) : base(fileName, EntityToFileMapping.CreatePlayer) { }
    }
}
