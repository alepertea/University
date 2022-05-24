
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

public class UserEventArgs {

    public UserEventArgs() {
    }

    private UserEvent userEvent;

    private Object data;


    /// <summary>
    /// @return
    /// </summary>
    public UserEvent UserEventType() {
        // TODO implement here
        return null;
    }

    /// <summary>
    /// @return
    /// </summary>
    public Object Data() {
        // TODO implement here
        return null;
    }

    public enum UserEvent {
        ACCOUNT_MODIFIED
    }

}