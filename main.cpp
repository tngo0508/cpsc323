/*
Purpose: to compute postfix expressions


what to do?
-read expression into a string variable
-convert from postfix to infix and store the final result as a string
-ask user for the values associate with the alphabets they input
-replace alphabets with actual numbers
-convert string to normal expresion and evaluate

TODO: Error handling
*/

#include <iostream>
using std::cout;
using std::cin;
using std::endl;

#include <map>
using std::map;

#include <string>
using std::string;

#include "VectorBased.h"
#include "FLVector.h"


int main() {

	char option;		//flag to continue or exit the program
	string input;
	VStack<int> stack;
	int value;
	map<char, int> M;

	do {



		int index = 0;
		cout << "Enter an expression: ";
		cin >> input;

		string dinput = input;
		FLVector<char> alphabet(input.length(), '0');
		FLVector<char> data(input.length(), '0');

		for (int i = 0; i < dinput.length(); i++) {
			for (int j = 0; j < dinput.length(); j++) {
				if ((i != j) && (dinput[j] == dinput[i])) {
					dinput[j] = '0';
				}
			}
		}


		for (int i = 0; i < dinput.length(); i++) {
			if (dinput[i] == '0' || dinput[i] == '+' || dinput[i] == '-' || dinput[i] == '*' || dinput[i] == '/') {
				continue;
			}
			alphabet.add(index, dinput[i]);
			index++;

		}

		//associate characters with value set by user
		for (int i = 0; i < alphabet.length(); i++) {
			if (alphabet.get(i) != '0') {
				cout << "Enter value for " << alphabet.get(i) << " : ";
				cin >> value;
				M.insert(std::make_pair(alphabet.get(i), value));
			}
		}


		int l, r, var, result = 0;
		for (int i = 0; i < input.length(); i++) {
			if (input[i] == '+' || input[i] == '-' || input[i] == '*' || input[i] == '/') {
				r = stack.peek();
				stack.pop();
				l = stack.peek();
				stack.pop();

				switch (input[i]) {
				case '+': result = l + r;
					break;
				case '-': result = l - r;
					break;
				case '*': result = l * r;
					break;
				case '/': result = l / r;
					break;
				}
				stack.push(result);
			}
			else {
				//convert characters into their correspondence value
				for (auto it = M.begin(); it != M.end(); it++) {
					if (input[i] == it->first) {
						var = it->second;
						stack.push(var);
					}
				}
			}
		}

		cout << "Sum is: " << stack.peek() << endl;
		stack.clear();

		cout << "Do you want to continue (Y/N): ";
		cin >> option;

	} while (option == 'y' || option == 'Y');

	cout << endl;
	return 0;
}