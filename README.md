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

Here is an example of a string in $A$: `abba(1.2*(1.-2.+3.1))abba`

Although it may not be immediately obvious, $A$ is not a regular language. However, $A$ is a context-free language, because there exists a context free grammar that defines $A$.

### Context Free Grammar for $A$
For an exact definition of the langauge, $A$ can be defined by the context-free grammar $G$, which itself can be defined as the 4-tuple $G = (V, \Sigma, R, S)$, 
where:
 * $V = \\{S,T,C,H,Y,N\\}$ is the set of variables, also called nonterminals
 * $\Sigma = \\{.,0,1,2,...,9,+,-,*,/,(,),a,b\\}$, where $\Sigma$ is the alphabet, also known as the set of terminals
 * $S$ is the start variable

And $R$ is the set of rules, which are as follows:
 * $S \rightarrow$ a $T$ a
 * $T \rightarrow$ b $T$ b | a $C$ a
 * $C \rightarrow$ $C+C$ | $C-C$ | $C*C$ | $C/C$ | $(C)$ | $H$
 * $H \rightarrow$ $Y.Y$ | $Y.$ | $.Y$
 * $Y \rightarrow$ $NY$ | $N$
 * $N \rightarrow$ 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9

With this context-free grammar $G$, we can formally define $A$ as the language of $G$, $A = L(G)$. This means that all strings in $A$ can be derived by $G$, and $G$ can only derive strings that are in $A$.

### Example Derivation
To make this context-free grammar more concrete, here is an example of how $G$ could derive the string: `abba(1.2*(1.-2.+3.1))abba`

$S \Rightarrow$ a $T$ a $\Rightarrow$ ab $T$ ba $\Rightarrow$ abb $T$ bba $\Rightarrow$ abba $C$ abba $\Rightarrow$ abba( $C$ )abba $\Rightarrow$ abba( $C\*C$ )abba  
  $\Rightarrow$ abba( $C*(C)$ )abba $\Rightarrow$ abba( $C*(C+C)$ )abba $\Rightarrow$ abba( $C*(C-C+C)$ )abba  
  $\Rightarrow$ abba( $H*(C-C+C)$ )abba $\Rightarrow$ abba( $Y.Y*(C-C+C)$ )abba $\Rightarrow$ abba( $N.N*(C-C+C)$ )abba  
  $\Rightarrow$ abba(1.2 $\*(C-C+C)$ )abba $\Rightarrow$ abba(1.2 $\*(H-C+C)$ )abba $\Rightarrow$ abba(1.2 $\*(Y.-C+C)$ )abba  
  $\Rightarrow$ abba(1.2 $\*(N.-C+C)$ )abba $\Rightarrow$ abba(1.2 $\*(1.-C+C)$ )abba $\Rightarrow$ abba(1.2 $\*(1.-H+C)$ )abba  
  $\Rightarrow$ abba(1.2 $\*(1.-Y.+C)$ )abba $\Rightarrow$ abba(1.2 $\*(1.-N.+C)$ )abba $\Rightarrow$ abba(1.2 $\*(1.-2.+C)$ )abba  
  $\Rightarrow$ abba(1.2 $\*(1.-2.+H)$ )abba $\Rightarrow$ abba(1.2 $\*(1.-2.+Y.Y)$ )abba $\Rightarrow$ abba(1.2 $\*(1.-2.+3.1)$ )abba

### Proof: $A$ is not a regular language

## Context-Free Grammar for A


 
![pda drawing drawio(1)](https://github.com/jackr276/Expression-Validation-with-a-PDA/assets/113046361/1205c8ae-bdf5-4aae-9cd4-0d8c5c649076)
