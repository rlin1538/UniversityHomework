#include "common_header.h"
using namespace std;

//����ʽ������飨�������������ӡ�������ݹ飩
string grammar[maxnum];
//��ʼ����, Ĭ�ϵ�һ���ķ��ĵ�һ����ĸΪ��ʼ����
char start_char;
//���ս�� �� �ս�� ������, ����ʽ����
int cnt_nonT = 0;
int cnt_term = 0;
int lines = 0;
//���еķ��ս��
vector<char> nonT;
//���е��ս��
vector<char> term;
//ÿһ������ʽ�� first ���ϣ�ע�� '$' '@',first ���� $, follow ���� @
vector<char> firstP[maxnum];
//ÿһ�����ս���� first ����
vector<char> firstN[maxnum];
//ÿһ�����ս���� follow ����
vector<char> follow[maxnum];
//��ά���飬Ԥ���������Ų���ʽ�����±꣬û�еĵط�����Ϊ -1
int table[maxnum][maxnum];

//��ѯ �ַ� x ��ĳ�� vector<char> �е��±꣬û���򷵻� -1
//Ҫ�� vector<char> ��û���ظ���Ԫ��
int indexOf(const vector<char>& v, char x) {
	vector<char>::const_iterator it = find(v.begin(), v.end(), x);
	return it == v.end() ? -1 : it - v.begin();
}
// ��vector�����Ԫ�أ�����Ѿ����������
void add_unique_item(vector<char>& v, char c) {
	if (indexOf(v, c) == -1)
		v.push_back(c);
}

//��ѯ �ַ� x ���ս�����Ƿ��ս��
//����ֵ�� 1 ��ʾ�ս����0 ��ʾ���ս����-1��ʾ�����ˣ��ĸ�������
int typeOf(char x) {
	if (indexOf(nonT, x) != -1)
		return NonTerminator;
	if (indexOf(term, x) != -1)
		return Terminator;
	return -1;
}

//��ѯ �ַ� x �� nonT ���±�
int indexOfNonT(char x) {
	return indexOf(nonT, x);
}
//��ѯ �ַ� x �� term ���±�
int indexOfTerm(char x) {
	return indexOf(term, x);
}



