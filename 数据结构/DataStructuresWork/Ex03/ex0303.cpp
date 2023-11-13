#include <iostream>
#define STACKINITSIZE 256
#define STACKINCREMENT 128
#define OK 1
#define OVERFLOW 0
#define ERROR 0
using namespace std;
int N;
int ans;

struct Point
{
    int col;
    int row;
};

struct SeqStack
{
    Point *pBase;
    Point *pTop;
    int stacksize; //ջ�ѷ���Ŀռ�
} StkQueen;
//��ʼ�������ټ���ղ���
int InitStack(SeqStack &S)
{
    S.pBase = new Point[STACKINITSIZE];
    if (S.pBase == NULL)
        exit(OVERFLOW);
    S.pTop = S.pBase;
    S.stacksize = STACKINITSIZE;
    return OK;
}
int DestroyStack(SeqStack &S)
{
    if (S.pBase != NULL)
    {
        delete[] S.pBase;
        S.pBase = NULL;
    }
    S.pTop = NULL;
    S.stacksize = 0;
    return OK;
}
int ClearStack(SeqStack &S)
{
    S.pTop = S.pBase;
    return OK;
}
//�ӹ��Ͳ���
int Push(SeqStack &S, Point e)
{
    Point *temp;
    if (S.pBase)
    {
        if (S.pTop - S.pBase >= S.stacksize) //ջ���˶�̬���ӿռ�
        {
            temp = new Point[S.stacksize + STACKINCREMENT];
            if (temp == NULL)
                exit(OVERFLOW);
            for (int j = 0; (S.pBase + j) < S.pTop; j++)
                *(temp + j) = *(S.pBase + j);
            delete[] S.pBase;
            S.pBase = temp;
            S.pTop = S.pBase + S.stacksize;
            S.stacksize += STACKINCREMENT;
        }
        *S.pTop = e;
        S.pTop++;
    }
    return OK;
}
int Pop(SeqStack &S, Point &e)
{
    if (S.pBase && S.pBase != S.pTop)
    {
        e = *(S.pTop - 1);
        S.pTop--;
        return OK;
    }
    return ERROR;
}

bool Judge(Point newQueen,SeqStack SktQueen)
{
    Point *p;
    p = StkQueen.pBase;
    while (p<StkQueen.pTop-1)
    {
        if (p->col == newQueen.col) return false;
        if (abs(p->col-newQueen.col)==(abs(p->row-newQueen.row)))
            return false;
        p++;
    }
    return true;
}
void OutputResult(SeqStack StkQueen)
{
    cout<<"��" <<ans<<"�ְڷ���"<<endl;
    for (int i=0;i<N;i++)
    {
        for (int j=0;j<N;j++)
        {
            if (StkQueen.pBase[i].col == j)
            {
                cout<<'Q'<<' ';
            }
            else
            {
                cout<<'#'<<' ';
            }
        }
        cout<<endl;
    }
    cout<<endl;
}

int PlaceQueen(int row)
{
    Point curQueen;
    for (int col=0;col<N;col++) //ѭ����
    {
        curQueen.col = col;
        curQueen.row = row;
        Push(StkQueen,curQueen);    //��ǰ����ջ
        if (Judge(curQueen,StkQueen))   //���������ջ
        {
            if (row<N-1)            //����������һ��
            {
                PlaceQueen(row+1);  //�ݹ���һ��
            }
            else                    //����Ϊ���һ�У���ô������
            {
                ans++;
                OutputResult(StkQueen);
            }
            
        }
        Pop(StkQueen,curQueen); //��ǰ���ջ��ѭ��������һ��
    }
    return 1;
}

int main()
{
    cout<<"����N:";
    cin>>N;
    InitStack(StkQueen);
    PlaceQueen(0);
    cout<<"����"<<ans<<"�ְڷ�";
}