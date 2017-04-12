#include <iostream>
#include <stack>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <iomanip>

using namespace std;

const int ROW = 17;
const int COL = 12;
stack<string> myStack;
string grandma[8] = {"E6", "E6", "E2", "T6", "T6", "T2", "F6", "F2"};

// Prints stack without removing items
void printStack(stack<string>& myStack)
{
	if (myStack.empty())
		cout << "Stack is empty.";
	else
	{
		int size = myStack.size();
		string * arr = new string[size + 1];
		cout << "Stack is: ";
		for (int i = 0; i < size; ++i)
		{
			arr[i] = myStack.top();
			myStack.pop();
		}
		for (int i = size - 1; i >= 0; --i)
		{
			myStack.push(arr[i]);
			cout << arr[i];
		}
		delete[] arr;
	}
	cout << endl;
}


void Process_s(string b, string c, string s, stack<string>& st) {
	st.push(b);
	st.push(c);
	st.push(s);
}

void Process_r(string b, string c, string s, stack<string>& st) {
	st.push(b);
	int num = stoi(s);
	int num2 = stoi(grandma[num - 1].substr(1,1));
	for (int i = 0; i < num2; i++) {
		st.pop();
	}
	string e = st.top();
	st.pop();

	grandma[num - 1].substr(0, 1);

	

}

void Process_num(string b, string c, string s, stack<string>& st) {

}

void findInTable(const string& rowVal, const string& colVal, const string parsing_table[ROW][COL])
{
	int i = 0, j = 0;
	for (; i < ROW; i++)
	{
		if (parsing_table[i][0] == rowVal)
		{
			for (;j < COL;j++)
			{
				if (parsing_table[0][j] == colVal) {
					string d = parsing_table[i][j];
					if (d[0] == 's') {
						Process_s(rowVal, colVal, d.substr(1, 1), myStack);
					}
					else if (d[0] == 'r') {
						Process_r(rowVal, colVal, d.substr(1, 1), myStack);
					}
					else {
						Process_num(rowVal, colVal, d, myStack);
					}
				}
			}
		}
	}

}

int main() {

	string exp = "(i+i)*i$";
	//cout << "Enter the expression:";
	//cin >> exp;
	ifstream input;
	input.open("parsing_table.txt", ios_base::in);
	if (!input) {
		cout << "Cannot open file";
		return 0;
	}
	
	string a;
	string parsing_table[ROW][COL];
	for (int i = 0; i < ROW; i++) {
		for (int j = 0; j < COL; j++) {
			input >> a;
			parsing_table[i][j] = a;
		}
	}

	cout << "Printing out the table" << endl;
	
	for (int i = 0; i < 17; i++) {
		for (int j = 0; j < 12; j++) {
			cout << setw(8) << parsing_table[i][j] << " ";
		}
		cout << endl;
	}


	string b;
	string c;
	myStack.push("0");
	b = myStack.top();
	myStack.pop();

	for (int i = 0; i < exp.length(); i++) {
		c = exp[i];
		findInTable(b, c, parsing_table);
		printStack(myStack);
	}



	return 0;
}
