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


string RemoveSpaces(string& s) {
	string str;
	for (int i = 0, k = 1; i < s.length(); i++, k++) {

		if (s[i] != ' ') {
			// If first character is not a space, add to string
			if (i == 0) {
				str.push_back(s[i]);

			// If ith character is not a space and i++th character is a space, add both of them
			}
			else if (s[k] == ' ') {
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
	int a = 0;

	// Insert a space at the beginning in order for RemoveSpace() to work
	s.insert(0, 1, ' ');
	for (int i = 0; i < s.length(); i++) {
		a = i;
		for (int j = 0; j < 13; j++) {
			if (s[i] == token[j]) {

				// If a token is found, add spaces before and after, doesnt matter if there's already space since RemoveSpaces() will take care of extra spaces
				s.insert(i, 1, ' ');
				a = i + 2;

				s.insert(a, 1, ' ');
				i++;

			}
		}
	}
	return s;
}

string RemoveComment(string& s) {
	string str;
	int j = 0;
	for (int i = 0; i < s.length(); i++) {
		j = i;
		// If // is found, break and we're done
		if (s[j] == '/' && s[++j] == '/') {
			break;

		}
		// If there are texts before //, gotta save them
		else {
			str.push_back(s[i]);
		}
	}
	return str;
}





int main() {
	// Store a text line from file when read
	string a;
	char token[] = { '{', '}', '(', ')', '+','-','/','*','%',';','=',',',':', };

	
	// Open a file and read from it
	ifstream input("file2.txt", std::ios_base::in);
	ofstream output("output.txt", std::ios_base::out);
	if (input.fail()) {
		cout << "Cannot open file" << endl;
		return 0;
	}
	
	// Read in text in the file line by line into a string
	while (getline(input, a)) {
		a = RemoveSpaces(AddSpace(RemoveComment(a), token));
		//check for empty line
		if (a == "") {
			continue;
		}

		output << a << endl;

	}

	return 0;
}
