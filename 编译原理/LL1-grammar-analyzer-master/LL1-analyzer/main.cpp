#include "common_header.h"
#define bufsize 300
using namespace std;
char str[bufsize];
int main() {
	cout << "�������ķ�:" << endl;
	input_grammer();
	pick_up();
	getFirstN();
	getFirstP();
	getFollow();
	generateTable();
	printAllTerminator();
	printAllNonTerminator();
	printAllFirstN();
	//printAllFirstP();
	printAllFollow();
	printTable();
	cout << "#######����#######" << endl;
	while (true) {
		cout << "������һ�����ӣ�(�˳������� quit��" << endl;
		cin >> str;
		if (strcmp("quit", str) == 0)
			break;
		analyze(str);
	}

}