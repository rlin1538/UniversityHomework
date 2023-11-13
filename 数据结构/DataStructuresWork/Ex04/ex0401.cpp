#include <iostream>
#define MAXSIZE 256
using namespace std;

struct Triple
{
    int i, j; //数据所在行、列
    int v;    //数据元素值
};

struct SqMatrix
{
    Triple arr[MAXSIZE];
    int Rows, Cols, Nums; //行、列，非零元素个数
};

void CreatSMatrix(int m, int n, int M[MAXSIZE][MAXSIZE], SqMatrix &A) //由矩阵建立三元组
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

void TransposeSMatrix(SqMatrix A, SqMatrix &B) //列序遍历转置
{
    int c = 0; //计数变量
    B.Cols = A.Rows;
    B.Rows = A.Cols;
    B.Nums = A.Nums;
    if (A.Nums > 0) //当三元组A中有元素
    {
        for (int k = 0; k < A.Cols; k++) //循环A的列
        {
            for (int l = 0; l < A.Nums; l++) //循环三元组A，找出列号为k的
            {
                if (A.arr[l].j == k) //列号为k
                {
                    B.arr[c].i = A.arr[l].j; //转移至B
                    B.arr[c].j = A.arr[l].i;
                    B.arr[c].v = A.arr[l].v;
                    c++;
                }
            }
        }
    }
}

void FastTransposeSMatrix(SqMatrix A, SqMatrix &B) //快速转置
{
    int l; //放置A中某个三元组的列，以便找到B中合适的位置
    B.Cols = A.Rows;
    B.Rows = A.Cols;
    B.Nums = A.Nums;
    int rowNum[MAXSIZE] = {0};   //记录A中每列的非零元素个数
    int rowStart[MAXSIZE] = {0}; //由A得出的B中三元组存放的起始位置

    if (A.Nums) //如果A三元组中有元素
    {
        for (int i = 0; i < A.Nums; i++) //记录矩阵A中每列非零元个数
            rowNum[A.arr[i].j]++;
        rowStart[0] = 0;                 //第一列起始位置为0
        for (int i = 1; i < A.Cols; i++) //计算B中每个三元组存放起始位置
            rowStart[i] = rowStart[i - 1] + rowNum[i - 1];
        for (int k = 0; k < A.Nums; k++) //遍历A，转置结果到B
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
    cout << "行" << '\t' << "列" << '\t' << "值" << endl;
    for (int i = 0; i < A.Nums; i++)
        cout << A.arr[i].i << '\t' << A.arr[i].j << '\t' << A.arr[i].v << endl;
    cout << endl;
}

int main()
{
    int Mt[MAXSIZE][MAXSIZE]; //矩阵
    SqMatrix A, B, C;         //三元组表
    int m, n;                 //m行n列

    cout << "输入行、列：";
    cin >> m >> n;
    cout << "输入稀疏矩阵" << endl;
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            cin >> Mt[i][j];
    CreatSMatrix(m, n, Mt, A);
    cout << "转置前三元组为：" << endl;
    OutputSMatrix(A);
    TransposeSMatrix(A, B);
    cout << "列序转置后三元组为：" << endl;
    OutputSMatrix(B);
    FastTransposeSMatrix(A, C);
    cout << "快速转置后三元组为：" << endl;
    OutputSMatrix(C);
}