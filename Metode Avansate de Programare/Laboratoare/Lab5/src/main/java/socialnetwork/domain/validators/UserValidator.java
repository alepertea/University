package socialnetwork.domain.validators;

import socialnetwork.domain.User;

public class UserValidator implements Validator<User>
{
    @Override
    public void validate(User entity) throws ValidationException
    {
        String firstName = entity.getFirstName();
        String lastName = entity.getLastName();

        String errorMessage = "";

        if(firstName.contentEquals(""))
            errorMessage += "First name cannot be empty!\n";
        if(lastName.contentEquals(""))
            errorMessage += "Last name cannot be empty!\n";

        char[] fName = firstName.toCharArray();
        for(char c : fName)
        {
            if(Character.isDigit(c))
            {
                errorMessage += "First name cannot contain digits!\n";
                break;
            }
        }

        char[] lName = lastName.toCharArray();
        for(char c : lName)
        {
            if(Character.isDigit(c))
            {
                errorMessage += "Last name cannot contain digits!\n";
                break;
            }
        }

        if(errorMessage.compareTo("") != 0)
            throw new ValidationException(errorMessage);
    }
}
