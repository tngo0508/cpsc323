#include <iostream>
using std::cin;
using std::cout;
using std::endl;

#include <string>
using std::string;
using std::getline;
using std::stoi;

#include <map>
using std::map;

#include <vector>
using std::vector;

#include <stack>
using std::stack;

int main() {
	string exp;		//store user input expression
	string temp;
	int value;
	int l, r, result = 0;
	stack<int> stack;
	map<string, int> map;
	cout << "Enter an expression: ";
	getline(cin, exp);

	for (int i = 0; i < exp.length(); i++) {
		if (exp[i] == '+' || exp[i] == '-' || exp[i] == '*' || exp[i] == '/') {
			//found an operator
			r = stack.top();
			stack.pop();
			l = stack.top();
			stack.pop();

			switch (exp[i]) {
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
			//Not an expression
			if (exp[i] != ' ') {
				temp.push_back(exp[i]);
				continue;
			}
			//if temp is empty (whitespace after operator was detected), move on to next character
			if (temp.empty()) {
				continue;
			}

			//Check if word exists and already assigned value
			if (map.count(temp) < 1) {
				//If first character is a number, then whatever inside temp will be a number
				if (isdigit(temp[0])) {
					value = stoi(temp);
					map.insert(std::make_pair(temp, value));
				}
				else {
					cout << "Enter value for " << temp << " : ";
					cin >> value;
					cin.ignore(256, '\n');
					map.insert(std::make_pair(temp, value));
				}
			}
			for (auto it = map.begin(); it != map.end(); it++) {
				if (it->first == temp) {
					stack.push(it->second);
				}
			}
			temp.clear();
		}
	}

	cout << "ANSWER: " << stack.top() << endl;

	return 0;
}
