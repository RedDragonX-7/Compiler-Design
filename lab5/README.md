# Lab 5: IF-ELSE Statement Parser Using Flex and Bison

## Objective

To design and implement a parser for validating **IF-ELSE statements** using **Flex (Lex)** and **Bison (Yacc)**. The parser checks whether the entered IF-ELSE statements follow the specified grammar and reports whether they are valid or contain syntax errors.

---

## Theory

### Flex (Lex)

Flex is a lexical analyzer generator that converts an input stream into a sequence of tokens. It scans the input according to predefined regular expressions and passes the recognized tokens to the parser.

Examples of tokens recognized in this lab include:

- `if`
- `else`
- Identifiers (`ID`)
- Numbers (`NUM`)
- Assignment operator (`=`)
- Relational operators (`<`, `>`, `<=`, `>=`, `==`, `!=`)
- Semicolon (`;`)
- Parentheses (`(` and `)`)

---

### Bison (Yacc)

Bison is a parser generator that accepts tokens from the lexer and verifies whether they conform to the specified grammar.

In this experiment, Bison parses:

- Simple IF statements
- IF-ELSE statements
- Nested IF statements
- Assignment statements inside IF blocks

It also resolves the **dangling else** ambiguity using precedence declarations.

---

## Problem Statement

Develop a lexical analyzer and parser to validate IF-ELSE statements using Flex and Bison.

---

## Grammar

```
stmt        → if_stmt

if_stmt     → IF '(' cond ')' stmt_block
            | IF '(' cond ')' stmt_block ELSE stmt_block

stmt_block  → ID ASSIGN expr SEMICOLON
            | if_stmt

cond        → ID RELOP ID
            | ID RELOP NUM

expr        → ID
            | NUM
```

---

## Files

| File | Description |
|------|-------------|
| `ifelse.l` | Flex lexer specification |
| `ifelse.y` | Bison parser specification |
| `ifelse.tab.c` | Generated parser source |
| `ifelse.tab.h` | Generated parser header |
| `lex.yy.c` | Generated lexer source |
| `README.md` | Lab documentation |

---

## Compilation

Generate the parser and lexer:

```bash
bison -d ifelse.y
flex ifelse.l
```

Compile the program:

### Linux

```bash
gcc ifelse.tab.c lex.yy.c -lfl -o ifelsechecker
```

### macOS (Homebrew Flex)

```bash
gcc ifelse.tab.c lex.yy.c \
-I/opt/homebrew/opt/flex/include \
-L/opt/homebrew/opt/flex/lib \
-lfl \
-o ifelsechecker
```

Run the executable:

```bash
./ifelsechecker
```

---

## Sample Input and Output

### Example 1

**Input**

```
if(a>b)x=y;
```

**Output**

```
Valid
```

---

### Example 2

**Input**

```
if(a>b)x=y;else x=z;
```

**Output**

```
Valid
```

---

### Example 3

**Input**

```
if(a>=5)x=10;
```

**Output**

```
Valid
```

---

### Example 4

**Input**

```
if(a>b)x=;
```

**Output**

```
Syntax Error: Invalid statement
```

---

### Example 5

**Input**

```
2
```

**Output**

```
Syntax Error: Invalid statement
```

---

## Working

1. The lexer reads the input statement character by character.
2. Keywords, identifiers, operators, and numbers are converted into tokens.
3. Tokens are passed to the Bison parser.
4. The parser checks whether the tokens satisfy the defined grammar.
5. If the grammar is satisfied, the parser prints **Valid**.
6. Otherwise, a syntax error message is displayed.

---

## Features

- Recognizes IF statements.
- Recognizes IF-ELSE statements.
- Supports nested IF statements.
- Supports identifiers and numeric constants.
- Supports relational operators.
- Detects invalid syntax.
- Resolves the dangling ELSE ambiguity using precedence rules.

---

## Advantages

- Demonstrates lexical analysis and syntax analysis.
- Easy to extend with additional language constructs.
- Provides clear syntax error reporting.
- Modular implementation using Flex and Bison.

---

## Limitations

- Supports only assignment statements inside IF blocks.
- Does not evaluate expressions.
- Does not execute the parsed statements.
- Does not maintain a symbol table or perform semantic analysis.

---

## Applications

- Compiler front-end development.
- Programming language syntax validation.
- Educational compiler design experiments.
- Source code parsing and analysis.

---

## Learning Outcomes

After completing this experiment, the following concepts are understood:

- Lexical analysis using Flex.
- Syntax analysis using Bison.
- Token generation and parsing.
- Grammar design.
- Recursive grammar rules.
- Dangling ELSE problem and its resolution.
- Error handling in parsers.

---

## Conclusion

This experiment successfully demonstrates the implementation of an IF-ELSE statement parser using Flex and Bison. The lexer identifies valid lexical tokens, while the parser validates the syntax according to the defined grammar. The parser correctly accepts valid IF-ELSE statements, supports nested IF structures, and reports syntax errors for invalid inputs, illustrating the fundamental phases of compiler front-end design.