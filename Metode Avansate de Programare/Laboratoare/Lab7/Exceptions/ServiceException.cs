using System;

namespace Lab7.Exceptions
{
    class ServiceException : Exception
    {
        private string message;
        public ServiceException(string message)
        {
            this.message = message;
        }
        public string GetMessage()
        {
            return this.message;
        }
    }
}
