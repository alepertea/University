package model;

public class Registration extends Entity<Tuple<Participant, Track>> {
    private Participant participant;
    private Track track;

    public Registration(Participant participant, Track track) {
        this.setId(new Tuple<>(participant, track));
        this.participant = participant;
        this.track = track;
    }

    public Participant getParticipant() {
        return participant;
    }

    public void setParticipantID(Participant participant) {
        this.participant = participant;
    }

    public Track getTrack() {
        return track;
    }

    public void setTrack(Track track) {
        this.track = track;
    }

    @Override
    public String toString() {
        return "Participant: " + this.participant + " | Track: " + this.track;
    }
}
