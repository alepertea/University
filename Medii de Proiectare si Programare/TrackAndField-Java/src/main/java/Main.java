import model.Participant;
import model.Registration;
import model.Track;
import model.User;
import repository.ParticipantRepository;
import repository.RegistrationRepository;
import repository.TrackRepository;
import repository.UserRepository;

import java.io.FileReader;
import java.io.IOException;
import java.util.Map;
import java.util.Properties;

public class Main {
    public static void main(String[] args) {
        Properties props = new Properties();
        try {
            props.load(new FileReader("bd.config"));
        } catch (IOException e) {
            System.out.println("Cannot find bd.config " + e);
        }

        Participant p1 = new Participant("Ale", 11);
        Participant p2 = new Participant("Razvan", 15);
        Participant p3 = new Participant("Tani", 7);
        Track t1 = new Track("50m", 6, 15);
        Track t2 = new Track("100m", 6, 15);
        Track t3 = new Track("1000m", 9, 15);
        Track t4 = new Track("1500m", 9, 15);

        ParticipantRepository participantRepository = new ParticipantRepository(props);
        participantRepository.save(p1); participantRepository.save(p2); participantRepository.save(p3);

        TrackRepository trackRepository = new TrackRepository(props);
        trackRepository.save(t1); trackRepository.save(t2); trackRepository.save(t3); trackRepository.save(t4);

        UserRepository userRepository = new UserRepository(props);
        userRepository.save(new User("user1", "user1"));

        RegistrationRepository registrationRepository = new RegistrationRepository(props);
        registrationRepository.save(new Registration(p1, t1));
        registrationRepository.save(new Registration(p2, t3));
        registrationRepository.save(new Registration(p2, t4));
        registrationRepository.save(new Registration(p3, t3));

        Iterable<User> users = userRepository.findAll();
        Iterable<Track> tracks = trackRepository.findAll();
        Iterable<Participant> participants = participantRepository.findAll();
        Iterable<Registration> registrations = registrationRepository.findAll();
        Map<Participant, Integer> map = registrationRepository.getParticipantsByTrackAndAgeGroup(t3, "6-15");

        System.out.println("Users:");
        for(User user : users) {
            System.out.println(user);
        }

        System.out.println("Tracks:");
        for(Track track : tracks) {
            System.out.println(track);
        }

        System.out.println("Participants:");
        for(Participant participant : participants) {
            System.out.println(participant);
        }

        System.out.println("Registrations:");
        for(Registration registration : registrations) {
            System.out.println(registration);
        }

        System.out.println("Participants by track and age group:");
        for(var k : map.keySet()) {
            System.out.println(k + " -> " + map.get(k));
        }
    }
}
