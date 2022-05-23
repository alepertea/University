using System;
using System.Collections.Generic;
using System.Text;

namespace Lab7.Validator
{
    interface IValidator<E>
    {
        public void Validate(E entity);
    }
}
