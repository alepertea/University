package socialnetwork.domain.validators;

import socialnetwork.domain.Account;

public class AccountValidator implements Validator<Account>
{
    @Override
    public void validate(Account entity) throws ValidationException
    {
        if(!entity.getUsername().matches("\\w+@\\w+\\.com") && !entity.getUsername().matches("\\w+@\\w+\\.ro"))
        {
            throw new ValidationException("Invalid username!");
        }
    }
}
