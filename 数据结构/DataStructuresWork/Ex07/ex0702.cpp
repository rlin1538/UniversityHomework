//�����ڽӾ����Dijkastra�㷨(��Դ�������·��)
#include <iostream>
#define OK 1
#define OVERFLOW 0
#define ERROR 0
#define INFINITY 999999 //�Զ���һ�������
#define MAX_V 20
using namespace std;

struct VertexType
{
    int code;  //������
    int value; //����Ԫ��ֵ
};

struct MGraph
{
    int arcs[MAX_V][MAX_V]; //�ڽӾ���
    int vexnum, arcnum;     //������������
    VertexType vexs[MAX_V]; //������Ϣ
    int GraphKind;          //ͼ���ͣ�������������Ϊ��
};
//��ʼ�������ٲ���
int CreateGraph(MGraph &G) //����������
{
    int v, w;   //������
    int weight; //�ߵ�Ȩ��
    cout << "��������������������ߵĸ�����";
    cin >> G.vexnum >> G.arcnum;
    cout << "����" << G.vexnum << "��������Ϣ:";
    for (int i = 0; i < G.vexnum; i++) //���붥����Ϣ
    {
        G.vexs[i].code = i;
        cin >> G.vexs[i].value;
    }
    for (int i = 0; i < MAX_V; i++) //�ڽӾ����ʼ��
        for (int j = 0; j < MAX_V; j++)
            G.arcs[i][j] = INFINITY; //����ʼ��Ϊ�����
    for (int i = 0; i < G.arcnum; i++)
    {
        cout << "�����(��������)����Ȩ�أ�";
        cin >> v >> w >> weight;
        G.arcs[v][w] = weight;
    }
    return OK;
}

void Dijkastra(MGraph G, int cur) //Dijikastra�㷨,curΪ��������
{
    int dis[MAX_V];   //��¼��̾���
    int path[MAX_V];  //��¼·��
    bool flag[MAX_V]; //����������
    int min = INFINITY;
    int temp;

    for (int i = 0; i < G.vexnum; i++) //��һ�ֲ���
    {
        flag[i] = false;
        dis[i] = G.arcs[cur][i];
        if (dis[i] < INFINITY)
            path[i] = cur;
        else
            path[i] = -1;
    }
    dis[cur] = 0;                          //����������Ϊ0
    flag[cur] = true;                      //������߹�
    for (int i = 0; i < G.vexnum - 1; i++) //�������·
    {
        min = INFINITY;
        for (int j = 0; j < G.vexnum; j++)
            if (flag[j] == false && dis[j] < min)
            {
                min = dis[j];
                temp = j;
            }
        flag[temp] = true;
        if (min == INFINITY)
            continue;
        for (int j = 0; j < G.vexnum; j++)
        {
            if (flag[j] == false && G.arcs[temp][j] < INFINITY)
                if (G.arcs[temp][j] + min < dis[j])
                {
                    dis[j] = G.arcs[temp][j] + min;
                    path[j] = temp;
                }
        }
    }
    cout << "dis����Ϊ��";
    for (int i = 0; i < G.vexnum; i++)
        cout << dis[i] << '\t';
    cout << endl
         << "path����Ϊ��";
    for (int i = 0; i < G.vexnum; i++)
        cout << path[i] << '\t';
}

int main()
{
    MGraph G;
    CreateGraph(G);
    Dijkastra(G, 0);
}