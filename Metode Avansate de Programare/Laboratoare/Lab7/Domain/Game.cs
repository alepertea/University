using System;

namespace Lab7.Domain
{
    class Game : Entity<int>
    {
        public Team FirstTeam { get; set; }
        public Team SecondTeam { get; set; }
        public DateTime Date { get; set; }

        public Game(int id, Team firstTeam, Team secondTeam)
        {
            this.ID = id;
            this.FirstTeam = firstTeam;
            this.SecondTeam = secondTeam;
        }
        public Game() { }
        public override string ToString()
        {
            return this.FirstTeam.Name + " vs. " + this.SecondTeam.Name + " | " + this.Date.ToString();
        }
    }
}
