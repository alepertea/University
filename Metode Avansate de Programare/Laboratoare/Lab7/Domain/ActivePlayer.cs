using System;
using System.Collections.Generic;
using System.Text;

namespace Lab7.Domain
{
    enum Type
    {
        Substitute, Participant
    }

    class ActivePlayer : Entity<Tuple<int, int>>
    {
        public int PlayerID { get; set; }
        public int GameID { get; set; }
        public int ScoredPoints { get; set; }
        public Type Type { get; set; }

        public ActivePlayer(int playerID, int gameID, int scoredPoints, Type type)
        {
            this.ID = new Tuple<int, int>(playerID, gameID);
            this.PlayerID = playerID;
            this.GameID = gameID;
            this.ScoredPoints = scoredPoints;
            this.Type = type;
        }
        public ActivePlayer() { }
        public override string ToString()
        {
            return "Player ID: " + this.PlayerID + " | Game ID: " + this.GameID + " | Points: " + this.ScoredPoints + " | Type: " + this.Type;
        }
    }
}
