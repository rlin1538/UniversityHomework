#include "common_header.h"
#define bufsize 300
using namespace std;
char str[bufsize];
int main() {
	cout << "请输入文法:" << endl;
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
	cout << "#######测试#######" << endl;
	while (true) {
		cout << "请输入一个句子：(退出请输入 quit）" << endl;
		cin >> str;
		if (strcmp("quit", str) == 0)
			break;
		analyze(str);
	}

}