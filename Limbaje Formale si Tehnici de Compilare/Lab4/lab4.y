%{
    #include <string.h>
    #include <stdio.h>
    #include <stdlib.h>

    extern int yylex();
    extern int yyparse();
    extern FILE* yyin;
    extern int currentLine;
    void yyerror();
%}
%token DACA
%token ATUNCI
%token SFDACA
%token PROGRAM
%token BGN
%token VAR
%token TYPE
%token ID
%token CONST
%token END
%token DATA_TYPE
%token IF
%token WHILE
%token DO
%token READLN
%token WRITELN
%token THEN
%token ELSE
%token LPR
%token RPR
%token SEMICOLON
%token COMMA
%token COLON
%token ASSIGN
%token PLUS
%token MINUS
%token MUL
%token LT
%token GT
%token NE
%token PERIOD
%%     

program: header declarations BGN instruction_list END PERIOD
	;

header: PROGRAM ID SEMICOLON
	;

declarations: VAR variable_list COLON DATA_TYPE SEMICOLON
	;

variable_list: ID 
	| ID COMMA variable_list
	;

instruction_list : instruction
		|  instruction instruction_list
		;

instruction : assign_instruction
	| if_instruction
	| io_instruction
	| while_loop
	| daca_instruction
	;

daca_instruction : DACA LPR ID RPR ATUNCI instruction SFDACA
		;

assign_instruction : ID ASSIGN expression SEMICOLON
		;

expression : ID
	| CONST
	| ID operator expression
	| CONST operator expression
	;

operator : PLUS | MINUS | MUL

bool_operator : GT | LT | NE

if_instruction : IF boolean_expression THEN BGN instruction_list END SEMICOLON
		;

boolean_expression : ID bool_operator expression
		;

io_instruction : READLN LPR ID RPR SEMICOLON
		| WRITELN LPR ID RPR SEMICOLON
		;

while_loop : WHILE boolean_expression DO BGN instruction_list END SEMICOLON
		;
                    
%%

int main(int argc, char* argv[]) {
    ++argv, --argc;
    
    // sets the input for flex file
    if (argc > 0) 
        yyin = fopen(argv[0], "r"); 
    else 
        yyin = stdin; 
    
    //read each line from the input file and process it
    while (!feof(yyin)) {
        yyparse();
    }
    printf("The file is sintactically correct!\n");
    return 0;
}

void yyerror() {
    printf("Error at line: %d ! \n", currentLine);
    exit(1);
}