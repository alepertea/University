package socialnetwork.domain;

import java.time.LocalDateTime;

public class Friendship extends Entity<Tuple<Long,Long>>
{
    LocalDateTime date;

    public Friendship() {}

    /**
     *
     * @return the date when the friendship was created
     */
    public LocalDateTime getDate() {
        return date;
    }
}
