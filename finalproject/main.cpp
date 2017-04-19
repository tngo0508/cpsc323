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

#include <stack>
#include <algorithm>
using namespace std;
bool isOperand(char& a) {
	return (isalnum(a) || a == '_');
}

// Add space before and after each token
void addSpaceToken(string & str)
{
	int i = 1;
	while (i < str.length())
	{
		// if we found an operator, excluding '.' since 
		// "END." does not have space in between
		if (!isOperand(str[i]) && str[i] != '.')
		{
			// we insert space before and after it
			str.insert(i, " ");
			str.insert(i + 2, " ");
			i += 2;
		}
		++i;
	}
}


string RemoveSpaces(string& s) {
	string str = "";
	string str2 = "";
	// Remove leading whitespaces
	auto bpos = s.find_first_not_of(" \t");
	auto epos = s.find_last_not_of(" \t");

	// Empty line if cant find the first character that is not a space
	if (bpos == s.npos) {
		return "";
	}
	
	str += s.substr(bpos, epos - bpos + 1);
	/*
	for (int i = 0; i < str.length(); i++) {
		if (!isOperand(str[i])) {
			str.insert(i, " ");
		}
	}
	*/
	// String with no leading or trailing whitespaces
	for (int i = 0, j = 0; i < str.length(); i++) {
		j = i;
		if (str[i] == ' ' && str[++j] == ' ') {
			continue;
		}
		str2 += str[i];
	}
	



	return str2;
}

bool bothAreSpaces(char lhs, char rhs)
{
	return ((lhs == rhs) && ((lhs == ' ') || (lhs == '\t')))
		|| ((lhs == '\t') && (rhs == ' '))
		|| ((lhs == ' ') && (rhs == '\t'));
}

void removeExtraSpaces(string &str)
{
	// remove leading blank spaces
	size_t p = str.find_first_not_of(" \t");
	str.erase(0, p);

	// remove extra blank spaces inside the string
	string::iterator i = unique(str.begin(), str.end(), bothAreSpaces);
	str.erase(i, str.end());
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
	string b = "";
	char token[] = { '{', '}', '(', ')', '+','-','/','*','%',';','=',',',':', };
	stack<char> myStack;

	// Open a file and read from it
	ifstream input("file.txt", std::ios_base::in);
	ofstream output("output.txt", std::ios_base::out);
	if (input.fail()) {
		cout << "Cannot open file" << endl;
		return 0;
	}

	// Read in text in the file line by line into a string
	int j = 0;
	bool bComment = false;

	while (getline(input, a)) {
		b = "";


		for (int i = 0; i < a.length(); i++) {
			j = i;
			if (a[i] == '/' && a[++j] == '/') {
				bComment = !bComment;
				i++;
				continue;
			}
			if (bComment == true) {
				continue;
			}
			b += a[i];
		}
		bool eol;
		auto bpos = b.find_first_not_of(" \t");
		auto epos = b.find_last_not_of(" \t");
		(epos == b.npos) ? eol = true : eol = false;
		addSpaceToken(a);
		removeExtraSpaces(a);
		//check for empty line
		if (b == "") {
			continue;
		}




		cout << b << endl;


	}

	return 0;
}
