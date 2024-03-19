# Author: Jack Robbins
# This is a simple runner script that runs the PDA

#!/bin/bash

#Ensure file exists
if [[ ! -f ./src/pda.cpp ]]; then
	echo "Source code file \"pda.cpp\" not found"
	exit 1;
fi

read -p "Do you want to use the given test cases?[Y/n]: " USEGIVEN

#Compile with aggressive warnings
g++ -Wall -Wextra ./src/pda.cpp -o ./src/pda


#If the user wants to use given test cases, pipe them in
if [[ $USEGIVEN == "Y" ]] || [[ $USEGIVEN == "y" ]]; then
	./src/pda < tests/test_cases.txt
	exit 0;
fi

#otherwise hand control over to the program for input
./src/pda

