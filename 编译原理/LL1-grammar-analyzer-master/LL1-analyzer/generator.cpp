#include "common_header.h"
using namespace std;

//����ʽ������飨�������������ӡ�������ݹ飩
extern string grammar[maxnum];
//����ʽ����
extern int lines;
//ÿһ������ʽ�� first ���ϣ�ע�� '$' '@'
extern vector<char> firstP[maxnum];

//ÿһ�����ս���� follow ���ϣ�ע�� '$'
extern vector<char> follow[maxnum];

//��ά���飬Ԥ���������Ų���ʽ�����±꣬û�еĵط�����Ϊ -1
extern int table[maxnum][maxnum];

//����Ԥ�������
void generateTable() {
	memset(table, -1, sizeof table);
	for (int k = 0; k < lines;k++) {
		bool hasEmpty = false; // ��� firstP[k] ���Ƿ� ���� '@'
		int i = indexOfNonT(grammar[k][0]); // �� k ������ʽ�� ��ͷ���ս�� �� nonT ���±�
		for (char c : firstP[k]) {
			if (c == '@') { // �������в������ @ ��һ�У���Ϊ�ò���
				hasEmpty = true;
			}
			else {
				int j = indexOfTerm(c);
				table[i][j] = k; // ������ʽ �� grammar �е��±� �����������
			}
		}
		// ����� ���ա�����ô��Ҫ ���� follow[i] �е�ÿ���ս��
		if (hasEmpty) {
			for (char c : follow[i]) { // ע��follow �в����ܺ��� '@'
				int j = indexOfTerm(c);
				table[i][j] = k; // ������ʽ �� grammar �е��±� �����������
			}
		}
	}
}

