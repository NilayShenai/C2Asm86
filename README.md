
# C2Asm86  

C2Asm86 is a tool that converts C code into optimized 8086 assembly language. It uses **lex** and **yacc** to perform lexical analysis, parsing, and assembly generation, with built-in optimization for efficient output.  

## How It Works  
1. Place your C code in the file `Input.c`.  
2. Run the following commands:  
   ```bash
   chmod +x Script.sh  
   ./Script.sh  
   ```  
3. The generated assembly code will be saved in two files:  
   - `code.asm`: Contains the unoptimized assembly code.  
   - `optimized_code.asm`: Contains the optimized assembly code.  

---

## File Structure  

### Key Files and Their Purpose  
- **SymbolInfo.h**:  
  Defines the structure to represent tokens. For example, the token `int a;` is stored as `<ID, a>` or `<ID, location of a in the symbol table>`. It includes attributes like name and type, organized via the `SymbolInfo` class.  

- **ExtraSymbolInfo.h**:  
  Stores additional details about tokens, including information crucial for intermediate code generation and storing the generated assembly instructions.  

- **ScopeTable.h**:  
  Tracks the scope (global or local) of each symbol in the program.  

- **SymbolTable.h**:  
  Manages all symbol-related operations, including storage and processing of valid tokens.  

- **StringHandler.h**:  
  Assists in generating labels, variables, and optimizing the code.  

- **SymbolTable.cpp**:  
  Combines the functionality of `SymbolInfo.h`, `ExtraSymbolInfo.h`, `ScopeTable.h`, and `SymbolTable.h`.  

- **Lexer.l**:  
  Contains rules to tokenize valid C code and handle lexical errors.  

- **Parser.y**:  
  Implements parsing rules based on a defined grammar.  

- **Script.sh**:  
  A shell script to automate the compilation and execution process.  

- **Input.c**:  
  The input file where you write your C code to test its validity.  

- **log.txt**:  
  Stores the output of the process.  

- **error.txt**:  
  Records any errors encountered during execution.  

- **code.asm**:  
  The unoptimized 8086 assembly code generated from the input C code.  

- **optimized_code.asm**:  
  The optimized version of the assembly code.  

---

## Tools  

### Development Tools Used  
- **FLEX**:  
  A tool for generating lexical analyzers. Flex takes a set of rules and produces a program to process input text for matching patterns.  

- **BISON**:  
  A parser generator that analyzes context-free grammars and creates parsers for them. It checks the syntax of the input code and ensures it adheres to the defined rules.  

---

## References  

- [Tiny C Compiler Notes](https://www.hpcs.cs.tsukuba.ac.jp/~msato/lecture-note/comp-lecture/tiny-c-note1.html)  
  A detailed set of lecture notes about implementing a simple C compiler.  

- **Book**: *Lex & Yacc* by John R. Levine, Tony Mason, Doug Brown  
  A comprehensive guide to building compilers and interpreters using `lex` and `yacc`.  

---

## Usage Instructions  

To get started, clone the repository and execute the tool as follows:  
```bash
git clone https://github.com/NilayShenai/C2Asm86  
```  
Follow the steps in the "How It Works" section to generate assembly code from your C code.  
