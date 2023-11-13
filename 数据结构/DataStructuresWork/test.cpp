#include <iostream>
#include <string>
#include <fstream>
#define OK 1
#define MAX_V 20
#define vexNum 5  //������
#define arcNum 10 //����
using namespace std;
#define MAX_V 20 //��󶥵���
/*
typedef struct
{
    int code;  //������
    char name; //��������
} vertexType;

typedef struct
{
    int arcs[MAX_V][MAX_V]; //�ڽӾ���
    int weight[vexNum][vexNum];
    vertexType vexs[MAX_V]; //������Ϣ
} mGraph;

//��������ͼ
void create_graph(mGraph &G)
{
    int i, j;
    for (i = 0; i < vexNum; i++)
    {
        G.vexs[i].code = i; //�����ų�ʼ��
    }
    G.vexs[0].name = 'A';
    G.vexs[1].name = 'B';
    G.vexs[2].name = 'C';
    G.vexs[3].name = 'D';
    G.vexs[4].name = 'E'; //�Զ������ı��
    G.weight[0][1] = 5;
    G.weight[1][0] = 5;
    G.weight[0][2] = 12;
    G.weight[2][0] = 12;
    G.weight[0][3] = 5;
    G.weight[3][0] = 5;
    G.weight[0][4] = 5;
    G.weight[4][0] = 5;
    G.weight[1][2] = 9;
    G.weight[2][1] = 9;
    G.weight[1][3] = 7;
    G.weight[3][1] = 7;
    G.weight[1][4] = 8;
    G.weight[4][1] = 8;
    G.weight[2][3] = 9;
    G.weight[3][2] = 9;
    G.weight[2][4] = 16;
    G.weight[4][2] = 16;
    G.weight[3][4] = 8;
    G.weight[4][3] = 8;
    for (int i = 0; i < vexNum; i++)
    {
        G.weight[i][i] = 666;
    } ////��ʼ������Ȩֵ����ppt�е�Ϊ����
    for (i = 0; i < vexNum; i++)
        for (j = 0; j < vexNum; j++)
            G.arcs[i][j] = 0; //����ͼ�ڽӾ����ʼ��
    for (i = 0; i < arcNum; i++)
    {
        for (j = 0; j < arcNum; j++)
        {
            if (i == j)
                G.arcs[i][j] = 0; //�������ڱߵ��ڽӾ����Ӧֵ��Ϊ0
            else
                G.arcs[i][j] = 1; //�����ڱߵ��ڽӾ����Ӧֵ��Ϊ1
        }
    }
}*/

int main()
{
    ofstream out("FamilyTree.txt");
    string s="����,�ѹ�,1870.5.2-1900.11.3\n �����,�ѹ�,1890.11.3-1940.7.8\n  ����,�ѹ�,1921.3.22-1967.4.4\n   ���ķ�,�ѹ�,1950.7.9-1952.7.18\n   ����Զ,�ѹ�,1952.12.12-1999.4.3\n    ����,����,1974.11.12-\n     ������,����,1995.9.14-\n      ��ʥ��,����,2020.1.2-\n  ������,�ѹ�,1923.11.10-1980.9.3\n   ����,�ѹ�,1950.10.14-\n    ���Ĳ�,�ѹ�,1974.6.7-     ����Դ,�ѹ�,1997.11.9-\n     ������,�ѹ�,1998.6.5-\n  ������,�ѹ�,1908.4.1-1933.2.4\n   ������,�ѹ�,1927.10.18-1999.9.9\n    ����Զ,����,1949.10.1-\n     ����,����,1980.9.15-\n     ��Ϊ��,����,1984.4.13-\n    ������,�ѹ�,1951.7.8-2019.4.3\n     ������,����,1977.5.8-\n    ������,����,1952..30-\n     ����,����,1982.9.9-\n   ����,�ѹ�,1930.9.5-1967.12.13\n    ��̩��,����,1951.11.9-\n     ����Դ,����,1977.2.18-\n ������,�ѹ�,1892.1.4-1944.8.9\n  ������,�ѹ�,1910.11.11-1945.8.12\n  ������,�ѹ�,1915.4.2-1970.12.31\n   ����,�ѹ�,1940.8.7-2005.3.9\n    ������,����,1963.10.18-\n     ����,����,1983.3.18-\n     ����̩,����,1990.3.3-\n      ��Ӫ,����,2018.3.18-\n   ����,����,1950.7.4-\n    ����,�ѹ�,1977.8.11-2000.3.4\n     ������,����,2007.8.11-\n  ��Դ,�ѹ�,1922.8.2-1980.2.6\n   ������,�ѹ�,1944.9.7-1954..12.11\n   ���ӳ�,�ѹ�,1942.1.8-1972.5.8\n    ��ʱ��,�ѹ�,1967.2.4-1973.9.9\n ������,�ѹ�,1900.7.7-1955.2.3";
    int x;
    char y;
    cin>>x>>y;
    cout<<x<<' '<<y;
    //cout<<char(156);
    /*//string s="��绰";
    char *s;
    s=new char[20];
    for (int i = 0; i < 20; i+=2)
    {
        cin>>s[i]>>s[i+1];
    }
    
    cout<<s;*/

    /*mGraph G;
    create_graph(G);
    int visit[5] = {0};
    visit[0] = 1;
    cout << "��A�����������ڽ�����õĽ��ƽ�Ϊ��" << G.vexs[0].name;
    int t = 0, q = 0, sum = 0;
    int temp = 666;
    for (q; q < vexNum - 1; q++)
    {int i = t;
        t = 0;
        for (int j = 0; j < vexNum; j++)
        {
            if (!visit[j] && G.weight[i][j] < temp)
            {
                temp = G.weight[i][j];
                visit[j] = 1;
                if (t)
                    visit[t] = 0;
                else
                    ;
                t = j;
            }
            else
                continue;
        }
        sum += temp;
        cout << G.vexs[t].name<<"("<<temp<<")";
        //q = 0;
        temp = 666;
        if (q == 3)
            sum += G.weight[t][0];
    }
    cout << endl;
    cout << "�˽��ƽ��Ȩֵ֮��Ϊ��" << sum << endl;*/
    return 0;
}