# Author: Jack Robbins
# This is a simple runner script that runs the PDA

#!/bin/bash

file=$1

#Ensure filename is valid
if [[ ! -f $file ]]; then
	echo "Invalid file name"
	exit 1;
fi

read -p "Enter name of testing file: " TESTS
read -p "Enter name of output file: " OUTPUT

name=$(basename -s .cpp "$file")

g++ -Wall -Wextra $file -o $name


./${name} < TESTS > OUTPUT
