using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace TrackAndField.model
{
    class Participant : Entity<string>
    {
        public string Name { get; set; }
        public int Age { get; set; }

        public Participant(string name, int age)
        {
            Name = name;
            Age = age;
        }
        public override string ToString()
        {
            return Name + " | " + Age;
        }
    }
}
