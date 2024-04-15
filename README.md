# Validating expressions with a Pushdown Automaton
Author: [Jack Robbins](https://www.github.com/jackr276)

## Introduction
This project defines and implements a Pushdown Automaton(PDA) that recognizes a context-free language $A$. A full description of the language $A$, a proof that it is not regular, and a finite state machine diagram for the PDA is given in this README. This project also contains the 
implmentation of the [PDA](https://github.com/jackr276/Expression-Validation-with-a-PDA/blob/main/src/pda.cpp), written in C++. Although the source code is very well documented, I would greatly encourage reading and understanding the README first to get a theoretical understanding
of the project.

## The Language $A$
### Informal Definition
Define the context-free language $A$ to be the set of all valid arithmetic floating point operations, enclosed in two strings of symbols in a specific format. Each string A is of the form:
$ab^kaEab^ka$, for any $k \geq 0$, and any $E$ that is a valid expression over floating point numbers. 

Here is an example of a string in $A$: `abba(1.2/.2*0.2+(1.-2.+3.1))abba`

Although it may not be immediately obvious, $A$ is not a regular language. However, $A$ is a context-free language, because there exists a context free grammar that defines $A$. 

### Proof: $A$ is not a regular language

## Context-Free Grammar for A


 
![pda drawing drawio(1)](https://github.com/jackr276/Expression-Validation-with-a-PDA/assets/113046361/1205c8ae-bdf5-4aae-9cd4-0d8c5c649076)
