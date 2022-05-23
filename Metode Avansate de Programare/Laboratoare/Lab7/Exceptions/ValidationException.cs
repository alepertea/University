using System;

namespace Lab7.Exceptions
{
    class ValidationException : Exception
    {
        private string message;
        public ValidationException(string message)
        {
            this.message = message;
        }
        public string GetMessage()
        {
            return this.message;
        }
    }
}
