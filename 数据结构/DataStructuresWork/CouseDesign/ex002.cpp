//2.�Թ�����
#include <iostream>
#include <iomanip>
#include <fstream>
#define N 100
#define STACKINITSIZE 512
#define STACKINCREMENT 128
using namespace std;

struct Point
{
    int x;
    int y;
    //bool flag;
};

int n, m;
class Stack
{
    Point *pBase;
    Point *pTop;
    int stacksize; //ջ�ѷ���Ŀռ�
public:
    void InitStack()
    {
        pBase = new Point[STACKINITSIZE];
        pTop = pBase;
        stacksize = STACKINITSIZE;
    }
    bool IsEmpty()
    {
        if (pBase)
        {
            if (pBase == pTop)
                return true;
            else
                return false;
        }
        return true;
    }
    void GetTop(Point &e)
    {
        if (pBase && (pBase != pTop))
        {
            e.x = (pTop - 1)->x;
            e.y = (pTop - 1)->y;
        }
    }
    void Pop()
    {
        if (pBase && pBase != pTop)
            pTop--;
    }
    void Push(int a, int b)
    {
        Point *temp;
        if (pBase)
        {
            if (pTop - pBase >= stacksize) //ջ���˶�̬���ӿռ�
            {
                temp = new Point[stacksize + STACKINCREMENT];
                for (int j = 0; (pBase + j) < pTop; j++)
                    *(temp + j) = *(pBase + j);
                delete[] pBase;
                pBase = temp;
                pTop = pBase + stacksize;
                stacksize += STACKINCREMENT;
            }
            pTop->x = a;
            pTop->y = b;
            pTop++;
        }
    }
    void Print(int M[N][N])
    {
        int i = 0;
        char map[N][N];
        for (int j = 0; j < n; j++)
            for (int k = 0; k < m; k++)
            {
                if (M[j][k])
                    map[j][k] = '#';
                else
                    map[j][k] = ' ';
            }

        if (pBase)
            while ((pBase + i) < pTop)
            {
                map[(pBase + i)->x][(pBase + i)->y] = '@';
                i++;
            }
        cout << endl
             << "-------------------------------------------------" << endl;
        for (int j = 0; j < n; j++)
        {
            for (int k = 0; k < m; k++)
                cout << map[j][k] << ' ';
            cout << endl;
        }
    }
};

void FindWay(Point a, int M[N][N], Point b)
{
    Stack way;
    Point cur;
    int tx, ty; //��һ��������
    int next[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
    int flag[N][N] = {0}; //������߹��ĵ�
    bool temp;            //���ĳ����·����

    way.InitStack();
    way.Push(a.x, a.y);
    flag[a.x][a.y] = 1;

    while (!way.IsEmpty()) //ջ��Ϊ�ռ���ѭ��
    {
        way.GetTop(cur); //��ȡջ��Ԫ��
        temp = false;
        for (int i = 0; i < 4; i++) //�������ĸ�����
        {
            tx = cur.x + next[i][0];
            ty = cur.y + next[i][1];
            if (tx < 0 || tx >= n || ty < 0 || ty >= m || M[tx][ty] == 1) //�жϲ����ߵĵ�
                continue;
            if (flag[tx][ty] == 0) //���û�߹�
            {
                flag[tx][ty] = 1; //��Ǹõ��߹�
                way.Push(tx, ty); //��ջ
                temp = true;      //�����·
                break;
            }
        }
        if (temp == false) //û·���ˣ���ջ
        {
            if ((cur.x == b.x && cur.y == b.y)) //������յ㣬���(cur.x != a.x && cur.y != a.y) &&
            {
                way.Print(M);
                return;
            }
            way.Pop();
        }
    }
    cout << "δ�ҵ�ͨ·" << endl;
}

int main()
{
    ifstream fin("Maze.txt");
    int map[N][N];
    Point pbegin, pend;

    fin >> n >> m;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
            fin >> map[i][j];
    }
    for (int i = -1; i < n; i++)
    {
        if (i > -1)
            cout << setw(2) << i;
        for (int j = -1; j < m; j++)
        {
            if (i == -1)
                cout << setw(2) << j;
            else if (map[i][j] == 1)
                cout << "# ";
            else
                cout << "  ";
        }

        cout << endl;
    }
    cout << "�������λ��(�ո�Ϊ���)��";
    cin >> pbegin.x >> pbegin.y;
    cout << "�����յ�λ��(�ո�Ϊ���)��";
    cin >> pend.x >> pend.y;
    FindWay(pbegin, map, pend);
}
