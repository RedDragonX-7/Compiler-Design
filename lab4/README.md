# Lab 4: Arithmetic Expression Parser Using Lex and Yacc

## 1. Introduction

This lab focuses on designing and implementing an arithmetic expression parser using Lex (Flex) and Yacc (Bison). The parser evaluates mathematical expressions involving integers and basic arithmetic operators while respecting operator precedence and associativity rules.

The project demonstrates key concepts of compiler design, including lexical analysis, syntax analysis, grammar definition, and expression evaluation.

## 2. Objectives

- To understand lexical analysis using Flex.
- To understand syntax analysis using Bison.
- To implement grammar rules for arithmetic expressions.
- To evaluate expressions using semantic actions.
- To handle errors such as invalid characters and division by zero.

## 3. Tools Used

- Flex (Lexical Analyzer Generator)
- Bison (Parser Generator)
- GCC Compiler
- Linux/macOS Terminal

## 4. Files Description

### y.y (Bison File)
Contains:
- Grammar rules for arithmetic expressions
- Token definitions
- Semantic actions for evaluation
- Error handling function (yyerror)
- Main function to run parser

### key.l (Flex File)
Contains:
- Regular expressions for tokenizing input
- Integer recognition
- Operator recognition (+ - * / ( ))
- Whitespace handling
- Invalid character detection

## 5. Lexical Analysis

The lexer converts input strings into tokens.

| Input | Token |
|------|------|
| 123  | NUMBER |
| +    | + |
| -    | - |
| *    | * |
| /    | / |
| ( )  | Parentheses |

## 6. Grammar Used

expr → expr + term | expr - term | term  
term → term * factor | term / factor | factor  
factor → ( expr ) | NUMBER  

## 7. Compilation Process

Step 1: Generate Parser
bison -d y.y

Step 2: Generate Lexer
flex key.l

Step 3: Compile Program
gcc y.tab.c lex.yy.c -o calculator -lfl

On macOS (if needed):
gcc y.tab.c lex.yy.c -o calculator

## 8. Execution

Run the program:
./calculator

## 9. Sample Input and Output

Input:
3+4*2

Output:
Result = 11

Input:
(3+4)*2

Output:
Result = 14

Input:
10/5+7

Output:
Result = 9

## 10. Error Handling

### Division by Zero

Input:
10/0

Output:
Error: Division by zero

### Invalid Character

Input:
3+4a

Output:
Unknown character: a

## 11. Features

- Arithmetic expression evaluation
- Operator precedence support
- Parentheses support
- Division-by-zero detection
- Invalid character handling
- Interactive input system

## 12. Learning Outcomes

- Understanding lexical analysis using Flex
- Understanding syntax analysis using Bison
- Implementation of expression evaluation
- Grammar rule design
- Error handling in compiler design

## 13. Conclusion

This lab successfully implements an arithmetic expression parser using Flex and Bison. The parser evaluates expressions correctly while handling precedence rules and runtime errors.