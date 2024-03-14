/**
 * Jack Robbins
 * UCID: jmr226
 * Section 010
 * Semester: Spring 2024
 * Implementation of a PDA for project 2
 */

#include <iostream>
#include <stack>
#include <sstream>

using namespace std;

int main(){
	//Predeclare main PDA function
	bool pda(string word);

	int numStrings;
	//prompt user for number of strings to enter
	cout << "\nEnter the number of strings that you would like to process: ";
	cin >> numStrings;

	cout << "\nProcessing " << numStrings << " string" << (numStrings == 1 ? "" : "s") << endl;

	//Main processing loop, simply calls pda function and prints appropriate message
	for(int i = 1; i <= numStrings && numStrings > 0; i++) {
		string word;
		printf("Enter string %d of %d: ", i, numStrings);
		cin >> word;
	
		cout << "\nProcessing string: " << word << endl;

		if(pda(word)) {
			cout << "\n" << word << " is in the language\n" << endl;
		} else {
			cout << "\n" << word << " is not in the language\n" << endl;
		}
	}

	return 0;
}


bool pda(string word){
	//All states in our pda
	enum pdaState{q1=1, q2, q3, q4, q5, q6, q7, q8, q9, q10, q11};
	//All strings begin in q1
	pdaState currstate = q1;
	//Stack for pushing and popping
	stack<char> langStack;
	//Stringstream will be used for stepping through string
	stringstream w(word);
	//Grabber for each char
	char ch;
	//Keep track of whether or not we are in an accepting state
	bool inAccept;
	
	//Main loop keeps going so long as entire stringstream hasn't been consumed
	while(w.get(ch)){
			
	}


	return inAccept;
}
