using System;
using System.Collections.Generic;
using System.Globalization;
using System.Text;

namespace Lab7.Domain
{
    class EntityToFileMapping
    {
        public static Team CreateTeam(string line)
        {
            string[] fields = line.Split(";");
            Team team = new Team() 
            {
                ID = int.Parse(fields[0]), 
                Name = fields[1] 
            };
            return team;
        }
        public static Player CreatePlayer(string line)
        {
            string[] fields = line.Split(";");
            Player player = new Player()
            {
                ID = int.Parse(fields[0]),
                Name = fields[1],
                School = fields[2],
                Team = new Team(int.Parse(fields[3]), fields[4])
            };
            return player;
        }
        public static ActivePlayer CreateActivePlayer(string line)
        {
            string[] fields = line.Split(";");

            Type type;
            if (fields[3] == "Substitute")
                type = Type.Substitute;
            else
                type = Type.Participant;

            ActivePlayer activePlayer = new ActivePlayer()
            {
                ID = new Tuple<int, int>(int.Parse(fields[0]), int.Parse(fields[1])),
                PlayerID = int.Parse(fields[0]),
                GameID = int.Parse(fields[1]),
                ScoredPoints = int.Parse(fields[2]),
                Type = type
            };
            return activePlayer;
        }
        public static Game CreateGame(string line)
        {
            string[] fields = line.Split(";");

            Team firstTeam = new Team()
            {
                ID = int.Parse(fields[1]),
                Name = fields[2]
            };
            Team secondTeam = new Team()
            {
                ID = int.Parse(fields[3]),
                Name = fields[4]
            };

            Game game = new Game()
            {
                ID = int.Parse(fields[0]),
                FirstTeam = firstTeam,
                SecondTeam = secondTeam,
                Date = DateTime.ParseExact(fields[5], @"d/M/yyyy", null)
            };
            return game;
        }
    }
}
