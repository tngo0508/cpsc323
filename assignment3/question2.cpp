#include <iostream>
using std::cin;
using std::cout;
using std::endl;

#include <string>
using std::string;

void checkWord(string& w, int table[][2]) {
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

		default:
			cout << "No information on input " << w[i] << endl;
			state = 4;
			exit = true;
			break;
		}

		state = table[state][input];

		if (exit == true) {
			break;
		}
		i++;


	}

	if (state == 4) {
		cout << w << " is not accepted" << endl;
	}
	else {
		cout << w << " is accepted" << endl;
	}
}

int main() {
	string w1 = "aaab$";
	string w2 = "bcbbca$";

	//5 states 2 inputs per state
	int table[5][2] = { {1,2} , {1,3}, {4,2} , {4,4} , {4,4} };

	checkWord(w2, table);

	return 0;
}
