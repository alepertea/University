package socialnetwork.service;

import socialnetwork.domain.Friendship;
import socialnetwork.domain.Message;
import socialnetwork.domain.Tuple;
import socialnetwork.domain.validators.MessageValidator;
import socialnetwork.domain.validators.Validator;
import socialnetwork.event.ChangeEventType;
import socialnetwork.event.MessageEvent;
import socialnetwork.observer.Observable;
import socialnetwork.observer.Observer;
import socialnetwork.repository.Repository;

import javax.crypto.BadPaddingException;
import javax.crypto.IllegalBlockSizeException;
import javax.crypto.NoSuchPaddingException;
import java.security.InvalidAlgorithmParameterException;
import java.security.InvalidKeyException;
import java.security.NoSuchAlgorithmException;
import java.util.ArrayList;
import java.util.Comparator;
import java.util.List;

public class MessageService implements Observable<MessageEvent>
{
    private final Repository<Long, Message> messageRepository;
    private final Repository<Tuple<Long,Long>, Friendship> friendshipRepository;
    private final Validator<Message> messageValidator;

    private List<Observer<MessageEvent>> observers;

    public MessageService(Repository<Long, Message> messageRepository, Repository<Tuple<Long, Long>, Friendship> friendshipRepository, MessageValidator messageValidator)
    {
        this.messageRepository = messageRepository;
        this.friendshipRepository = friendshipRepository;
        this.messageValidator = messageValidator;
        this.observers = new ArrayList<>();
    }

    public Long generateMessageID()
    {
        Long messageID = 1L;
        Iterable<Message> all = this.messageRepository.findAll();

        for(Message message : all)
            messageID++;

        return messageID;
    }

    public void sendMessage(Message message) throws BadPaddingException, InvalidAlgorithmParameterException, NoSuchAlgorithmException, IllegalBlockSizeException, NoSuchPaddingException, InvalidKeyException {
        this.messageValidator.validate(message);

        ArrayList<Long> recipients = message.getTo();
        ArrayList<Long> finalRecipients = new ArrayList<>();

        final String[] errorMessage = {""};
        recipients.forEach(
                x-> { if(this.friendshipRepository.findOne(new Tuple<>(x, message.getFrom())) != null)
                {
                    finalRecipients.add(x);
                }
                else
                {
                    errorMessage[0] += "You are not friends with user " + x + "!\n";
                }
                });

        message.setTo(finalRecipients);
        message.setId(this.generateMessageID());

        if(finalRecipients.size() > 0)
            this.messageRepository.save(message);

        notifyObservers(new MessageEvent(ChangeEventType.ADD, message));

        if(errorMessage[0].compareTo("") != 0)
            throw new ServiceException(errorMessage[0]);
    }

    public Message replyToAll(Message message, ArrayList<Long> arguments, Long from) throws BadPaddingException, InvalidAlgorithmParameterException, NoSuchAlgorithmException, IllegalBlockSizeException, NoSuchPaddingException, InvalidKeyException {
        ArrayList<Long> recipients = new ArrayList<>();
        arguments.forEach(x -> {
            if(!x.equals(from))
            {
                recipients.add(x);
            } });
        message.setTo(recipients);
        return this.messageRepository.save(message);
    }

    public Message replyToOne(Message message, Long recipient) throws BadPaddingException, InvalidAlgorithmParameterException, NoSuchAlgorithmException, IllegalBlockSizeException, NoSuchPaddingException, InvalidKeyException {
        ArrayList<Long> recipients = new ArrayList<>();
        recipients.add(recipient);
        message.setTo(recipients);
        return this.messageRepository.save(message);
    }

    public Message getMessage(long id)
    {
        return this.messageRepository.findOne(id);
    }

    public List<Message> getConversation(Long id1, Long id2)
    {
        Iterable<Message> all = this.messageRepository.findAll();
        List<Message> messages = new ArrayList<>();
        for(Message message : all)
            for(Long id : message.getTo())
                if(id.equals(id2) && message.getFrom().equals(id1) || id.equals(id1) && message.getFrom().equals(id2))
                {
                    messages.add(message);
                }

        messages.sort(new Comparator<Message>()
        {
            @Override
            public int compare(Message o1, Message o2)
            {
                if(o1.getDate().isEqual(o2.getDate()))
                    return 0;
                if(o1.getDate().isBefore(o2.getDate()))
                    return -1;
                return 1;
            }
        });
        return messages;
    }

    public List<Message> getGroupConversation(Long from, ArrayList<Long> friends)
    {
        Iterable<Message> all = this.messageRepository.findAll();
        List<Message> messages = new ArrayList<>();
        for(Message message : all)
        {
            if(message.getFrom().equals(from) && message.getTo() == friends)
                messages.add(message);
            //else
        }
        return messages;
    }


    @Override
    public void addObserver(Observer<MessageEvent> e) { observers.add(e); }

    @Override
    public void removeObserver(Observer<MessageEvent> e) { observers.remove(e);}

    @Override
    public void notifyObservers(MessageEvent t) {
        observers.forEach(x -> x.update(t));
    }
}
