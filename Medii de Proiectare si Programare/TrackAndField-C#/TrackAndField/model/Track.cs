using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace TrackAndField.model
{
    class Track : Entity<string>
    {
        public string Name { get; set; }
        public int MinimumAge { get; set; }
        public int MaximumAge { get; set; }
        public Track(string name, int minimumAge, int maximumAge)
        {
            ID = name;
            Name = name;
            MinimumAge = minimumAge;
            MaximumAge = maximumAge;
        }
        public override string ToString()
        {
            return Name + " | min age: " + MinimumAge + " | max age: " + MaximumAge;
        }
    }
}
