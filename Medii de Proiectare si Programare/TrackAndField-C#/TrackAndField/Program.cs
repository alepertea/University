using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using TrackAndField.repository;
using TrackAndField.model;

namespace TrackAndField
{
    class Program
    {
        static void Main(string[] args)
        {
            UserRepository userRepository = new UserRepository();
            TrackRepository trackRepository = new TrackRepository();
            ParticipantRepository participantRepository = new ParticipantRepository();
            RegistrationRepository registrationRepository = new RegistrationRepository();

            /*
            Participant p1 = new Participant("Razvan", 15);
            Participant p2 = new Participant("Tani", 7);
            participantRepository.Save(p1);
            participantRepository.Save(p2);

            trackRepository.Save(new Track("50m", 6, 15));
            Track t1 = new Track("100m", 6, 15);
            Track t2 = new Track("1000m", 9, 15);
            Track t3 = new Track("1500m", 9, 15);
            trackRepository.Save(t1);
            trackRepository.Save(t2);
            trackRepository.Save(t3);

            registrationRepository.Save(new Registration(p1, t1));
            registrationRepository.Save(new Registration(p2, t3));
            registrationRepository.Save(new Registration(p2, t2));
            */

            IEnumerable<Track> tracks = trackRepository.FindAll();
            Console.WriteLine("Tracks:");
            foreach(Track t in tracks)
            {
                Console.WriteLine(t);
            }
            IEnumerable<Participant> participants = participantRepository.FindAll();
            Console.WriteLine("Participants:");
            foreach(Participant p in participants)
            {
                Console.WriteLine(p);
            }
            IEnumerable<Registration> registrations = registrationRepository.FindAll();
            Console.WriteLine("Registrations:");
            foreach(Registration r in registrations)
            {
                Console.WriteLine(r);
            }

            Console.ReadKey();
        }
    }
}
