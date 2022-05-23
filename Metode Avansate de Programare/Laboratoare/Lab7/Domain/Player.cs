using System;
using System.Collections.Generic;
using System.Text;

namespace Lab7.Domain
{
    class Player : Student
    {
        public Team Team { get; set; }
        public Player(int id, string name, string school, Team team)
        {
            this.ID = id;
            this.Name = name;
            this.School = school;
            this.Team = team;
        }
        public Player() { }
        public override string ToString()
        {
            return base.ToString() + " | " + this.Team.Name;
        }
    }
}
