#include <iostream>
using namespace std;

bool judge(int M[15][10], int A[4][4], int k, int d) //�жϰ��A�ڵ�k���½�d�к��Ƿ��ܷ���
{
    for (int i = d; i < d + 4; i++)
        for (int j = k - 1; j < k + 3; j++)
            if (A[i - d][j - k + 1])
                if (M[i][j])
                    return false;
    return true;
}

int main()
{
    int M[16][10]; //����ͼ
    int A[4][4];   //���
    int k;         //�����λ��
    int c = 1;     //�����½�����

    for (int i = 0; i < 15; i++) //���뷽��ͼ
        for (int j = 0; j < 10; j++)
            cin >> M[i][j];
    for (int i = 0; i < 10; i++) //������ͼ�ײ�����
        M[15][i] = 1;
    for (int i = 0; i < 4; i++) //������
        for (int j = 0; j < 4; j++)
            cin >> A[i][j];
    cin >> k;                 //��������λ��
    while (judge(M, A, k, c)) //ģ������������ж�
        c++;
    c--;
    for (int i = c; i < c + 4; i++) //���·���ͼ
        for (int j = k - 1; j < k + 3; j++)
            if (A[i - c][j - k + 1])
                M[i][j] = 1;
    for (int i = 0; i < 15; i++) //�������ͼ
    {
        for (int j = 0; j < 10; j++)
            cout << M[i][j] << " ";
        cout << endl;
    }
}