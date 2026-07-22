# Lab 5: FIRST and FOLLOW Set Computation

## Objective

The objective of this lab is to implement a C program that computes the **FIRST** and **FOLLOW** sets for a given Context-Free Grammar (CFG). These sets are fundamental concepts in compiler design and are widely used in the construction of predictive (LL(1)) parsers.

---

## Problem Statement

Modify the hardcoded grammar in the provided C program to implement the following arithmetic expression grammar and compute its FIRST and FOLLOW sets.

### Original Grammar

```
E  → T E'
E' → + T E' | ε
T  → F T'
T' → * F T' | ε
F  → ( E ) | id
```

### Representation Used in the Program

Since the program supports only single-character non-terminals, the grammar is represented as:

```
E → T A
A → + T A | ε
T → F B
B → * F B | ε
F → ( E ) | i
```

where:

- `A` represents `E'`
- `B` represents `T'`
- `i` represents the terminal `id`
- `e` represents epsilon (ε)

---

## Theory

### FIRST Set

The **FIRST** set of a grammar symbol is the set of terminals that can appear as the first symbol of any string derived from that symbol.

Rules:

1. If `X` is a terminal, then `FIRST(X) = {X}`.
2. If `X → ε`, then `ε` belongs to `FIRST(X)`.
3. If `X → Y₁Y₂...Yn`, then include `FIRST(Y₁)` except ε.
4. If `FIRST(Y₁)` contains ε, continue with `Y₂`, and so on.
5. If every symbol can derive ε, include ε in `FIRST(X)`.

---

### FOLLOW Set

The **FOLLOW** set of a non-terminal is the set of terminals that can immediately follow it in some sentential form.

Rules:

1. Place `$` in the FOLLOW set of the start symbol.
2. If `A → αBβ`, then add `FIRST(β) − {ε}` to `FOLLOW(B)`.
3. If `β` can derive ε, add `FOLLOW(A)` to `FOLLOW(B)`.
4. If `B` is the last symbol in a production, add `FOLLOW(A)` to `FOLLOW(B)`.

---

## Algorithm

### Algorithm for FIRST Set

1. Initialize FIRST sets as empty.
2. Traverse each production.
3. If the production begins with a terminal, add it to FIRST.
4. If it begins with a non-terminal, recursively include its FIRST set.
5. If epsilon exists, continue with the next symbol.
6. Repeat until no changes occur.

---

### Algorithm for FOLLOW Set

1. Initialize FOLLOW sets as empty.
2. Add `$` to the FOLLOW of the start symbol.
3. For each production:
   - Add FIRST of succeeding symbols.
   - If succeeding symbols derive ε or do not exist, add FOLLOW of the head.
4. Repeat until no changes occur.

---

## Grammar Used

```
E → T A
A → + T A | ε
T → F B
B → * F B | ε
F → ( E ) | i
```

---

## Expected FIRST Sets

| Non-Terminal | FIRST Set |
|--------------|-----------|
| E | { (, i } |
| A | { +, ε } |
| T | { (, i } |
| B | { *, ε } |
| F | { (, i } |

---

## Expected FOLLOW Sets

| Non-Terminal | FOLLOW Set |
|--------------|------------|
| E | { $, ) } |
| A | { $, ) } |
| T | { +, $, ) } |
| B | { +, $, ) } |
| F | { *, +, $, ) } |

---

## Program Features

- Computes FIRST sets automatically.
- Computes FOLLOW sets automatically.
- Supports epsilon productions.
- Eliminates duplicate symbols in sets.
- Handles recursive grammar rules.
- Uses iterative computation until all sets stabilize.

---

## Sample Output

```
========== FIRST SETS ==========

FIRST(E) = { (, i }
FIRST(A) = { +, e }
FIRST(T) = { (, i }
FIRST(B) = { *, e }
FIRST(F) = { (, i }

========== FOLLOW SETS ==========

FOLLOW(E) = { $, ) }
FOLLOW(A) = { $, ) }
FOLLOW(T) = { +, $, ) }
FOLLOW(B) = { +, $, ) }
FOLLOW(F) = { *, +, $, ) }
```

---

## Applications

- LL(1) parser construction
- Predictive parsing
- Syntax analysis in compilers
- Parser table generation
- Compiler front-end design

---

## Conclusion

This lab demonstrates the implementation of FIRST and FOLLOW set computation for an arithmetic expression grammar using C. The program correctly handles epsilon productions, recursive rules, and grammar dependencies to produce the required FIRST and FOLLOW sets. These sets are essential for constructing predictive parsers and form a core component of compiler design.