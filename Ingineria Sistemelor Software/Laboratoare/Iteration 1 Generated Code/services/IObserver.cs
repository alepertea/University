
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

public interface IObserver {


    /// <summary>
    /// @param account 
    /// @return
    /// </summary>
    public void AccountAction(Account account);

}