#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <vector>
#include <stack>
#include <unordered_map>

using namespace std;

int CharToInt(string& str) {
	char s = str[0];
	switch (s) {
	case 'i':
		return 0;

	case '+':
		return 1;

	case '-':
		return 2;

	case '*':
		return 3;

	case '/':
		return 4;

	case '(':
		return 5;

	case ')':
		return 6;

	case '$':
		return 7;

	default:
		return -1;
	}

}

int main() {
	fstream input;
	input.open("parse_table.txt", ios_base::in);
	if (!input) {
		cout << "Cannot find the parsing table" << endl;
		cout << "Program exits" << endl;
		return 0;
	}

	vector<string> cols;
	unordered_map<string, vector<string>> myMap;
	string dummy_str;
	string key;
	for(int i = 1; input >> dummy_str; i++){
		cols.push_back(dummy_str);
		if (i % 9 == 0) {
			key = cols[0];
			cols.erase(cols.begin());
			myMap.insert(make_pair(key,cols));
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
	
	// Erase the first line since it contains irrelevant information (eg. states i + - * / ( ) $)
	myMap.erase(myMap.begin());
	// Push $ onto stack
	myStack.push("$");
	// Push the starting symbol
	myStack.push(myMap.begin()->first);
	// Read first character of the input
	a = exp[0];
	int i = 1;
	cout << exp.length();
	while(i < exp.length() + 1){
		
		// Pop the stack
		b = myStack.top();
		myStack.pop();

		// When there is a match, we move on to the next character in the expression
		if (b == a) {
			a = exp[i];
			i++;
		}else {
			// Look for [b,a]
			auto search = myMap.find(b);
			if (CharToInt(a) > -1 && CharToInt(a) < search->second.size()) {
				c = search->second[CharToInt(a)];
				cout << "TESTING VARIABLE c = " << c << endl;
				if (c == "&") {
					continue;
				}
			}
			else {
				cout << "ERROR" << endl;
			}
			// Push the string onto the stack in reverse order
			for (int i = c.length() - 1; i > -1; i--) {
				myStack.push(string(1, c[i]));
			}
		}
	}







	// Things in stack
	while (myStack.size() > 0){
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
		cout << "Word is not accepted or you screw up" << endl;
	}

	cout << endl;
	return 0;
}
