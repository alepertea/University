package com.company;

public class ExpressionParser
{
    /*
        Valideaza argumentele si trimite mesaj de eroare daca nu sunt valide
        Daca argumentele sunt valide, se separa numerele si se executa operatiile in functie de operator
     */
    public ComplexExpression parseExpression(String[] args)
    {
        try
        {
            isValid(args);

            ExpressionFactory exp = ExpressionFactory.getInstance();
            Complex[] numbers = buildArgs(args);
            switch(args[1])
            {
                case "+": return exp.createExpression(Operation.ADDITION,numbers);
                case "-": return exp.createExpression(Operation.SUBTRACTION,numbers);
                case "*": return exp.createExpression(Operation.MULTIPLICATION,numbers);
                case "/": return exp.createExpression(Operation.DIVISION,numbers);
            }
        }catch(ValidException e)
        {
            System.out.println(e.getMessage());
        }
        return null;
    }

    /*
        Verifica daca string-ul dat ca argument e valid
        Arunca exceptii:
            - "Expresie invalida":      daca expresia se termina in +/-
                                        daca expresia are doar un numar
            - "Numar complex invalid":  daca expresia contine cel putin un element care nu reprezinta un numar complex
            - "Operator invalid":       daca cel putin un operator e diferit de +/-
     */
    private void isValid(String[] args) throws ValidException
    {
        if(args.length % 2 == 0 || args.length == 1)
            throw new ValidException("Expresie invalida!");

        String[] patterns = {"-?\\d+(\\.\\d+)?[+-]\\d+(\\.\\d+)?\\*i", "-?\\d+(\\.\\d+)?", "-?\\d+(\\.\\d+)?\\*i", "-?i", "-?\\d+(\\.\\d+)?[+-]i"};
        for(int i = 0; i < args.length; i += 2)
            if(!args[i].matches(patterns[0]) && !args[i].matches(patterns[2]) && !args[i].matches(patterns[3]))
                throw new ValidException("Numar complex invalid!");

        for(int i = 1; i < args.length; i += 2)
            if(!args[i].matches("[-+/*]"))
                throw new ValidException("Operator invalid!");
    }

    /*
        Preia string-ul din linia de comanda si separa operanzii
        Returneaza un sir cu numerele complexe scrise
     */
    private Complex[] buildArgs(String[] args)
    {
        int k = 0;
        Complex[] numbers = new Complex[args.length / 2 + 1];
        String[] patterns = {"-?\\d+(\\.\\d+)?[+-]\\d+(\\.\\d+)?\\*i", "-?\\d+(\\.\\d+)?", "-?\\d+(\\.\\d+)?\\*i", "-?i", "-?\\d+(\\.\\d+)?[+-]i"};

        for(int i = 0; i < args.length; i += 2)
        {
            double real = 0;
            double imaginary = 0;

            if(args[i].matches(patterns[0]))
            {   // numarul e de forma a + b*i, a, b diferit de zero
                real = 1;
                imaginary = 1;
                if(args[i].charAt(0) == '-')
                {
                    real =- 1;
                    args[i] = args[i].substring(1);
                }
                String[] num = args[i].split("[+-]");
                real *= Double.parseDouble(num[0]);
                if(args[i].contains("-"))
                    imaginary = -1;
                imaginary *= Double.parseDouble(num[1].substring(0, num[1].length() - 2));
            }
            else if(args[i].matches(patterns[1]))
            {   // numarul e de forma a, a != 0
                real = 1;
                if(args[i].charAt(0) == '-')
                {
                    real =- 1;
                    args[i] = args[i].substring(1);
                }
                real *= Double.parseDouble(args[i]);
            }
            else if(args[i].matches(patterns[2]))
            {   // numarul e de forma b*i, b != 0
                imaginary = 1;
                if(args[i].charAt(0) == '-')
                {
                    imaginary =- 1;
                    args[i]=args[i].substring(1);
                }
                imaginary *= Double.parseDouble(args[i].substring(0, args[i].length() - 2));
            }
            else if(args[i].matches(patterns[3]))
            {   // numarul e de forma i
                if(args[i].charAt(0) == '-')
                    imaginary = -1;
                else
                    imaginary = 1;
            }
            else
            {   // numarul e de forma a + i, a != 0
                real = 1;
                if(args[i].charAt(0) == '-')
                {
                    real =- 1;
                    args[i] = args[i].substring(1);
                }
                String[] nr = args[i].split("[+-]");
                real *= Double.parseDouble(nr[0]);
                if(args[i].contains("-"))
                    imaginary = -1;
                else
                    imaginary = 1;
            }
            numbers[k] = new Complex(real, imaginary);
            k++;
        }
        return numbers;
    }
}