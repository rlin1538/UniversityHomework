#include "common_header.h"
using namespace std;
//����ʽ������飨�������������ӡ�������ݹ飩
extern string grammar[maxnum];
extern int lines;
//���еķ��ս��
extern vector<char> nonT;
//ÿһ������ʽ�� first ���ϣ�ע�� '$' '@'
extern vector<char> firstP[maxnum];
//ÿһ�����ս���� first ���ϣ�ע�� '$' '@'
extern vector<char> firstN[maxnum];
//���� ���ս�� �� first ��
void getfirst(char NonTer)
{
	int index_NonTer = indexOfNonT(NonTer);
	for (int j = 0;j < lines;j++) //��������ʽ 
	{
		if (grammar[j][0] != NonTer)
			continue;
		bool keep = true;// �Ƿ���������
		for (char c : grammar[j].substr(3)) {
			if (!keep)
				break;
			if (typeOf(c) == Terminator) {
				add_unique_item(firstN[index_NonTer], c);
				keep = false;
			}
			else { // ���ս��
				//��������ս���� first ����
				keep = false;
				getfirst(c); // ��֮ǰ�ȵݹ����һ��
				for (char b : firstN[indexOfNonT(c)]) {
					if (b == '@')
						keep = true;
					else
						add_unique_item(firstN[index_NonTer], b);
				}
			}
		}
		// ������ keep ��Ϊ true, ��˵�� �Ҳ��ɿ�
		if (keep)
			add_unique_item(firstN[index_NonTer], '@');
	}
}
//��������ս����first�� 
void getFirstN()
{
	for_each(nonT.begin(), nonT.end(), getfirst);
}
//������в���ʽ�Ҳ���first�� 
void getFirstP()
{
	for (int i = 0;i < lines;i++) {
		bool keep = true; // �Ƿ���������
		for (char c : grammar[i].substr(3)) {
			if (!keep)
				break;
			if (typeOf(c) == Terminator) {
				add_unique_item(firstP[i], c);
				keep = false;
			}
			else { // ���ս��
				//��������ս���� first ����
				keep = false;
				for (char b : firstN[indexOfNonT(c)]) {
					if (b == '@')
						keep = true;
					else
						add_unique_item(firstP[i], b);
				}
			}
		}
		// ������ keep ��Ϊ true, ��˵�� ����ʽ �Ҳ��ɿ�
		if(keep)
			add_unique_item(firstP[i], '@');
	}
}