using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace TrackAndField.model
{
    class Registration : Entity<Tuple<Participant, Track>>
    {
        public Participant Participant { get; set; }
        public Track Track { get; set; }

        public Registration(Participant participant, Track track)
        {
            ID = new Tuple<Participant, Track>(participant, track);
            Participant = participant;
            Track = track;
        }

        public override string ToString()
        {
            return "Participant: " + Participant + " | Track: " + Track;
        }
    }
}
