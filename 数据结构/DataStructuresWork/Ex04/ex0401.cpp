#include <iostream>
#define MAXSIZE 256
using namespace std;

struct Triple
{
    int i, j; //���������С���
    int v;    //����Ԫ��ֵ
};

struct SqMatrix
{
    Triple arr[MAXSIZE];
    int Rows, Cols, Nums; //�С��У�����Ԫ�ظ���
};

void CreatSMatrix(int m, int n, int M[MAXSIZE][MAXSIZE], SqMatrix &A) //�ɾ�������Ԫ��
{
    A.Cols = n;
    A.Rows = m;
    A.Nums = 0;
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (M[i][j])
            {
                A.arr[A.Nums].i = i;
                A.arr[A.Nums].j = j;
                A.arr[A.Nums].v = M[i][j];
                A.Nums++;
            }
        }
    }
}

void TransposeSMatrix(SqMatrix A, SqMatrix &B) //�������ת��
{
    int c = 0; //��������
    B.Cols = A.Rows;
    B.Rows = A.Cols;
    B.Nums = A.Nums;
    if (A.Nums > 0) //����Ԫ��A����Ԫ��
    {
        for (int k = 0; k < A.Cols; k++) //ѭ��A����
        {
            for (int l = 0; l < A.Nums; l++) //ѭ����Ԫ��A���ҳ��к�Ϊk��
            {
                if (A.arr[l].j == k) //�к�Ϊk
                {
                    B.arr[c].i = A.arr[l].j; //ת����B
                    B.arr[c].j = A.arr[l].i;
                    B.arr[c].v = A.arr[l].v;
                    c++;
                }
            }
        }
    }
}

void FastTransposeSMatrix(SqMatrix A, SqMatrix &B) //����ת��
{
    int l; //����A��ĳ����Ԫ����У��Ա��ҵ�B�к��ʵ�λ��
    B.Cols = A.Rows;
    B.Rows = A.Cols;
    B.Nums = A.Nums;
    int rowNum[MAXSIZE] = {0};   //��¼A��ÿ�еķ���Ԫ�ظ���
    int rowStart[MAXSIZE] = {0}; //��A�ó���B����Ԫ���ŵ���ʼλ��

    if (A.Nums) //���A��Ԫ������Ԫ��
    {
        for (int i = 0; i < A.Nums; i++) //��¼����A��ÿ�з���Ԫ����
            rowNum[A.arr[i].j]++;
        rowStart[0] = 0;                 //��һ����ʼλ��Ϊ0
        for (int i = 1; i < A.Cols; i++) //����B��ÿ����Ԫ������ʼλ��
            rowStart[i] = rowStart[i - 1] + rowNum[i - 1];
        for (int k = 0; k < A.Nums; k++) //����A��ת�ý����B
        {
            l = rowStart[A.arr[k].j];
            B.arr[l].i = A.arr[k].j;
            B.arr[l].j = A.arr[k].i;
            B.arr[l].v = A.arr[k].v;
            rowStart[A.arr[k].j]++;
        }
    }
}
void OutputSMatrix(SqMatrix A)
{
    cout << "��" << '\t' << "��" << '\t' << "ֵ" << endl;
    for (int i = 0; i < A.Nums; i++)
        cout << A.arr[i].i << '\t' << A.arr[i].j << '\t' << A.arr[i].v << endl;
    cout << endl;
}

int main()
{
    int Mt[MAXSIZE][MAXSIZE]; //����
    SqMatrix A, B, C;         //��Ԫ���
    int m, n;                 //m��n��

    cout << "�����С��У�";
    cin >> m >> n;
    cout << "����ϡ�����" << endl;
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            cin >> Mt[i][j];
    CreatSMatrix(m, n, Mt, A);
    cout << "ת��ǰ��Ԫ��Ϊ��" << endl;
    OutputSMatrix(A);
    TransposeSMatrix(A, B);
    cout << "����ת�ú���Ԫ��Ϊ��" << endl;
    OutputSMatrix(B);
    FastTransposeSMatrix(A, C);
    cout << "����ת�ú���Ԫ��Ϊ��" << endl;
    OutputSMatrix(C);
}