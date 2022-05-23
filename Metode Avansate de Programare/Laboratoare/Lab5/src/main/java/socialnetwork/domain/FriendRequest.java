package socialnetwork.domain;

import java.time.LocalDateTime;

public class FriendRequest extends Entity<Tuple<Long, Long>>
{
    private Long from;
    private Long to;
    private Status status;
    private LocalDateTime date;

    public FriendRequest(Long from, Long to)
    {
        this.from = from;
        this.to = to;
        this.status = Status.PENDING;
        this.date = LocalDateTime.now();
    }

    public Long getFrom() { return this.from; }

    public void setFrom(Long from) { this.from = from; }

    public Long getTo() { return this.to; }

    public void setTo(Long to) { this.to = to; }

    public Status getStatus() { return this.status; }

    public void setStatus(Status status) { this.status = status; }

    public LocalDateTime getDate() { return this.date; }

    public void setDate(LocalDateTime date) { this.date = date; }
}
