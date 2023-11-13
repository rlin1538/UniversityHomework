#include "common_header.h"
using namespace std;
//����ʽ������飨�������������ӡ�������ݹ飩
extern string grammar[maxnum];
//��ʼ����, Ĭ�ϵ�һ���ķ��ĵ�һ����ĸΪ��ʼ����
extern char start_char; 
//���ս�� �� �ս�� ������, ����ʽ����
extern int cnt_nonT;
extern int cnt_term;
extern int lines; 
//���еķ��ս��
extern vector<char> nonT;
//���е��ս��
extern vector<char> term;

//ֱ�Ӵӱ�׼�����ȡ �ķ�
//��ʽ�������棬ÿ���ķ��ڲ�û�пո� 
/**
A->aBc
A->d+
B->cA
B->@
*/
void input_grammer() {
	lines = 0;
	while (cin >> grammar[lines])
		lines++;
	cin.clear();
}
// ��ȡ���ս�� �� �ս��, ���浽 nonT �� term ��
void pick_up() {
	bool vis[256] = {0};
	for (int i = 0;i < lines;i++) {
		char cur = grammar[i][0];
		if (!vis[(int)cur]) {
			nonT.push_back(cur);
			vis[(int)cur] = true;
		}
	}
	// ���Ƿ��ս���Ķ����ս��
	for (int i = 0;i < lines;i++) {
		int n = grammar[i].length();
		for (int j = 3;j < n;j++) {
			char cur = grammar[i][j];
			if (!vis[(int)cur]) {
				term.push_back(cur);
				vis[(int)cur] = true;
			}
		}
	}
	term.push_back('$');
	cnt_nonT = nonT.size();
	cnt_term = term.size();
	start_char = grammar[0][0];
}