using System;
using Lab7.Domain;
using Lab7.Exceptions;

namespace Lab7.Validator
{
    class GameValidator : IValidator<Game>
    {
        public void Validate(Game entity)
        {
            string errorMessage = "";

            if (entity.Date.CompareTo(DateTime.Today) > 0)
                errorMessage += "Invalid date!";

            if (errorMessage.Length != 0)
                throw new ValidationException(errorMessage);
        }
    }
}
