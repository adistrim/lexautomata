# Lexer and Automata

This repository contains implementations of a simple lexer, a DFA recognizer, and an NFA recognizer.

## Folder Structure

* **simple_lexer.l:** Contains the lexer definitions. 
* **lexer.cpp:** Input file for the lexer.
* **DFA.c:** Contains the implementation of the DFA recognizer.
* **NFA.c:** Contains the implementation of the NFA recognizer. 
* **output:** Directory to store the outputs of the lexer and automata.

## Compilation

**For lexer:**
1. ```flex simple_lexer.l```
2. ```gcc lex.yy.c -o lexer -lfl```
3. ```./lexer input.cpp > output/lexerOutput.txt``` 

**For DFA:**
1. ```gcc -o DFA.o DFA.c```
2. ```./DFA.o```

**For NFA:**
1. ```gcc -o NFA.o NFA.c```
2. ```./NFA.o```
