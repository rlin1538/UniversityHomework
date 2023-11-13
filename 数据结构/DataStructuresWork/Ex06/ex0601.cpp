#include <iostream>
#define OK 1
#define OVERFLOW 0
#define ERROR 0
#define INFINITY 999999 //�Զ���һ�������
#define MAX_V 20
using namespace std;

int sum = 0;           //��������
int flag[MAX_V] = {0}; //����������

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
    int GraphKind;          //ͼ���ͣ�0����ͼ��1����ͼ��2Ϊ��������3������
};
//��ʼ�������ٲ���
int CreateGraph(MGraph &G) //����ͼ
{
    int v, w;   //������
    int weight; //�ߵ�Ȩ��
    cout << "����ͼ����(0����ͼ��1����ͼ��2Ϊ��������3������)��";
    cin >> G.GraphKind;
    cout << "����ͼ����������ߵĸ�����";
    cin >> G.vexnum >> G.arcnum;
    cout << "����" << G.vexnum << "�������Ԫ��ֵ:";
    for (int i = 0; i < G.vexnum; i++) //���붥����Ϣ
    {
        G.vexs[i].code = i;
        cin >> G.vexs[i].value;
    }
    for (int i = 0; i < MAX_V; i++) //�ڽӾ����ʼ��
        for (int j = 0; j < MAX_V; j++)
            if (G.GraphKind == 1 || G.GraphKind == 0) //����ͼ������ͼ��ʼ��Ϊ0
                G.arcs[i][j] = 0;
            else
                G.arcs[i][j] = INFINITY; //����ʼ��Ϊ�����
    if (G.GraphKind == 0 || G.GraphKind == 1)
    {
        for (int i = 0; i < G.arcnum; i++)
        {
            cout << "�����(��������)��";
            cin >> v >> w;
            G.arcs[v][w] = 1;
            if (G.GraphKind == 0)
                G.arcs[w][v] = 1;
        }
    }
    else
    {
        for (int i = 0; i < G.arcnum; i++)
        {
            cout << "�����(��������)����Ȩ�أ�";
            cin >> v >> w >> weight;
            G.arcs[v][w] = weight;
            if (G.GraphKind == 2)
                G.arcs[w][v] = weight;
        }
    }
    return OK;
}
int DestroyGraph(MGraph &G) //ɾ��ͼ
{
    for (int i = 0; i < G.vexnum; i++) //�ڽӾ������
        for (int j = 0; j < G.vexnum; j++)
            if (G.GraphKind == 1 || G.GraphKind == 0) //����ͼ������ͼΪ0
                G.arcs[i][j] = 0;
            else
                G.arcs[i][j] = INFINITY; //����ʼ��Ϊ�����
    G.arcnum = G.vexnum = 0;             //����ͱ�����
    return OK;
}
//�����Ͳ���
int GetVex(MGraph G, int V_num) //��ȡ��V_num�������Ԫ��ֵ
{
    if (G.vexnum)
    {
        return G.vexs[V_num].value;
        return OK;
    }
    return ERROR;
}
int FirstAdjVex(MGraph G, int V_num) //��ȡ��V_num������ĵ�һ���ڽӵ�
{
    if (G.vexnum)
    {
        for (int i = 0; i < G.vexnum; i++)
        {
            if (G.arcs[V_num][i] && G.arcs[V_num][i] != INFINITY)
                return i;
        }
    }
    return -1;
}
int NextAdjVex(MGraph G, int v_num, int w_num) //��ȡ��V_num��������w_num֮���һ���ڽӵ�
{
    if (G.vexnum && (G.arcs[v_num][w_num] && G.arcs[v_num][w_num] != INFINITY)) //ͼ������v��w��ȷ����
    {
        if (w_num == G.vexnum - 1)
            return -1; //w��v�����һ���㣬���ؿ�
        for (int i = w_num + 1; i < G.vexnum; i++)
        {
            if (G.arcs[v_num][i] && G.arcs[v_num][i] != INFINITY)
                return i;
        }
    }
    return -1;
}
void DFSTraverse(MGraph G, int cur) //������ȱ���
{
    cout << G.vexs[cur].value << '\t'; //�������
    flag[cur] = 1;
    sum++;
    if (sum == G.vexnum)
        return;
    for (int i = 0; i < G.vexnum; i++)
    {
        if (flag[i] == 0 && G.arcs[cur][i] && G.arcs[cur][i] != INFINITY)
        {
            DFSTraverse(G, i);
        }
    }
}
void BFSTraverse(MGraph G, int cur) //������ȱ���
{
    int q[MAX_V];    //����
    int front, rear; //��ͷ��βָ��
    int p;           //

    for (int i = 0; i < G.vexnum; i++) //�����������
        flag[i] = 0;

    front = rear = 0;
    q[rear] = cur; //cur�������
    flag[cur] = 1;
    rear = (rear + 1) % MAX_V;
    while (front < rear)
    {
        p = q[front];
        cout << G.vexs[p].value << '\t'; //�������
        front = (front + 1) % MAX_V;     //��ͷ����
        for (int i = 0; i < G.vexnum; i++)
        {
            if (flag[i] == 0 && G.arcs[p][i] && G.arcs[p][i] != INFINITY)
            {
                q[rear] = i;
                rear = (rear + 1) % MAX_V;
                flag[i] = 1;
            }
        }
    }
}
//�ӹ��Ͳ���
int InsertVex(MGraph &G, int v_value) //���붥��
{
    if (G.vexnum)
    {
        G.vexs[G.vexnum].code = G.vexnum;
        G.vexs[G.vexnum].value = v_value;
        G.vexnum++;
        return OK;
    }
    return ERROR;
}
int InsertArc(MGraph &G, int v_num, int w_num) //�����
{
    int weight = 1;

    if (G.vexnum)
    {
        G.arcnum++;
        if (G.GraphKind == 2 || G.GraphKind == 3) //��Ϊ����������Ȩֵ
        {
            cout << "����ñ�Ȩ�أ�";
            cin >> weight;
            G.arcs[v_num][w_num] = weight;
        }
        else //����Ϊ����ͼ������ͼ
        {
            G.arcs[v_num][w_num] = weight;
        }
        if (G.GraphKind == 0 || G.GraphKind == 2) //��Ϊ����ͼ����ԳƸ�ֵ
            G.arcs[w_num][v_num] = 1;
        return OK;
    }
    return ERROR;
}
int DeleteVex(MGraph &G, int v_num) //ɾ������
{
    int count = 0;
    if (G.vexnum)
    {
        for (int i = 0; i < G.vexnum; i++)
        {
            if (G.arcs[v_num][i] && G.arcs[v_num][i] != INFINITY) //�Ʊ���
                count++;
            if ((G.GraphKind == 1 || G.GraphKind == 3) && G.arcs[i][v_num] && G.arcs[i][v_num] != INFINITY) //������ͼ�������
                count++;
        }
        for (int i = v_num + 1; i < G.vexnum; i++)
        {
            G.vexs[i - 1].value = G.vexs[i].value; //�����Ÿ���
            for (int j = 0; j < G.vexnum; j++)     //ɾ����
                G.arcs[i - 1][j] = G.arcs[i][j];
        }
        for (int j = v_num + 1; j < G.vexnum; j++)
        {
            for (int i = 0; i < G.vexnum - 1; i++) //ɾ����
                G.arcs[i][j - 1] = G.arcs[i][j];
        }
        G.arcnum -= count;
        G.vexnum--; //������-1
        return OK;
    }
    return ERROR;
}
int DeleteArc(MGraph &G, int v_num, int w_num) //ɾ����
{
    if (G.vexnum)
    {
        if (G.GraphKind == 0 || G.GraphKind == 1)
        {
            G.arcs[v_num][w_num] = 0;
            if (G.GraphKind == 0)
                G.arcs[w_num][v_num] = 0;
        }
        else
        {
            G.arcs[v_num][w_num] = INFINITY;
            if (G.GraphKind == 2)
                G.arcs[w_num][v_num] = INFINITY;
        }
        G.arcnum--;
        return OK;
    }
    return ERROR;
}

