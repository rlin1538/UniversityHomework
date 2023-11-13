//���ڽ�����TSP����
#include <iostream>
#include <fstream>
#define START 0        //��ʼ��
#define INFINITY 99999 //�Զ���һ�������
#define MAX_V 20       //��󶥵����
using namespace std;

int *TSP(int G[MAX_V][MAX_V], int n)
{
    int sum = 1;           //��������
    int ans = 0;           //���·��
    int flag[MAX_V] = {0}; //����������
    int *path;             //��¼·��
    int cur;               //��ǰ���ڵĵ�
    int temp;              //��ʱ����
    int min;               //��ǰ������̱�

    path = new int[n + 1];
    flag[START] = 1;
    cur = START;
    path[0] = START; //�ӵ�һ���������
    while (sum < n)  //ѭ��n-1�Σ��ҳ���·
    {
        min = INFINITY;
        for (int i = 0; i < n; i++)
            if (flag[i] == 0 && G[cur][i] < min) //�ҳ����뵱ǰ���������
            {
                temp = i; //��¼����ı�temp
                min = G[cur][i];
            }
        ans += min;         //�ۼ���̱�
        path[sum++] = temp; //��¼·��
        flag[temp] = 1;     //������߹�
        cur = temp;         //����ǰ�����
    }
    path[sum] = START; //�ص����
    ans += G[cur][START];
    cout << "���·��Ϊ��" << ans << endl;

    return path;
}

int main()
{
    int G[MAX_V][MAX_V];
    int *H;
    int n; //�������
    fstream M;

    M.open("matrix.txt"); //���ļ���ȡ����
    M >> n;
    for (int i = 0; i < n; i++) //�ڽӾ����ʼ��
        for (int j = 0; j < n; j++)
            M >> G[i][j];
    cout << "��ǰ�ڽӾ���Ϊ��" << endl;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            cout << G[i][j] << '\t';
        cout << endl;
    }

    H = new int[n + 1];
    H = TSP(G, n);
    cout << "·��Ϊ��";
    for (int i = 0; i < n; i++)
        cout << H[i] << "-->";
    cout << H[n] << endl;
}

/*
5
99999 5 12 5 5
5 99999 9 7 8
12 9 99999 9 16
5 7 9 99999 8
5 8 16 8 99999
*/