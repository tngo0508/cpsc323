#include <iostream>
using std::cin;
using std::cout;
using std::endl;

#include <string>
using std::string;

#include <vector>
using std::vector;

bool isDigit(string& s) {
	for (int i = 0; i < s.length(); i++) {
		if (isdigit(s[i]) == false) {
			return false;
		}
	}
	return true;
}

bool isIdentifier(string& s) {
	//Identifier is a combination of letters, integers, and underscores with no integer being the first character
	//assume that people follow rules and dont put special characters in
	if (isdigit(s[0]) == true) {
		return false;
	}
	else {
		return true;
	}
}

bool isSpecial(string& s, vector<string>& list) {
	for (string str : list) {
		if (s == str) {
			return true;
		}
	}
	return false;
}

bool isReservedWord(string& s, vector<string>& list) {
	for (string str : list) {
		if (s == str) {
			return true;
		}
	}
	return false;
}

string checkType(string& s, vector<string>& specialList, vector<string>& reservedWordList) {
	if (isDigit(s)){
		return "Digit";
	}
	else if (isSpecial(s, specialList)) {
		return "Special";
	}
	else if (isReservedWord(s, reservedWordList)) {
		return "Reserved Word";
	}
	else if (isIdentifier(s)) {
		return "Identifier";
	}
	else {
		return "Not Identifier";
	}

}

int main() {
	
	//char reservedWords[4][10] = { "cout<<", "for", "int", "while" };
	//char special[8][3] = { "=", "*", "-", ";", "(", ")", "<=", "+" };

	vector<string> reservedWords{ "cout<<", "for", "int", "while" };
	vector<string> special{ "=", "*", "-", ";", "(", ")", "<=", "+" };

	string input;

	cout << "Enter an expression: ";
	getline(cin, input);
	
	cout << checkType(input,special,reservedWords) << endl;

	return 0;
}
