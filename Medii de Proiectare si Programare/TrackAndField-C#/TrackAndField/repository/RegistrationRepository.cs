using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using log4net;
using TrackAndField.model;

namespace TrackAndField.repository
{
    class RegistrationRepository : IRegistrationRepository
    {
        private static readonly ILog logger = LogManager.GetLogger("RegistrationRepository");

        public RegistrationRepository()
        {
            logger.Info("Initializing RegistrationRepository class");
        }

        public IEnumerable<Registration> FindAll()
        {
            logger.InfoFormat("Finding all registrations...");

            IList<Registration> registrations = new List<Registration>();

            var connection = DBUtils.GetConnection();

            using (var command = connection.CreateCommand())
            {
                command.CommandText = "SELECT * FROM Participant P " +
                "INNER JOIN Registration R ON P.participantName = R.participantID " +
                "INNER JOIN Track T ON T.name = R.trackID";

                using (var dataReader = command.ExecuteReader())
                {
                    while (dataReader.Read())
                    {
                        string participantName = dataReader.GetString(0);
                        int age = dataReader.GetInt32(1);
                        string trackName = dataReader.GetString(4);
                        int minimumAge = dataReader.GetInt32(5);
                        int maximumAge = dataReader.GetInt32(6);
                        Participant participant = new Participant(participantName, age);
                        Track track = new Track(trackName, minimumAge, maximumAge);
                        Registration registration = new Registration(participant, track);
                        registrations.Add(registration);
                    }
                }
            }

            return registrations;
        }

        public Registration FindOne(Tuple<Participant, Track> id)
        {
            logger.InfoFormat("Searching registration...");

            Registration registration = null;

            var connection = DBUtils.GetConnection();

            using (var command = connection.CreateCommand())
            {
                command.CommandText = "SELECT * FROM Participant P " +
                "INNER JOIN Registration R ON P.participantName = R.participantID " +
                "INNER JOIN Track T ON T.name = R.trackID " +
                "WHERE participantID = @p AND trackID = @t";

                var participantParameter = command.CreateParameter();
                participantParameter.ParameterName = "@p";
                participantParameter.Value = id.Item1.Name;
                command.Parameters.Add(participantParameter);

                var trackParameter = command.CreateParameter();
                trackParameter.ParameterName = "@t";
                trackParameter.Value = id.Item2.Name;
                command.Parameters.Add(trackParameter);

                using (var dataReader = command.ExecuteReader())
                {
                    if (dataReader.Read())
                    {
                        string participantName = dataReader.GetString(0);
                        int age = dataReader.GetInt32(1);
                        string trackName = dataReader.GetString(2);
                        int minimumAge = dataReader.GetInt32(3);
                        int maximumAge = dataReader.GetInt32(4);
                        Participant participant = new Participant(participantName, age);
                        Track track = new Track(trackName, minimumAge, maximumAge);
                        registration = new Registration(participant, track);
                    }
                }
            }

            return registration;
        }

        public Dictionary<Participant, int> GetParticipantsByTrackAndAgeGroup(Track track, string ageGroup)
        {
            Dictionary<Participant, int> participants = new Dictionary<Participant, int>();

            var connection = DBUtils.GetConnection();

            using (var command = connection.CreateCommand())
            {
                command.CommandText = "SELECT *, COUNT(participantName) AS [number] FROM Participant P " +
                "INNER JOIN Registration R ON P.participantName = R.participantID " +
                "WHERE trackID = @t AND age >= @a1 AND age <= @a2";

                var trackParameter = command.CreateParameter();
                trackParameter.ParameterName = "@t";
                trackParameter.Value = track.Name;
                command.Parameters.Add(trackParameter);

                var age1Parameter = command.CreateParameter();
                age1Parameter.ParameterName = "@a1";
                age1Parameter.Value = Int32.Parse(ageGroup.Split('-')[0]);
                command.Parameters.Add(age1Parameter);

                var age2Parameter = command.CreateParameter();
                age2Parameter.ParameterName = "@a2";
                age2Parameter.Value = Int32.Parse(ageGroup.Split('-')[1]);
                command.Parameters.Add(age2Parameter);

                using (var dataReader = command.ExecuteReader())
                {
                    while (dataReader.Read())
                    {
                        string participantName = dataReader.GetString(0);
                        int age = dataReader.GetInt32(1);
                        int number = dataReader.GetInt32(4);
                        Participant participant = new Participant(participantName, age);
                        participants.Add(participant, number);
                    }
                }
            }

            return participants;
        }

        public Registration Save(Registration entity)
        {
            logger.InfoFormat("Saving registration...");

            var connection = DBUtils.GetConnection();

            using (var command = connection.CreateCommand())
            {
                command.CommandText = "INSERT INTO Registration(participantID, trackID) VALUES (@p, @t)";

                var participantParameter = command.CreateParameter();
                participantParameter.ParameterName = "@p";
                participantParameter.Value = entity.Participant.Name;
                command.Parameters.Add(participantParameter);

                var trackParameter = command.CreateParameter();
                trackParameter.ParameterName = "@t";
                trackParameter.Value = entity.Track.Name;
                command.Parameters.Add(trackParameter);

                return entity;
            }
        }
    }
}
