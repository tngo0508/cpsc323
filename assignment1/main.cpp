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
	int value;			//hold numeric value for a character
	map<char, int> M;
	int l, r, result;

	do {

		int index = 0;
		cout << "Enter an expression: ";
		cin >> input;

		result = 0;
		for (int i = 0; i < input.length(); i++) {
			//If the next character is an operator
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
				//convert characters into their correspondence value and store in a stack
				if (M.count(input[i]) < 1) {
					cout << "Enter value for " << input[i] << " : ";
					cin >> value;
				}
				M.insert(std::make_pair(input[i], value));
				for (auto it = M.begin(); it != M.end(); it++) {
					if (input[i] == it->first) {
						stack.push(it->second);
					}
				}
			}
		}

		cout << "Sum is: " << stack.peek() << endl;
		//stack.clear();
		M.clear();

		cout << "Do you want to continue (Y/N): ";
		cin >> option;

	} while (option == 'y' || option == 'Y');

	cout << endl;
	return 0;
}
