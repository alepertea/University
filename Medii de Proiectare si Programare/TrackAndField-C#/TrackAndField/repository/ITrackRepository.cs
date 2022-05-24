using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using TrackAndField.model;

namespace TrackAndField.repository
{
    interface ITrackRepository : ICrudRepository<string, Track> { }
}
