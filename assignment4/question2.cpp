#include <iostream>
using std::cin;
using std::cout;
using std::endl;

#include <string>
using std::string;
using std::getline;
using std::begin;
using std::end;

#include <fstream>
using std::ifstream;
using std::ofstream;

string RemoveComment(string& s) {
	string str;
	int j = 0;
	for (int i = 0; i < s.length(); i++) {
		j = i;
		if (s[j] == '/' && s[j++] == '/') {
			break;

		}
		else {
			str.push_back(s[i]);
		}
	}
	return str;
}

string RemoveSpaces(string& s) {
	string str;
	for (int i = 0, k = 1; i < s.length(); i++, k++) {

		if (s[i] != ' ') {
			// If first character is not a space, add to string
			if (i == 0) {
				str.push_back(s[i]);

			// If ith character is not a space and i++th character is a space, add both of them
			}else if (s[k] == ' ') {
				str.push_back(s[i]);
				str.push_back(s[k]);
			}

			// If ith character is not a space, add it
			else {
				str.push_back(s[i]);
			}
			
		}
	}

	return str;
}

string AddSpace(string& s, char token[]) {
	string str;
	int a = 0;
	for (int i = 0; i < s.length(); i++) {
		a = i;
		for (int j = 0; j < 13; j++) {
			if (s[i] == token[j]) {
				if (s[a--] != ' ') {
					s.insert(i, 1, ' ');
					i++;
					a = i;
				}
				if (s[a++] != ' ') {
					s.insert(a++, 1, ' ');
					a = i;
				}

			}
		}
	}

	return s;
}


int main() {
	char token[] = { '{', '}', '(', ')', '+','-','/','*','%',';','=',',',':', };

	// Open a file and read from it
	ifstream input("file2.txt", std::ios_base::in);
	if (input.fail()) {
		cout << "Cannot open file" << endl;
		return 0;
	}
	string a;
	string b;
	string c;
	string d;

	// Read in text in the file line by line into a string
	while (getline(input, a)) {
		b = RemoveComment(a);
		c = AddSpace(b, token);
		d = RemoveSpaces(c);
		//check for empty line
		if (d == "") {
			continue;
		}



		cout << d << endl;

		//cout << a << endl;
	}

	return 0;
}
