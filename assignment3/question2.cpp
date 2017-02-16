#include <iostream>
using std::cin;
using std::cout;
using std::endl;

#include <string>
using std::string;

#include <fstream>
using std::ifstream;

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
	string a = "aacab$";
	string w1;
	string w2;
	ifstream input("data.txt", std::ios_base::in);
	if (input.good()) {
		input >> w1;
		input >> w2;
	}
	else {
		cout << "Cannot open Data.txt file" << endl;
		return 0;
	}

	
	//5 states 2 inputs per state
	int table[5][2] = { {1,2} , {1,3}, {4,2} , {4,4} , {4,4} };

	checkWord(w1, table);
	cout << endl;
	checkWord(w2, table);
	cout << endl;

	return 0;
}
