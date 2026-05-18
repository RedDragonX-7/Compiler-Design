%{
#include <stdio.h>
int line_no = 1;
%}

DIGIT      [0-9]
ID         [a-zA-Z_][a-zA-Z0-9_]*
KEYWORD    int|float|if|else|return
SEPARATOR  [;,(){}]

%%

"=="|"!="|"<="|">="|"+"|"-"|"*"|"/"|">"|"="   { printf("Operator: %s\n", yytext); }

{KEYWORD}      { printf("Keyword: %s\n", yytext); }

{ID}           { printf("Identifier: %s\n", yytext); }

{DIGIT}+       { printf("Number: %s\n", yytext); }

{SEPARATOR}    { printf("Separator: %s\n", yytext); }

\n             { line_no++; }

[ \t]+         { /* ignore whitespace */ }

.              { printf("Unknown symbol: %s\n", yytext); }

%%

int main() {
    printf("Enter input (Ctrl+D to end):\n");
    yylex();
    return 0;
}

int yywrap() {
    return 1;
}