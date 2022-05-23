using System;
using Lab7.Domain;

namespace Lab7.Repository
{
    class GameRepository : InFileRepository<int, Game>
    {
        public GameRepository(string fileName) : base(fileName, EntityToFileMapping.CreateGame) { }
    }
}
