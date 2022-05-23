using Lab7.Domain;

namespace Lab7.Repository
{
    class TeamRepository : InFileRepository<int, Team>
    {
        public TeamRepository(string fileName) : base(fileName, EntityToFileMapping.CreateTeam) { }
    }
}
