using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using log4net;
using TrackAndField.model;

namespace TrackAndField.repository
{
    class TrackRepository : ITrackRepository
    {
        private static readonly ILog logger = LogManager.GetLogger("TrackRepository");

        public TrackRepository()
        {
            logger.Info("Initializing TrackRepository class");
        }

        public IEnumerable<Track> FindAll()
        {
            logger.InfoFormat("Finding all tracks...");

            IList<Track> tracks = new List<Track>();

            var connection = DBUtils.GetConnection();

            using (var command = connection.CreateCommand())
            {
                command.CommandText = "SELECT * FROM Track";

                using (var dataReader = command.ExecuteReader())
                {
                    while (dataReader.Read())
                    {
                        string name = dataReader.GetString(0);
                        int minimumAge = dataReader.GetInt32(1);
                        int maximumAge = dataReader.GetInt32(2);
                        Track track = new Track(name, minimumAge, maximumAge);
                        tracks.Add(track);
                    }
                }
            }

            return tracks;
        }

        public Track FindOne(string id)
        {
            Track track = null;

            var connection = DBUtils.GetConnection();

            using (var command = connection.CreateCommand())
            {
                command.CommandText = "SELECT * FROM Track WHERE name = @id";

                var idParameter = command.CreateParameter();
                idParameter.ParameterName = "@id";
                idParameter.Value = id;
                command.Parameters.Add(idParameter);

                using (var dataReader = command.ExecuteReader())
                {
                    if (dataReader.Read())
                    {
                        string name = dataReader.GetString(0);
                        int minimumAge = dataReader.GetInt32(1);
                        int maximumAge = dataReader.GetInt32(2);
                        track = new Track(name, minimumAge, maximumAge);
                        logger.InfoFormat("Track found: {0}", track);
                    }
                }
            }

            return track;
        }

        public Track Save(Track entity)
        {
            var connection = DBUtils.GetConnection();

            using (var command = connection.CreateCommand())
            {
                command.CommandText = "INSERT INTO Track(name, minimumAge, maximumAge) VALUES (@name, @min, @max)";

                var nameParameter = command.CreateParameter();
                nameParameter.ParameterName = "@name";
                nameParameter.Value = entity.Name;
                command.Parameters.Add(nameParameter);

                var minParameter = command.CreateParameter();
                minParameter.ParameterName = "@min";
                minParameter.Value = entity.MinimumAge;
                command.Parameters.Add(minParameter);

                var maxParameter = command.CreateParameter();
                maxParameter.ParameterName = "@max";
                maxParameter.Value = entity.MaximumAge;
                command.Parameters.Add(maxParameter);

                var result = command.ExecuteNonQuery();
            }
            return entity;
        }
    }
}
