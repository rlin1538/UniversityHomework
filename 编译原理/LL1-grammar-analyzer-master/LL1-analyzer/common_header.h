#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <map>
#include <stack>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <string>
#include <queue>
#include <set>
#include <cassert>
#include <iomanip>
#include <ctime>
#include <list>
#include <cctype>
#include <functional>
#define maxnum 50
#define Terminator 1
#define NonTerminator 0
// �����
#define Table_width 20
using namespace std;

//��ѯ �ַ� x �� nonT ���±�
int indexOfNonT(char x);

//��ѯ �ַ� x �� term ���±�
int indexOfTerm(char x);

//��ѯ �ַ� x ��ĳ�� vector<char> �е��±꣬û���򷵻� -1
//Ҫ�� vector<char> ��û���ظ���Ԫ��
int indexOf(const vector<char>& v, char x);

// ��vector�����Ԫ�أ�����Ѿ����������
void add_unique_item(vector<char>& f, char c);

//��ѯ �ַ� x ���ս�����Ƿ��ս��
//����ֵ�� 1 ��ʾ�ս����0 ��ʾ���ս����-1��ʾ�����ˣ��ĸ�������
int typeOf(char x);

// ��������
// ����ɹ���������� ��������
void analyze(const char* str, int len = -1);
//�����ķ�
void input_grammer();
// ��ȡ���ս�� �� �ս��, ���浽 nonT �� term ��
void pick_up();
//firstN()���ս����first
void getFirstN();
//firstP()����ʽ��first
void getFirstP();
//���follow
void getFollow();
//����Ԥ�������
void generateTable();


// ��ӡ
void printAllTerminator();
void printAllNonTerminator();
void printAllFirstN();
void printAllFirstP();
void printAllFollow();
void printTable();

