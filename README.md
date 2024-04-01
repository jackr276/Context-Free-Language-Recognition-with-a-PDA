# Validating expressions with a Pushdown Automaton
Author: [Jack Robbins](https://www.github.com/jackr276)

## Introduction
Define the language $A$ to be the set of all valid arithmetic floating point operations, enclosed in two strings of symbols in a specific format. Each string A is of the form:
$ab^kaEab^ka$, for any $k \geq 0$, and any $E$ that is a valid expression over floating point numbers. 

Here is an example of a string in $A$: `abba(1.2/.2*0.2+(1.-2.+3.1))abba`

Although it may not be immediately obvious, $A$ is not regular(a proof is given below). However, $A$ is context free, because there exists a context free grammar that defines $A$.

## Context-Free Grammar for A


 
![pda drawing drawio(1)](https://github.com/jackr276/Expression-Validation-with-a-PDA/assets/113046361/1205c8ae-bdf5-4aae-9cd4-0d8c5c649076)
