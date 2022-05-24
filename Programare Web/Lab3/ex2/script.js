function validateName(name)
{
	if (name.length == 0)
		return "Numele nu a fost completat!";
	for (let c of name)
		if (c >= '0' && c <= '9')
			return "Numele este nevalid!";
	return "Ok";
}

function validateDate(date)
{
	var today = new Date();
	var d = new Date(date.toString());
	if (!date)
		return "Data nașterii nu a fost completată!";
	if (today < d)
		return "Data nașterii este nevalidă!";
	return "Ok";
}

function validateAge(age)
{
	if (age.length == 0)
		return "Vârsta nu a fost completată!";
	for (let c of age)
		if (c < '0' || c > '9')
			return "Vârsta este nevalidă!";
	return "Ok";
}

function validateEmail(email)
{
	if (email.length == 0)
		return "Email-ul nu a fost completat!";
	var found = 1;
	for (let c of email)
		if (c == "@")
			found = 0;
	if (found == 1)
		return "Email-ul este nevalid!";
	return "Ok";
}

function setMessage(labelID, inputID, message, color)
{
	document.getElementById(labelID).innerHTML = message;
	document.getElementById(inputID).style.borderColor = color;
}

function validate()
{
	var name = document.getElementById("nume");
	var date = document.getElementById("dataNasterii");
	var age = document.getElementById("varsta");
	var email = document.getElementById("email");
	
	var error = 0;
	
	var messageName = validateName(name.value);
	if (messageName != "Ok")
	{
		error = 1;
		setMessage("errorName", "nume", messageName, "red");
	}
	else
	{
		setMessage("errorName", "nume", "", "green");
	}
	
	var messageDate = validateDate(date.value);
	if (messageDate != "Ok")
	{
		error = 1;
		setMessage("errorDate", "dataNasterii", messageDate, "red");
	}
	else
	{
		setMessage("errorDate", "dataNasterii", "", "green");
	}
	
	var messageAge = validateAge(age.value);
	if (messageAge != "Ok")
	{
		error = 1;
		setMessage("errorAge", "varsta", messageAge, "red");
	}
	else
	{
		setMessage("errorAge", "varsta", "", "green");
	}
	
	var messageEmail = validateEmail(email.value);
	if (messageEmail != "Ok")
	{
		error = 1;
		setMessage("errorEmail", "email", messageEmail, "red");
	}
	else
	{
		setMessage("errorEmail", "email", "", "green");
	}
	
	if (error == 0)
		document.getElementById("success").innerHTML = "Câmpurile sunt completate corect!";
}