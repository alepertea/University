using System;
using System.Collections.Generic;
using System.Text;

namespace Lab7.Exceptions
{
    class InputException : Exception
    {
        private string message;
        public InputException(string message)
        {
            this.message = message;
        }
        public string GetMessage()
        {
            return this.message;
        }
    }
}
