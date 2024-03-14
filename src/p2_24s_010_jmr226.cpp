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
#include <string>

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
	enum pdaState{q1=1, q2, q3, q4, q5, q6, q7, q8, q9, q10};
	//All 10 digits for ease of finding
	string numbers = "0123456789";
	//All potential operators
	string operators = "+-/*";
	//All strings begin in q1
	pdaState currstate = q1;
	//Stack for pushing and popping
	stack<char> langStack;
	//Stringstream will be used for stepping through string
	stringstream w(word);
	//Grabber for each char
	char ch;
	
	//Main loop keeps going so long as entire stringstream hasn't been consumed
	while(w.get(ch)){
		switch(currstate){
			//start state, all strings begin here
			case q1:
				//Read nothing, pop nothing, push $(stack marker)
				langStack.push('$');
				//Move to q2
				currstate = q2;
				//we don't need the character here, simply pushing $ to stack
				w.putback(ch);
			
				break;
			
			case q2:
				//First character seen must be a
				if(ch != 'a'){
					return false;
				}	
				//read a, pop nothing, push a, move to q3
				langStack.push('a');
				currstate = q3;
				
				break;

			case q3:
				//We can see as many b's as we want
				if(ch == 'b'){
					langStack.push('b');
					currstate = q3;
				} else if(ch == 'a') {
					langStack.push('a');
					currstate = q4;
				} else {
					//crash
					return false;
				}

				break;

			case q4:
				if(ch == '('){
					langStack.push('(');
					currstate = q4;
				} else if(ch == '.'){
					currstate = q6;
				} else if(numbers.find(ch) != string::npos){
					currstate = q5;
				} else {
					//crash
					return false;
				}
			
				break;

			case q5:
				if(numbers.find(ch) != string::npos){
					currstate = q5;
				} else if(ch == '.') {
					currstate = q7;
				} else {
					//crash
					return false;
				}

				break;

			case q6:
				if(numbers.find(ch) != string::npos){
					currstate = q7;
				} else {
					//crash
					return false;
				}

				break;
			
			case q7:
				if(numbers.find(ch) != string::npos){
					currstate = q7;
				} else if(ch == ')' && langStack.top() == '(') {
					langStack.pop();
					currstate = q8;
				} else if(ch == 'a' && langStack.top() == 'a'){
					//pop a
					langStack.pop();
					currstate = q9;
				} else if(operators.find(ch) != string::npos) {
					currstate = q4;
				} else {
					//crash
					return false;
				}

				break;

			case q8:
				if(ch == ')' && langStack.top() == '('){
					langStack.pop();
					currstate = q8;
				} else if(operators.find(ch) != string::npos){
					currstate = q4;
				} else if(ch == 'a' && langStack.top() == 'a') {
					langStack.pop();
					currstate = q9;
				}else {
					//crash
					return false;
				}

				break;

			case q9:
				if(ch == 'b' && langStack.top() == 'b'){
					langStack.pop();
					currstate = q9;
				} else if(ch == 'a' && langStack.top() == 'a'){
					langStack.pop();
					currstate = q10;
				} else {
					//crash
					return false;
				}

				break;

			default:
				return false;
		}
	}

	return langStack.top() == '$';
}
