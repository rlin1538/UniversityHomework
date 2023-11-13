//2.迷宫问题
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
    int stacksize; //栈已分配的空间
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
            if (pTop - pBase >= stacksize) //栈满了动态增加空间
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
    int tx, ty; //下一个点坐标
    int next[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
    int flag[N][N] = {0}; //标记已走过的点
    bool temp;            //标记某次有路可走

    way.InitStack();
    way.Push(a.x, a.y);
    flag[a.x][a.y] = 1;

    while (!way.IsEmpty()) //栈不为空继续循环
    {
        way.GetTop(cur); //获取栈顶元素
        temp = false;
        for (int i = 0; i < 4; i++) //尝试走四个方向
        {
            tx = cur.x + next[i][0];
            ty = cur.y + next[i][1];
            if (tx < 0 || tx >= n || ty < 0 || ty >= m || M[tx][ty] == 1) //判断不可走的点
                continue;
            if (flag[tx][ty] == 0) //如果没走过
            {
                flag[tx][ty] = 1; //标记该点走过
                way.Push(tx, ty); //入栈
                temp = true;      //标记有路
                break;
            }
        }
        if (temp == false) //没路走了，出栈
        {
            if ((cur.x == b.x && cur.y == b.y)) //如果是终点，输出(cur.x != a.x && cur.y != a.y) &&
            {
                way.Print(M);
                return;
            }
            way.Pop();
        }
    }
    cout << "未找到通路" << endl;
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
    cout << "输入起点位置(空格为间隔)：";
    cin >> pbegin.x >> pbegin.y;
    cout << "输入终点位置(空格为间隔)：";
    cin >> pend.x >> pend.y;
    FindWay(pbegin, map, pend);
}
