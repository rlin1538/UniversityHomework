#include "common_header.h"
using namespace std;
//����ʽ������飨�������������ӡ�������ݹ飩
extern string grammar[maxnum];
//��ʼ����, Ĭ�ϵ�һ���ķ��ĵ�һ����ĸΪ��ʼ����
extern char start_char;
extern int cnt_nonT;
extern int lines;
//���еķ��ս��
extern vector<char> nonT;
//���е��ս��
extern vector<char> term;
//ÿһ������ʽ�� first ���ϣ�ע�� '$' '@'
extern vector<char> firstP[maxnum];
//ÿһ�����ս���� first ���ϣ�ע�� '$' '@'
extern vector<char> firstN[maxnum];
//ÿһ�����ս���� follow ���ϣ�ע�� '$' '@'
extern vector<char> follow[maxnum];

typedef pair<int, int> Pair2;
vector<Pair2> to_do;
//���½�get_follow.cpp��ʹ��
vector<char> firstbeta(int i, int pos)
{
	vector<char> res;
	bool keep = true; // �Ƿ���������
	for (char c : grammar[i].substr(pos)) {
		if (!keep)
			break;
		if (typeOf(c) == Terminator) {
			add_unique_item(res, c);
			keep = false;
		}
		else { // ���ս��
			   //��������ս���� first ����
			keep = false;
			for (char b : firstN[indexOfNonT(c)]) {
				if (b == '@')
					keep = true;
				else
					add_unique_item(res, b);
			}
		}
	}
	// ������ keep ��Ϊ true, ��˵�� ����ʽ �Ҳ��ɿ�
	if (keep)
		add_unique_item(res, '@');
	return res;
}
//�󵥸�Ԫ�ص� FOLLOW ��
void singleFollow(char ch, vector<char> &inner_follow)
{
	int index_ch = indexOfNonT(ch);
	for (int k = 0;k < lines;k++) {
		string& cur_grammar = grammar[k];
		int index_head = indexOfNonT(cur_grammar[0]);
		int len = cur_grammar.length();
		for (int i = 3; i < len; i++)//����Ϊ��ǰ����ʽ�Ҳ�Ԫ�س���
		{
			if (cur_grammar[i] != ch)
				continue;
			auto next_follow = firstbeta(k, i + 1);
			bool hasat = false;
			for (auto d : next_follow) {
				if (d == '@') 
					hasat = true;
				else 
					add_unique_item(inner_follow, d);
			}
			if (hasat && index_head != index_ch)
				to_do.push_back(make_pair(index_head, index_ch));
		}
	}
}
//��� follow
int old_follow_size[maxnum];
bool isSameSize() {
	for (int i = 0;i < cnt_nonT;i++) {
		if (old_follow_size[i] != follow[i].size())
			return false;
	}
	return true;
}
void copy_from_to(vector<char>& from, vector<char>& to) {
	for (char c : from) {
		add_unique_item(to, c);
	}
}
void getFollow()
{
	follow[indexOfNonT(start_char)].push_back('$');
	to_do.clear();
	for (int i = 0;i < cnt_nonT;i++) {
		singleFollow(nonT[i], follow[i]);
	}
	do {
		for (int i = 0;i < cnt_nonT;i++) {
			old_follow_size[i] = follow[i].size();
		}
		for (auto p : to_do) {
			copy_from_to(follow[p.first], follow[p.second]);
		}
	} while (!isSameSize()); //ֻҪ��һ�£����ظ�
}