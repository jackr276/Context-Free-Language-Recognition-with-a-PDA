# Validating Expressions with a Pushdown Automaton
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

>[!NOTE]
>$G$ is not deterministic, meaning that there exist many ways to derive the same string using $G$. The above only demonstrates one such way of doing so.

### Proof: $A$ is not a regular language
Before introducing the Pushdown Automato(PDA), let's first understand why we need to use a PDA in for this language. It has already shown that the language $A$ is context free, because there exist a context-free grammar $G$, which was defined above, that derives all strings in the language
$A$. However, since all regular languages are also context-free languages, it is worth asking why we can not instead use a regular expression to derive languages in $A$, or use a Deterministic Finite Automaton(DFA) or a Nondeterministc Finite Automaton(NFA) to recognize strings belonging to
$A$. Tempting as it is to try and create a regular expression for $A$, it turns out that $A$ is proveably not a regular language, and therefore there exist no regular expression that derives $A$.

To prove that $A$ is not regular, we will use a proof by contradiction and the **pumping lemma for regular languages**.

**Recall the pumping lemma for regular languages:**
> If $A$ is a regular language, then $\exists$ number $p$, the pumping length, where if $s \in A$ and $|s| \geq p$, then the string $s$ can be split into three pieces $s = xyz$, which must satisfy the following properties:
> 1. $xy^iz \in A$ for each $i \geq 0$
> 2. $|y| \gt 0$
> 3. $|xy| \leq p$

With this in mind, let's begin the proof.

**Proof:**  
Suppose that $A$ is a regular language. It must follow that $A$ has some pumping length $p$.  
Now consider the string $s = ab^pa(1.0)ab^pa \in A$, for which $|s| = p+p+9 = 2p+9 \geq p$, so the pumping lemma must hold for this such string.  
So, by the **pumping lemma**, we can split $s$ into $s = xyz$, which must satisfy properties 1-3 of the pumping lemma.   

This leaves us with:   
* $x = a$, so $|x| = 1$
* $y = b^k$, for some $0 \lt k \leq p-1$
* $z = b^ma(1.0)ab^pa$ for some $0 \lt m \lt p-1$

So $s = xyz$ implies:  
* $s = ab^kb^ma(1.))ab^pa$, so it follows that $k+m = p$

This split satisfies properties 2 & 3 above because:   
* $y = |k| \gt 0$, satisfying property 2
* $|xy| = |x| + |y|$ which is at most $p-1 + 1 = p \leq p$, satisfying property 3

Property 1 implies that $s = xy^2z = xyyz \in A$, but  
* $xyyz = ab^kb^kb^ma(1.0)ab^pa = ab^{k+k+m}a(1.0)ab^pa = ab^{p+k}a(1.0)ab^pa \notin A$
  because $k+m = p$ and $k \gt 0$.
  
Therefore, we have a **contradiction**, so $A$ cannot be regular.  
**End proof**

## A Pushdown Automaton(PDA) that recognizes $A$
Since $A$ is not a regular language, an NFA and DFA are not capable of recognizing it. However, since there exists a Context-Free Grammer $G$ for $A$, $A$ is a Context-Free Language. Due to this, $A$ can be recognized using a Pushdown Automaton(PDA). A PDA can be thought of as an
NFA or DFA with a stack "bolted on" for memory. This gives PDAs the extra feature of being able to remember and count symbols that they have seen before. This is especially useful in this problem because we need to count the number of `b` symbols, to ensure that the front and back of the
string have an even number of them, and we also need to match `(` with `)` to make sure that the floating point expression component of the string is valid as well. With the extra features of a PDA, we can design a finite state machine $M$ that recognizes the $L(G)$, which itself is $A$.

### Pushdown Automaton $M$
The most intuitive way to understand the PDA $M$ is to view the state machine diagram for it:   

