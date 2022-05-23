using Lab7.Domain;
using Lab7.Exceptions;
using System.Linq;

namespace Lab7.Validator
{
    class PlayerValidator : IValidator<Player>
    {
        public void Validate(Player entity)
        {
            string errorMessage = "";

            if (entity.Name.Length == 0)
                errorMessage.Concat("Student must have a name!\n");

            char[] name = entity.Name.ToCharArray();
            var query1 = name.Where(n => n.CompareTo('0') >= 0 && n.CompareTo('9') <= 0);

            if (query1.FirstOrDefault() != default(int))
                errorMessage.Concat("Student name cannot contain digits!\n");

            char[] school = entity.School.ToCharArray();
            var query2 = school.Where(s => s.CompareTo('0') >= 0 && s.CompareTo('9') <= 0);

            if (query2.FirstOrDefault() != default(int))
                errorMessage.Concat("School name cannot contain digits!\n");

            if (errorMessage.Length > 0)
                throw new ValidationException(errorMessage);
        }
    }
}
