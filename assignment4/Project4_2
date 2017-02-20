#include <iostream>
using std::cin;
using std::cout;
using std::endl;

#include <string>
using std::string;
using std::getline;

#include <fstream>
using std::ifstream;
using std::ofstream;

string RemoveComment(string& s) {
	string a;
	int j = 0;
	for (int i = 0; i < s.length(); i++) {
		j = i;
		if (s[j] == '/' && s[j++] == '/') {
			break;
			
		}
		else {
			a.push_back(s[i]);
		}
	}
	return a;
}

int main() {
	char token[] = { '{', '}', '(', ')', '+','-','/','*','%',';','=',',',':', };

	// Open a file and read from it
	ifstream input("file.txt", std::ios_base::in);
	if (input.fail()) {
		cout << "Cannot open file" << endl;
		return 0;
	}
	string a;
	string b;

	// Read in text in the file line by line into a string
	while (getline(input, a)) {
		//check for empty line
		if (RemoveComment(a) == "") {
			continue;
		}

		//Check for comments
		cout << RemoveComment(a) << endl;

		//cout << a << endl;
	}

	return 0;
}
