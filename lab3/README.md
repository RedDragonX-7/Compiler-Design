# Lab 3: Token Counter Using Flex

## Experiment Title

Token Counter for Identifiers, Keywords, Operators, and Other Tokens Using Flex

---

## Aim

To design and implement a lexical analyzer using Flex that:

- Identifies tokens such as keywords, identifiers, numbers, strings, operators, delimiters, comments, and unknown symbols.

- Counts the number of occurrences of each token type in the input program.

---

## Software Requirements

- **Flex** – Lexical analyzer generator  

- **GCC** – C compiler  

- **Operating System** – Windows (MinGW) / Linux / macOS  

---

## Theory

A lexical analyzer (lexer) is the first phase of a compiler. It reads the input source code and converts it into meaningful tokens.
In this experiment:
- Regular expressions define token patterns.
- Flex rules match patterns in the input.
- Actions inside `{ }` increment counters and display tokens.
- A final summary shows total token counts.
This helps in understanding how compilers classify and process source code.

sample input
int x = 5;
if (x > 2) x = x + 1;

sample output
KEYWORD: int IDENTIFIER: x OPERATOR: =
NUMBER: 5 DELIMITER: ;

KEYWORD: if DELIMITER: ( IDENTIFIER: x
OPERATOR: > NUMBER: 2 DELIMITER: )

IDENTIFIER: x OPERATOR: =
IDENTIFIER: x OPERATOR: +
NUMBER: 1 DELIMITER: ;

Token Count Summary
Keywords     : 2
Identifiers  : 4
Numbers      : 3
Strings      : 0
Logical Ops  : 0
Operators    : 4
Delimiters   : 5
Comments     : 0
Unknown      : 0


Result
• The lex program successfully detected and printed all relevant tokens.
• Counted token types such as keywords, operators, etc.
• Displayed the final count summary at the end of execution.

Conclusion
• Understood how to use regular expressions to detect various token types.
• Used Flex actions to maintain counters and print real-time results.
