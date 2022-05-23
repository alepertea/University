using System;
using System.Collections.Generic;
using System.Text;
using Lab7.Domain;
using Lab7.Validator;
using Lab7.Exceptions;

namespace Lab7.Validator
{
    class ActivePlayerValidator : IValidator<ActivePlayer>
    {
        public void Validate(ActivePlayer entity)
        {
            if (entity.ScoredPoints < 0)
                throw new ValidationException("Invalid number of points!");
        }
    }
}
