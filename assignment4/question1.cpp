/*
Nguyen, Hympert
Nguyen, Thao
*/

#include <iostream>
using std::cin;
using std::cout;
using std::endl;

#include <string>
using std::string;

void checkWord(string& w, int table[][3]) {
	bool exit = false;
	int i = 0;
	int state = 0, input;
	while (w[i] != '$') {
		switch (w[i]) {
		case 'a':
			input = 0;
			break;

		case 'b':
			input = 1;
			break;

		case 'c':
			input = 2;
			break;

		default:
			cout << "No information on input " << w[i] << endl;
			state = 2;
			exit = true;
			break;
		}

		state = table[state][input];

		if (exit == true) {
			break;
		}
		i++;


	}

	if (state == 0 || state == 2) {
		cout << w << " is not accepted" << endl;
	}
	else {
		cout << w << " is accepted" << endl;
	}
}

int main() {
	string w1 = "abbbcaaa$";
	string w2 = "ccccbbb$";
	string w3 = "aabbcbbb$";

	//4 states 3 inputs per state
	int table[5][3] = { {0,1,3}, {3,1,2}, {1,2,2}, {0,2,2} };
	checkWord(w1, table);
	checkWord(w2, table);
	checkWord(w3, table);

	return 0;
}
