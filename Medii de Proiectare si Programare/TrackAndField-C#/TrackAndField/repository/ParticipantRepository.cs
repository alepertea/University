using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using log4net;
using TrackAndField.model;

namespace TrackAndField.repository
{
    class ParticipantRepository : IParticipantRepository
    {
        private static readonly ILog logger = LogManager.GetLogger("ParticipantRepository");

        public ParticipantRepository()
        {
            logger.Info("Initializing ParticipantRepository class");
        }

        public IEnumerable<Participant> FindAll()
        {
            logger.InfoFormat("Finding all participants...");

            IList<Participant> participants = new List<Participant>();

            var connection = DBUtils.GetConnection();

            using (var command = connection.CreateCommand())
            {
                command.CommandText = "SELECT * FROM Participant";

                using (var dataReader = command.ExecuteReader())
                {
                    while (dataReader.Read())
                    {
                        string name = dataReader.GetString(0);
                        int age = dataReader.GetInt32(1);
                        Participant participant = new Participant(name, age);
                        participants.Add(participant);
                    }
                }
            }

            return participants;
        }

        public Participant FindOne(string id)
        {
            Participant participant = null;

            var connection = DBUtils.GetConnection();

            using (var command = connection.CreateCommand())
            {
                command.CommandText = "SELECT * FROM Participant WHERE participantName = @n";

                var nameParameter = command.CreateParameter();
                nameParameter.ParameterName = "@n";
                nameParameter.Value = id;
                command.Parameters.Add(nameParameter);

                using (var dataReader = command.ExecuteReader())
                {
                    while (dataReader.Read())
                    {
                        string name = dataReader.GetString(0);
                        int age = dataReader.GetInt32(1);
                        participant = new Participant(name, age);
                        logger.InfoFormat("Found participant: {0}", participant);
                    }
                }
            }

            return participant;
        }

        public Participant Save(Participant entity)
        {
            logger.InfoFormat("Saving participant...", entity);

            var connection = DBUtils.GetConnection();

            using (var command = connection.CreateCommand())
            {
                command.CommandText = "INSERT INTO Participant(participantName, age) VALUES (@n, @a)";

                var nameParameter = command.CreateParameter();
                nameParameter.ParameterName = "@n";
                nameParameter.Value = entity.Name;
                command.Parameters.Add(nameParameter);

                var ageParameter = command.CreateParameter();
                ageParameter.ParameterName = "@a";
                ageParameter.Value = entity.Age;
                command.Parameters.Add(ageParameter);

                var result = command.ExecuteNonQuery();

                return entity;
            }
        }
    }
}