int menu_sel() //���Բ˵�
{
    char *m[12] = {(char *)"1.����ͼ",
                   (char *)"2.ɾ��ͼ",
                   (char *)"3.��ȡ����Ԫ��",
                   (char *)"4.���Ҷ���v�׸��ڽӵ�",
                   (char *)"5.���Ҷ���v���w���׸��ڽӵ�",
                   (char *)"6.������ȱ���",
                   (char *)"7.������ȱ���",
                   (char *)"8.���붥��",
                   (char *)"9.�����",
                   (char *)"10.ɾ������",
                   (char *)"11.ɾ����",
                   (char *)"0.�˳�"};
    int i, choice;
    do
    {
        system("cls");
        cout << "-------���˵�-------" << endl;
        for (i = 0; i < 12; i++)
            cout << m[i] << endl;
        cout << "������ѡ��";
        cin >> choice;
    } while (choice < 0 || choice > 11);
    return choice;
}

int main()
{
    MGraph G;
    int sel, temp;
    int v, w;

    for (;;)
    {
        switch (sel = menu_sel())
        {
        case 1:
            CreateGraph(G);
            system("pause");
            break;
        case 2:
            DestroyGraph(G);
            system("pause");
            break;
        case 3:
            cout << "����Ԫ�ر��:";
            cin >> v;
            cout << "Ԫ��ֵΪ��" << GetVex(G, v) << endl;
            system("pause");
            break;
        case 4:
            cout << "����Ԫ�ر��:";
            cin >> v;
            temp = FirstAdjVex(G, v);
            if (temp >= 0)
                cout << "�׸��ڽӵ���Ϊ��" << temp << endl;
            else
                cout << "�ڽӵ�Ϊ��" << endl;
            system("pause");
            break;
        case 5:
            cout << "����Ԫ��v��w���:";
            cin >> v >> w;
            temp = NextAdjVex(G, v, w);
            if (temp >= 0)
                cout << "����׸��ڽӵ���Ϊ��" << temp << endl;
            else
                cout << "��" << endl;
            system("pause");
            break;
        case 6:
            cout << "������ȱ���Ϊ��";
            for (int i = 0; i < G.vexnum; i++) //�����������
                flag[i] = 0;
            sum = 0; //����
            DFSTraverse(G, 0);
            cout << endl;
            system("pause");
            break;
        case 7:
            cout << "������ȱ�����";
            BFSTraverse(G, 0);
            cout << endl;
            system("pause");
            break;
        case 8:
            cout << "�����¶���Ԫ��ֵ��";
            cin >> v;
            if (InsertVex(G, v))
                cout << "����ɹ�" << endl;
            else
                cout << "����ʧ��" << endl;
            //cout << G.vexnum << '\t' << G.arcnum << endl;
            system("pause");
            break;
        case 9:
            cout << "���붥��v��w���:";
            cin >> v >> w;
            if (InsertArc(G, v, w))
                cout << "����ɹ�" << endl;
            else
                cout << "����ʧ��" << endl;
            //cout << G.vexnum << '\t' << G.arcnum << endl;
            system("pause");
            break;
        case 10:
            cout << "����ɾ���Ķ�����:";
            cin >> v;
            if (DeleteVex(G, v))
                cout << "ɾ���ɹ�" << endl;
            else
                cout << "ɾ��ʧ��" << endl;
            //cout << G.vexnum << '\t' << G.arcnum << endl;
            system("pause");
            break;
        case 11:
            cout << "����ɾ���ı�:";
            cin >> v >> w;
            if (DeleteArc(G, v, w))
                cout << "ɾ���ɹ�" << endl;
            else
                cout << "ɾ��ʧ��" << endl;
            //cout << G.vexnum << '\t' << G.arcnum << endl;
            system("pause");
            break;
        case 0:
            break;
        }
        if (sel == 0)
            break;
    }
}