![pda drawing drawio(1)](https://github.com/jackr276/Expression-Validation-with-a-PDA/assets/113046361/1205c8ae-bdf5-4aae-9cd4-0d8c5c649076)   

>[!NOTE]
> Notice how the transitions are of the form $a, a, \rightarrow b$. This is interpreted as "Read a from the input string, pop a off of the stack, push b onto the stack, move to the next state"

#### Examples
Let's see how this Pushdown Automaton processes the example string: `abba(1.1*(2.1/3.1)+((2.2*.8)+(1.2)))abba`. First, visually inspect the string and verify that it is in the langauge $A$.
On taking in $A$, the PDA executes as follows:
```
In q1. Read ε, pop ε, push $. Move to q2.
In q2. Read a, pop ε, push a. Move to q3.
In q3. Read b, pop ε, push b. Move to q3.
In q3. Read b, pop ε, push b. Move to q3.
In q3. Read a, pop ε, push a. Move to q4.
In q4. Read (, pop ε, push (. Move to q4.
In q4. Read 1, pop ε, push ε. Move to q5.
In q5. Read ., pop ε, push ε. Move to q7.
In q7. Read 1, pop ε, push ε. Move to q7.
In q7. Read *, pop ε, push ε. Move to q4.
In q4. Read (, pop ε, push (. Move to q4.
In q4. Read 2, pop ε, push ε. Move to q5.
In q5. Read ., pop ε, push ε. Move to q7.
In q7. Read 1, pop ε, push ε. Move to q7.
In q7. Read /, pop ε, push ε. Move to q4.
In q4. Read 3, pop ε, push ε. Move to q5.
In q5. Read ., pop ε, push ε. Move to q7.
In q7. Read 1, pop ε, push ε. Move to q7.
In q7. Read ), pop (, push ε. Move to q8.
In q8. Read +, pop ε, push ε. Move to q4.
In q4. Read (, pop ε, push (. Move to q4.
In q4. Read (, pop ε, push (. Move to q4.
In q4. Read 2, pop ε, push ε. Move to q5.
In q5. Read ., pop ε, push ε. Move to q7.
In q7. Read 2, pop ε, push ε. Move to q7.
In q7. Read *, pop ε, push ε. Move to q4.
In q4. Read ., pop ε, push ε. Move to q6.
In q6. Read 8, pop ε, push ε. Move to q7.
In q7. Read ), pop (, push ε. Move to q8.
In q8. Read +, pop ε, push ε. Move to q4.
In q4. Read (, pop ε, push (. Move to q4.
In q4. Read 1, pop ε, push ε. Move to q5.
In q5. Read ., pop ε, push ε. Move to q7.
In q7. Read 2, pop ε, push ε. Move to q7.
In q7. Read ), pop (, push ε. Move to q8.
In q8. Read ), pop (, push ε. Move to q8.
In q8. Read ), pop (, push ε. Move to q8.
In q8. Read a, pop a, push ε. Move to q9.
In q9. Read b, pop b, push ε. Move to q9.
In q9. Read b, pop b, push ε. Move to q9.
In q9. Read a, pop a, push ε. Move to q10.
In q10. Read ε, pop $, push ε. Move to q11.
In q11, the accepting state. String has been fully processed. String is accepted.
```

Let's also look at an example of a string that is not in $A$, the string: `abbbba(1.2*2.1))abbbba`. Upon visual inspection, we can see that the parenthesis are not properly matched, so the expression is not valid. Let's see how $M$ handles it:
```
In q1. Read ε, pop ε, push $. Move to q2.
In q2. Read a, pop ε, push a. Move to q3.
In q3. Read b, pop ε, push b. Move to q3.
In q3. Read b, pop ε, push b. Move to q3.
In q3. Read b, pop ε, push b. Move to q3.
In q3. Read b, pop ε, push b. Move to q3.
In q3. Read a, pop ε, push a. Move to q4.
In q4. Read (, pop ε, push (. Move to q4.
In q4. Read 1, pop ε, push ε. Move to q5.
In q5. Read ., pop ε, push ε. Move to q7.
In q7. Read 2, pop ε, push ε. Move to q7.
In q7. Read *, pop ε, push ε. Move to q4.
In q4. Read 2, pop ε, push ε. Move to q5.
In q5. Read ., pop ε, push ε. Move to q7.
In q7. Read 1, pop ε, push ε. Move to q7.
In q7. Read ), pop (, push ε. Move to q8.
In q8. Read ), pop ε, push ε. PDA crashes.
```
Notice how upon reading the unmatched `)`,  the PDA crashes. This happens because it has no valid transitions out of the state q8 with the current state of the stack, meaning that the parenthesis must not be matched. A PDA crashing is a way of rejecting the string, so we 
know that `abbbba(1.2*2.1))abbbba` is not in the language $A$.

### Programmatic Implementation
The C++ program [pda.cpp](https://github.com/jackr276/Expression-Validation-with-a-PDA/blob/main/src/pda.cpp) implements the PDA $M$ into an interactive program. The program itself is very simple and well documented, so the exact details of how it works will not be re-explained here. The program
allows the user to test as many strings as they please with the PDA, and provides detailed output upon every transition that the PDA makes.

#### Running this program
The runner script [run.sh](https://github.com/jackr276/Expression-Validation-with-a-PDA/blob/main/run.sh) is provided for ease of compilation and execution. To run this program using the runner script, download the entirety of this project and navigate to the folder where it was downloaded.
Following this, run the following commands:
```console
example@bash:~$ chmod +x run.sh
example@bash:~$ ./run.sh
Do you want to use the given test cases?[Y/n]:
```
At this stage, if you type `Y`, the program will be run with the 15 test cases that are provided in the [tests](https://github.com/jackr276/Expression-Validation-with-a-PDA/tree/main/tests) folder. This is a convenient and typing-free option if you just want to see what some output on example
strings looks like. If you type `n`, then the program control will be given to you, and you will enter the strings that you want to process one by one.


