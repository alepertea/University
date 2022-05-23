package socialnetwork.domain;

import java.time.LocalDateTime;

public class Friendship extends Entity<Tuple<Long,Long>>
{
    LocalDateTime date;

    public Friendship() { this.date = LocalDateTime.now(); }

    /**
     *
     * @return the date when the friendship was created
     */
    public LocalDateTime getDate() { return this.date; }

    /**
     *
     * @param date - the new date assigned
     */
    public void setDate(LocalDateTime date) { this.date = date; }
}
