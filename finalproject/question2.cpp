#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <vector>
#include <stack>
#include <unordered_map>

using namespace std;


// Generic function to convert the character into number to look up within the vector
int TestFunc(string& str, vector<string>& states) {
	int j = -1;
	for (int i = 0; i < states.size(); i++) {
		if (str == states[i]) {
			j = i;
			return j;
		}
	}
	return j;
}

bool process_identifier(string& id, stack<string> myStack) {

	return true;
}

int main() {
	// Store the number of states
	int states_number = 0;

	fstream input;
	fstream programInputFile;
	ofstream output;
	input.open("parsing_table.txt", ios_base::in);
	if (!input) {
		cout << "Cannot find the parsing table" << endl;
		cout << "Program exits" << endl;
		return 0;
	}

	bool legit = false;
	vector<string> cols;
	unordered_map<string, vector<string>> myMap;
	string dummy_str;
	string key;
	for (int i = 1; input >> dummy_str; i++) {
		cols.push_back(dummy_str);
		if (dummy_str == "(") {
			legit = true;
			states_number = i;
		}
		if (legit == true && i % states_number == 0) {
			key = cols[0];
			cols.erase(cols.begin());
			myMap.insert(make_pair(key, cols));
			cols.clear();
		}
	}
	output.open("output.txt");
	cout << "Testing parsing table" << endl;
	for (auto it = myMap.begin(); it != myMap.end(); it++) {
		cout << setw(4) << it->first;
		for (auto data : it->second) {
			cout << setw(4) << data << " ";
		}
		cout << endl;
	}

	cout << endl << endl << endl << endl << endl;

	////////////////////////////////////
	// BEGIN THE MEAT OF THIS PROGRAM //
	////////////////////////////////////

	// Vector of strings to hold individual word within the program ignoring spaces and newlines
	// PROGRAM S2017 becomes { (PROGRAM), (S2017), .... }
	vector<string> program;

	// Check for identifier such as S2017, since it's composed of P|Q|R|S follows by P|Q|R|S or 0 -> 9
	// We have to check individual character separately, variable identifier holds such string
	string identifier;


	string input_word;			// Reading word inputs
	string stack_front_value;	// Storing data after popping the stack
	string value_in_table;		// Storing the lookup data inside parsing table
	stack<string> myStack;		// Main stack to work with

	// Whats this?
	vector<string> vstack;

	// Read in the program
	programInputFile.open("program.txt", ios_base::in);
	if (!programInputFile) {
		cout << "Fail to open program text file";
		return 0;
	}

	// Dummy variable storing the word read from the program file, then it is pushed into the program vector
	string dummyVar;
	while (programInputFile >> dummyVar) {
		if (dummyVar == "PROGRAM") {
			dummyVar = "p";
		}
		else if (dummyVar == "BEGIN") {
			dummyVar = "b";
		}
		else if (dummyVar == "INTEGER") {
			dummyVar = "i";
		}
		else if (dummyVar == "PRINT") {
			dummyVar = "c";
		}
		else if (dummyVar == "END."){
			dummyVar = "$";
		}
		program.push_back(dummyVar);
	}


	// Save the first key->value pair in map since it will be erased for the following reasons:
	//  -it makes adding the starting symbol into the stack more easily
	//  -look up function needs the states to return value of a cells
	vector<string> states;
	auto it = myMap.begin();
	for (string elm : it->second) {
		states.push_back(elm);
	}
	// Erase the first line since it contains irrelevant information (eg. states i + - * / ( ) $)
	myMap.erase(myMap.begin());

	// Push $ onto stack
	//myStack.push("$");

	// Push the starting symbol
	myStack.push(myMap.begin()->first);
	
	// Read first word of the program
	input_word = program[0];

	// Keeping track of where we are in the program, since first word index 0 was read above, the next time will be the next 
	// word which is program[i] where i = 1, 2, ... , program.size() - 1
	int word_index = 1;

	// Keep track of how many words total in the program
	int programLength = program.size();
	
	// Keep looping if there are still words
	while (word_index < program.size()+1) {
		cout << "INPUT WORD: " << input_word << endl << endl;
		// Check for identifier by checking the first character if it is P|Q|R|S
		if (input_word[0] == 'P' || input_word[0] == 'Q' || input_word[0] == 'R' || input_word[0] == 'S') {
			// Process each character individually

			identifier = input_word[0];
			cout << "IDENTIFIER: " << identifier << endl << endl;
			int word_length = input_word.length();
			int j = 1;
			while (word_length > 0) {
				// Pop the stack
				stack_front_value = myStack.top();
				myStack.pop();
				// When there is a match, we move on to the next word in the program
				if (stack_front_value == identifier) {
					identifier = input_word[j];
					word_length--;
					j++;
				}
				else {
					// Look for [stack_front_value, input_word] in the table
					auto search = myMap.find(stack_front_value);
					// Check to see if the character that was read is actually one of the tokens
					if (TestFunc(identifier, states) > -1 && TestFunc(identifier, states) < search->second.size()) {
						value_in_table = search->second[TestFunc(identifier, states)];
						cout << "TESTING VARIABLE value_in_table = " << value_in_table << endl;
						// If the cell in the table is a lamda, then pop the next character in the stack
						if (value_in_table == "&") {
							continue;
						}
						// If the tracing ends up at one of the empty cell in the parsing table (labeled ! in this program), then the expression is not a word
						if (value_in_table == "!") {
							break;
						}
					}
					// If the expression has something that is not one of the tokens, then the expression is not a word
					else {
						cout << "ERROR" << endl;
						break;
					}
					// Push the string onto the stack in reverse order
					for (int i = value_in_table.length() - 1; i > -1; i--) {
						myStack.push(string(1, value_in_table[i]));
					}
				}
			} // End while loop

			input_word = program[word_index];
			word_index++;
			programLength--;
		}// End identifier processing

		// Pop the stack
		stack_front_value = myStack.top();
		myStack.pop();

		// When there is a match, we move on to the next word in the program
		if (stack_front_value == input_word) {
			if (word_index != 50) {
				input_word = program[word_index];
			}
			programLength--;
			word_index++;
			
		}
		else {
			// Look for [stack_front_value, input_word] in the table
			auto search = myMap.find(stack_front_value);
			// Check to see if the character that was read is actually one of the tokens
			if (TestFunc(input_word, states) > -1 && TestFunc(input_word, states) < search->second.size()) {
				value_in_table = search->second[TestFunc(input_word, states)];
				cout << "TESTING VARIABLE value_in_table = " << value_in_table << endl;
				// If the cell in the table is a lamda, then pop the next character in the stack
				if (value_in_table == "&") {
					continue;
				}
				// If the tracing ends up at one of the empty cell in the parsing table (labeled ! in this program), then the expression is not a word
				if (value_in_table == "!") {
					break;
				}
			}
			// If the expression has something that is not one of the tokens, then the expression is not a word
			else {
				cout << "ERROR" << endl;
				break;
			}
			// Push the string onto the stack in reverse order
			for (int i = value_in_table.length() - 1; i > -1; i--) {
				myStack.push(string(1, value_in_table[i]));
			}
		}
	}// End while loop

	// Things in stack
	while (myStack.size() > 0) {
		vstack.push_back(myStack.top());
		myStack.pop();
	}
	cout << "Stack: ";
	for (int i = vstack.size() - 1; i < vstack.size(); i--) {
		cout << vstack[i];
	}

	cout << endl;
	if (vstack.size() == 0) {
		cout << "Program accepted" << endl;
	}
	else {
		cout << "Program is not accepted" << endl;
	}


	cout << endl;
	return 0;
}
