## Overview
This project is a **Lexical Analyzer** for the FanC programming language. It reads a source code file, tokenizes the input, and outputs a list of tokens along with their types and line numbers.

## Features
- Recognizes built-in keywords (e.g., `if`, `else`, `while`, `int`, `void`).
- Identifies user-defined identifiers, numeric constants, string literals, and comments.
- Detects basic operators, delimiters, and punctuation.
- Handles valid escape sequences in string literals.

## Requirements
- A working C++ compiler (e.g., GCC, Clang).
- Flex (Fast Lexical Analyzer Generator).

## Files
- `scanner.lex`: The Flex file containing lexical rules.
- `tokens.hpp`: Header file defining token types.
- `main.cpp`: Main driver for testing the lexical analyzer.

## How to Build
1. Generate the scanner using Flex:
   ```bash
   flex scanner.lex
   ```
2. Compile the generated C file:
   ```bash
   g++ -std=c++17 -o scanner lex.yy.c main.cpp
   ```

## How to Run
Run the compiled program and provide the input file via standard input or redirection:
```bash
./scanner < input.fanc
```

## Output
- The program outputs each token along with its type and line number. For example:
  ```
  1 INT int
  1 ID x
  1 ASSIGN =
  1 NUM 5
  ```
