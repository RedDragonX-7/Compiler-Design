%{
#include <stdio.h>
#include <stdlib.h>

int yylex(void);
void yyerror(const char *s);

int isError = 0;
%}

%token IF ELSE ID RELOP ASSIGN NUM SEMICOLON

%nonassoc LOWER_THAN_ELSE
%nonassoc ELSE

%start stmt

%%

stmt
    : if_stmt
      {
          if (!isError)
              printf("Valid\n");
      }
    ;

if_stmt
    : IF '(' cond ')' stmt_block %prec LOWER_THAN_ELSE
    | IF '(' cond ')' stmt_block ELSE stmt_block
    ;

stmt_block
    : ID ASSIGN expr SEMICOLON
    | if_stmt
    ;

cond
    : ID RELOP ID
    | ID RELOP NUM
    ;

expr
    : ID
    | NUM
    ;

%%

void yyerror(const char *s)
{
    isError = 1;
    printf("Syntax Error: Invalid statement\n");

    /* Discard remaining tokens until end of line */
    while (yylex() != 0)
        ;
}

int main(void)
{
    printf("=== IF-ELSE Statement Parser ===\n");
    printf("Enter one statement per line.\n");
    printf("Examples:\n");
    printf("if (a>b) x=y;\n");
    printf("if (a>b) x=y; else x=z;\n");
    printf("Press Ctrl+D (Linux/macOS) or Ctrl+Z (Windows) to exit.\n\n");

    while (!feof(stdin))
    {
        isError = 0;
        printf("> ");

        yyparse();
    }

    return 0;
}