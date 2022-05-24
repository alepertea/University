using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using TrackAndField.model;

namespace TrackAndField.repository
{
    interface IRegistrationRepository : ICrudRepository<Tuple<Participant, Track>, Registration> 
    {
        /**
         * param: track
         *        ageGroup
         * return: all participants registered by track & age group and the number of registrations per participant
         */
        Dictionary<Participant, int> GetParticipantsByTrackAndAgeGroup(Track track, string ageGroup);
    }
}
