package com.company;

public class Atom {

    private String input;
    private final String ID = "^[a-z][a-z0-9]{0,7}";
    private final String CONST = "^[0-9]\\.*[0-9]*";
    private final String[] BOOL_OPERATORS = {"<", ">", "<>"};
    private final String[] OPERATORS = {"+", "-", "*", ":="};
    private final String[] SEPARATORS = {".", ",", ";"};
    private final String[] KEYWORDS = {"program", "begin", "var", "type", "end", "integer", "real", "if", "while", "readln", "writeln"};

    public Atom() { }

    public void setInput(String input){
        this.input = input;
    }

    /**
     * Checks whether the input represents an ID.
     * An ID is defined by: ID = letter , { letter | digit }, with a maximum length of 8 characters.
     * @return true, if the input matches the criteria, false otherwise
     */
    public boolean isID() {
        return input.matches(this.ID);
    }

    /**
     * Checks whether the input represents a CONST.
     * A CONST is defined by: digit , [‘.’] , { digit }.
     * @return true, if the input matches the criteria, false otherwise
     */
    public boolean isCONST() {
        return this.input.matches(this.CONST);
    }

    /**
     * Checks whether the input represents a boolean operator.
     * A boolean operator is defined by: bool_operator = ‘>’ | ‘<’ | ‘<>’.
     * @return true, if the input matches the criteria, false otherwise
     */
    public boolean isBoolOperator() {
        for (String boolOperator : BOOL_OPERATORS) {
            if (this.input.equals(boolOperator)) {
                return true;
            }
        }
        return false;
    }

    /**
     * Checks whether the input represents an operator.
     * An operator is defined by: operator = ‘+’ | ‘-’ | ‘*’.
     * @return true, if the input matches the criteria, false otherwise
     */
    public boolean isOperator() {
        for (String operator : OPERATORS) {
            if (this.input.equals(operator)) {
                return true;
            }
        }
        return false;
    }

    /**
     * Checks whether the input represents a separator.
     * An operator is defined by: separator = ‘.’ | ‘,’ | ‘;’.
     * @return true, if the input matches the criteria, false otherwise
     */
    public boolean isSeparator() {
        for (String separator : SEPARATORS) {
            if (this.input.equals(separator)) {
                return true;
            }
        }
        return false;
    }

    /**
     * Checks whether the input represents a keyword.
     * @return true, if the input matches the criteria, false otherwise
     */
    public boolean isKeyword() {
        for (String keyword : KEYWORDS) {
            if (this.input.equals(keyword)) {
                return true;
            }
        }
        return false;
    }
}
