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

int main() {
	// Store the number of states
	int states_number = 0;

	fstream input;
	input.open("parse_table2.txt", ios_base::in);
	if (!input) {
		cout << "Cannot find the parsing table" << endl;
		cout << "Program exits" << endl;
		return 0;
	}

	vector<string> cols;
	unordered_map<string, vector<string>> myMap;
	string dummy_str;
	string key;
	for (int i = 1; input >> dummy_str; i++) {
		cols.push_back(dummy_str);
		if (dummy_str == "$") {
			states_number = i;
		}
		if (states_number != 0 && i % states_number == 0) {
			key = cols[0];
			cols.erase(cols.begin());
			myMap.insert(make_pair(key, cols));
			cols.clear();
		}
	}

	cout << "Testing parsing table" << endl;
	for (auto it = myMap.begin(); it != myMap.end(); it++) {
		cout << setw(10) << it->first;
		for (auto data : it->second) {
			cout << setw(10) << data << " ";
		}
		cout << endl;
	}


	string exp;
	stack<string> myStack;
	vector<string> vstack;

	cout << endl << endl << endl << endl << endl;
	cout << "Enter an expression: ";
	cin >> exp;
	string a;	// Reading inputs
	string b;	// Storing data after popping the stack
	string c;	// Storing the lookup data inside parsing table

	vector<string> states;
	auto it = myMap.begin();
	for (string elm : it->second) {
		states.push_back(elm);
	}
	// Erase the first line since it contains irrelevant information (eg. states i + - * / ( ) $)
	myMap.erase(myMap.begin());
	// Push $ onto stack
	myStack.push("$");
	// Push the starting symbol
	myStack.push(myMap.begin()->first);
	// Read first character of the input
	a = exp[0];
	int i = 1;
	int str_size = exp.length();
	//cout << exp.length();
	while (str_size > 0) {

		// Pop the stack
		b = myStack.top();
		myStack.pop();

		// When there is a match, we move on to the next character in the expression
		if (b == a) {
			a = exp[i];
			str_size--;
			i++;
		}
		else {
			// Look for [b,a]
			auto search = myMap.find(b);
			// Check to see if the character that was read is actually one of the tokens
			if (TestFunc(a, states) > -1 && TestFunc(a, states) < search->second.size()) {
				c = search->second[TestFunc(a, states)];
				cout << "TESTING VARIABLE c = " << c << endl;
				// If the cell in the table is a lamda, then pop the next character in the stack
				if (c == "&") {
					continue;
				}
				// If the tracing ends up at one of the empty cell in the parsing table (labeled 0 in this program), then the expression is not a word
				if (c == "0") {
					break;
				}
			}
			// If the expression has something that is not one of the tokens, then the expression is not a word
			else {
				cout << "ERROR" << endl;
				break;
			}
			// Push the string onto the stack in reverse order
			for (int i = c.length() - 1; i > -1; i--) {
				myStack.push(string(1, c[i]));
			}
		}
	}

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
		cout << "Word accepted" << endl;
	}
	else {
		cout << "Word is not accepted" << endl;
	}


	cout << endl;
	return 0;
}
