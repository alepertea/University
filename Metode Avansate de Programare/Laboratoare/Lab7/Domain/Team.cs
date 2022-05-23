using System;
using System.Collections.Generic;
using System.Text;

namespace Lab7.Domain
{
    class Team : Entity<int>
    {
        public string Name { get; set; }

        public Team(int id, string name)
        {
            this.ID = id;
            this.Name = name;
        }

        public Team() { }
        public override string ToString()
        {
            return this.ID + " | " + this.Name;
        }
    }
}
