package socialnetwork.domain;

import java.time.LocalDateTime;
import java.util.ArrayList;

public class Message extends Entity<Long>
{
    private Long id;
    private Long from;
    private ArrayList<Long> to;
    private String message;
    private LocalDateTime date;
    private Long originalMessageId;

    public Message(Long from, ArrayList<Long> to, String message, LocalDateTime date)
    {
        this.from = from;
        this.to = to;
        this.message = message;
        this.date = date;
        this.originalMessageId = -1L;
    }

    public Long getFrom() { return this.from; }

    public void setFrom(Long from) { this.from = from; }

    public ArrayList<Long> getTo() { return this.to; }

    public void setTo(ArrayList<Long> to) { this.to = to; }

    public String getMessage() { return message; }

    public void setMessage(String message) { this.message = message; }

    public LocalDateTime getDate() { return date; }

    public void setDate(LocalDateTime date) { this.date = date; }

    public Long getOriginalMessageId() { return this.originalMessageId; }

    public void setOriginalMessageId(Long originalMessageId) { this.originalMessageId = originalMessageId; }
}
