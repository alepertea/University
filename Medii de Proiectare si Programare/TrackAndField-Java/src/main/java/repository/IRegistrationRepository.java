package repository;

import model.*;

import java.util.Map;

public interface IRegistrationRepository extends ICrudRepository<Tuple<Participant, Track>, Registration> {
    /**
     *
     * @param track
     * @param ageGroup
     * @return all participants registered by track & age group and the number of registrations per participant
     */
    Map<Participant, Integer> getParticipantsByTrackAndAgeGroup(Track track, String ageGroup);
}
