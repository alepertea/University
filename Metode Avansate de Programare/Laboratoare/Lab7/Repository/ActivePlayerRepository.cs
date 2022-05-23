using System;
using Lab7.Domain;

namespace Lab7.Repository
{
    class ActivePlayerRepository : InFileRepository<Tuple<int, int>, ActivePlayer>
    {
        public ActivePlayerRepository(string fileName) : base(fileName, EntityToFileMapping.CreateActivePlayer) { }
    }
}
