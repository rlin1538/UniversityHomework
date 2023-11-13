//�����ڽӱ��������ȱ����͹�����ȱ���
#include <iostream>
#define MAX_V 20
using namespace std;

bool flag[MAX_V]; //����ʱ�ı������

struct ArcNode //�߽��
{
    int adjvex;       //������
    int weight;       //��Ȩֵ�����ã�
    ArcNode *nextarc; //��һ���ߵĵ�ַ
};
struct VexNode
{
    int data;          //������Ϣ
    ArcNode *firstarc; //ָ���һ���߽��
};
struct AlGpraph
{
    VexNode AdjList[MAX_V]; //�ڽӱ�
    int vexnum, arcnum;     //�����������
    int vexs[MAX_V];        //������Ϣ
    //GraphKind type    //ͼ���ͣ�����������ͼΪ��
};
//��������ͼ(������ͼΪ��)
void CreatGraph(AlGpraph &G)
{
    ArcNode *p;
    int i, j;

    cout << "��������ͼ�������ͱ�����";
    cin >> G.vexnum >> G.arcnum;
    cout << "���붥����Ϣ��";
    for (i = 0; i < G.vexnum; i++)
    {
        cin >> G.vexs[i]; //���붥����Ϣ
        G.AdjList[i].data = G.vexs[i];
        G.AdjList[i].firstarc = NULL; //��ʼ���ڽӱ�
    }
    for (int k = 0; k < G.arcnum; k++)
    {
        cout << "�����" << k + 1 << "����(������)��";
        cin >> i >> j;
        p = new ArcNode; //�����±�
        p->adjvex = j;   //���յ�Ϊj
        p->nextarc = G.AdjList[i].firstarc;
        G.AdjList[i].firstarc = p; //���߽ӵ��ڽӱ���Ӧ������������
        p = new ArcNode;           //����ͼ�����ԳƱ�
        p->adjvex = i;
        p->nextarc = G.AdjList[j].firstarc;
        G.AdjList[j].firstarc = p;
    }
}

void DFS(AlGpraph G, int cur)
{
    ArcNode *p;
    flag[cur] = true;
    cout << G.vexs[cur] << '\t'; //�������
    p = G.AdjList[cur].firstarc; //pָ��cur����ĵ�һ����
    while (p)
    {
        if (flag[p->adjvex] == false) //�ñ��յ�δ����
            DFS(G, p->adjvex);        //�ݹ����
        p = p->nextarc;               //��һ����
    }
}
//������ȱ���
void DFS_visit(AlGpraph G)
{
    for (int i = 0; i < G.vexnum; i++)
        flag[i] = false; //��������ʼ��Ϊfalse��ʾδ����
    for (int i = 0; i < G.vexnum; i++)
    {
        if (flag[i] == false)
            DFS(G, i);
    }
    cout << endl;
}

void BFS(AlGpraph G, int cur)
{
    ArcNode *p;
    int l;                   //��ų��Ӷ���
    int q[MAX_V];            //����
    int front = 0, rear = 0; //��ͷ��βָ��

    q[rear++] = cur; //��ǰ�������
    flag[cur] = true;
    while (rear != front)
    {
        l = q[front]; //��ͷ����
        front = (front + 1) % MAX_V;
        cout << G.vexs[l] << '\t';
        p = G.AdjList[l].firstarc; //��ָ��ָ��l���ڽӵ�
        while (p)
        {
            if (flag[p->adjvex] == false)
            {
                q[rear] = p->adjvex; //δ���ʵĵ����
                rear = (rear + 1) % MAX_V;
                flag[p->adjvex] = true;
            }
            p = p->nextarc;
        }
    }
}
//������ȱ���
void BFS_visit(AlGpraph G)
{
    for (int i = 0; i < G.vexnum; i++)
        flag[i] = false; //��������ʼ��Ϊfalse��ʾδ����
    for (int i = 0; i < G.vexnum; i++)
    {
        if (flag[i] == false)
            BFS(G, i);
    }
    cout << endl;
}
int main()
{
    AlGpraph G;

    CreatGraph(G);
    cout << "������ȱ�����";
    DFS_visit(G);
    cout << "������ȱ�����";
    BFS_visit(G);

    return 0;
}
