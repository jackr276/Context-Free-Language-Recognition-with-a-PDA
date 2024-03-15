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


/**
 * The main function simply gets user input and calls the pda function, printing out the appropriate
 * input based on the result
 */
int main(){
	//Predeclare main PDA function
	bool pda(string word);
	//Big print statement
	printf("Project 2 for CS 341\nSection number: 010\nSemester: Spring 2024\nWritten by: Jack Robbins, jmr226\nInstructor: Marvin Nakayama");

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

		//Print out appropriate message
		if(pda(word)) {
			cout << "\n" << word << " is in the language\n" << endl;
		} else {
			cout << "\n" << word << " is not in the language\n" << endl;
		}
	}
	return 0;
}


/**
 * The PDA function simulates a pushdown automaton that recognizes the language. The PDA is simulated using
 * a while loop for grabbing chars, an enumerated pdaState type, and a large swtich statement. If at any point the
 * PDA crashes, this function hard exits by returning false.
 */
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
			//start state, all strings begin here. The PDA never returns to here
			case q1:
				cout << "In q1. Read nothing, pop nothing, push '$'. Move to q2." << endl;
				//Read nothing, pop nothing, push $(stack marker)
				langStack.push('$');
				//Move to q2
				currstate = q2;
				//we don't need the character here, simply pushing $ to stack
				w.putback(ch);

				break;
		
			//We enter here immediately after the start state, and we must see an 'a'
			case q2:
				//First character seen must be a
				if(ch != 'a'){
					cout << "In q2. Read '" << ch << "', pop nothing, push nothing. PDA crashes." << endl;
					return false;
				}
				cout << "In q2. Read 'a', pop nothing, push 'a'. Move to q3." << endl;
				//read a, pop nothing, push a, move to q3
				langStack.push('a');
				currstate = q3;
				
				break;

			//In q3, we can see as many b's as we want. We can only exit q3 by reading an 'a'
			case q3:
				//We can see as many b's as we want
				if(ch == 'b'){
					//Keep track of the 'b's on the stack
					cout << "In q3. Read 'b', pop nothing, push 'b'. Move to q3." << endl;
					langStack.push('b');
					currstate = q3;
				} else if(ch == 'a') {
					//if we see an 'a', leave q4
					cout << "In q3. Read 'a', pop nothing, push 'a'. Move to q4." << endl;
					langStack.push('a');
					currstate = q4;
				} else {
					//crash
					cout << "In q3. Read '" << ch << "', pop nothing, push nothing. PDA crashes." << endl;
					return false;
				}

				break;
			
			//In q4, we can read as many '('s as we want. This state can only be left on reading '.' or a number
			case q4:
				//Keep track of the lParens on the stack
				if(ch == '('){
					cout << "In q4. Read '(', pop nothing, push '('. Move to q4." << endl;
					langStack.push('(');
					currstate = q4;
				} else if(ch == '.'){
					//q6 is the '.' state
					cout << "In q4. Read '.', pop nothing, push nothing. Move to q6." << endl;
					currstate = q6;
				} else if(numbers.find(ch) != string::npos){
					//If we see a number, move to q5
					cout << "In q4. Read '" << ch <<"', pop nothing, push nothing. Move to q5." << endl;
					currstate = q5;
				} else {
					//crash
					cout << "In q4. Read '" << ch << "', pop nothing, push nothing. PDA crashes." << endl;
					return false;
				}
			
				break;
	
			//In q5, we can see as many numbers as we want, and exit upon seeing a '.'
			case q5:
				//Numbers result in the PDA staying in q5
				if(numbers.find(ch) != string::npos){
					cout << "In q5. Read '" << ch <<"', pop nothing, push nothing. Move to q5." << endl;
					currstate = q5;
				//The '.' will escape this state
				} else if(ch == '.') {
					cout << "In q5. Read '.', pop nothing, push nothing. Move to q7." << endl;
					currstate = q7;
				} else {
					//crash
					cout << "In q5. Read '" << ch << "', pop nothing, push nothing. PDA crashes." << endl;
					return false;
				}

				break;

			//If they PDA is in q6, it means that we've seen a dot before seeing a number 
			case q6:
				//We must see a number to move on
				if(numbers.find(ch) != string::npos){
					cout << "In q6. Read '" << ch << "', pop nothing, push nothing. Move to q7." << endl;
					currstate = q7;
				} else {
					//crash
					cout << "In q6. Read '" << ch << "', pop nothing, push nothing. PDA crashes." << endl; 
					return false;
				}

				break;
			
			//If we get to q7, we can see as many digits as we want, and exit upon seeing 'a', ')' or an operator
			case q7:
				//We can see as many numbers as we want, so stay in q7
				if(numbers.find(ch) != string::npos){
					cout << "In q7. Read '" << ch << "', pop nothing, push nothing. Move to q7." << endl;
					currstate = q7;
				//Once we see a ')' and can pop a '(' off the stack, move to q8
				} else if(ch == ')' && langStack.top() == '(') {
					cout << "In q7. Read ')', pop '(', push nothing. Move to q8." << endl; 
					langStack.pop();
					currstate = q8;
				//If we see an a and can pop an a, move to q9 to begin accepting sequence
				} else if(ch == 'a' && langStack.top() == 'a'){
					cout << "In q7. Read 'a', pop 'a', push nothing. Move to q9." << endl;
					//pop a
					langStack.pop();
					currstate = q9;
				//If we see an operator, we must see another number, so move back to q4
				} else if(operators.find(ch) != string::npos) {
					cout << "In q7. Read '" << ch << "', pop nothing, push nothing. Move to q4." << endl;
					currstate = q4;
				} else {
					//crash
					cout << "In q7. Read '" << ch << "', pop nothing, push nothing. PDA crashes." << endl;
					return false;
				}

				break;

			//In q8, we can read as many ')' as the stack allows, and we exit upon seeing an 'a' or an operator
			case q8:
				//As long as these are matched in the stack, we can proceed
				if(ch == ')' && langStack.top() == '('){
					cout << "In q8. Read ')', pop '(', push nothing. Move to q8." << endl;
					langStack.pop();
					currstate = q8;
				//If we see an operator, there must be another number after it, so return to q4
				} else if(operators.find(ch) != string::npos){
					cout << "In q8. Read '" << ch << "', pop nothing, push nothing. Move to q4." << endl;
					currstate = q4;
				//If we see an 'a', we begin checking the final sequence
				} else if(ch == 'a' && langStack.top() == 'a') {
					cout << "In q8. Read 'a', pop 'a', push nothing. Move to q9." << endl;
					langStack.pop();
					currstate = q9;
				}else {
					//crash
					cout << "In q8. Read '" << ch << "', pop nothing, push nothing. PDA crashes." << endl;
					return false;
				}

				break;

			//If we make it here, we've already seen 'a' and we can now see as many b's as are on the stack
			case q9:
				//There is no limit to the number of b's that we can see, so stay in q9
				if(ch == 'b' && langStack.top() == 'b'){
					cout << "In q9. Read 'b', pop 'b', push nothing. Move to q9." << endl;
					langStack.pop();
					currstate = q9;
				//once we see an 'a', we move to q10
				} else if(ch == 'a' && langStack.top() == 'a'){
					cout << "In q9. Read 'a', pop 'a', push nothing. Move to q10." << endl;
					langStack.pop();
					currstate = q10;
				} else {
					//crash
					cout << "In q9. Read '" << ch << "', push nothing, pop nothing. PDA crashes." << endl;
					return false;
				}

				break;

			//We only end up here if we read a's after we've exceeded the number of a's in the front
			default:
				cout << "In " << currstate <<". Read '" << ch << "', pop nothing, push nothing. PDA crashes." << endl;
				return false;
		}
	}

	//If we end and the end of the stack is the stack marker('$'), the string has passed through successfully
	if(langStack.top() == '$'){
		cout << "In q10. Read nothing, pop '$', push nothing. Move to q11 and accept." << endl; 
	} else {
		cout << "In q10. Read nothing, pop '" << langStack.top() << "', push nothing. PDA crashes" << endl;
	}

	//Return based on if the top of stack is '$'
	return langStack.top() == '$';
}
