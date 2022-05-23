using System;
using System.Collections.Generic;
using System.Text;
using Lab7.Domain;
using Lab7.Exceptions;

namespace Lab7.Validator
{
    class TeamValidator : IValidator<Team>
    {
        public void Validate(Team entity)
        {
            if (entity.Name.Length == 0)
                throw new ValidationException("Team must have a name!");
        }
    }
}
