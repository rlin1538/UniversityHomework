#include <iostream>
#include <string>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;
/*
1.����ÿ���ڵ������M������
2.���ڵ������������������������Ҷ�ӽڵ㣩
3.�����ڵ�֮������з�Ҷ�ӽڵ㣬������M/2������������ȡ����
4.���з�Ҷ�ӽڵ����keycount,child[0],key[1],child[1],key[2]..key[keycount],child[keycount]
keycountΪ�ýڵ�����Ĺؼ�������
keyΪ�ؼ���
childΪ�������������ڸ����ؼ���֮�䣬���Ա�key��һ��
*/
class MyBTree
{
private:
    enum
    {
        M = 5,
        KEY_MIN = (M + 1) / 2 - 1,
        KEY_MAX = M - 1,
        KEY_START = 1,
        CHILD_MIN = (M + 1) / 2,
        CHILD_MAX = M
    };
    typedef struct Node
    {
        bool leaf;           //�Ƿ�ΪҶ�ӽڵ�
        int keycount;        //��ֵ����,�����ĸ���Ϊkeycount + 1
        Node *parent;        //���ڵ�ָ��
        int keys[M + 1];     //��ֵ/�����Ǵ�1...M��
        Node *childs[M + 1]; //����ָ��0...M
        Node(Node *p = 0, bool flag = true) : leaf(flag), keycount(0), parent(p)
        {
        }
    } BTree;
    typedef struct Result //���Ҳ���ڵ���Ϣ
    {
        Node *node; //Ҫ��keyֵ����Ľڵ�
        int keypos; //Ҫ������node�е�λ��
        Result() : node(0), keypos(1) {}
    } SearchInsertResult, SearchEarseResult;
    BTree *root;
    bool release;

public:
    MyBTree() : root(0), release(false) {}
    ~MyBTree()
    {
        if (this->release == false)
            this->destroy();
    }

private:
    int find_pos(Node *node, int key);                              //����һ���ڵ���keyֵ���ʲ����λ��
    bool find_node(int key, SearchInsertResult *searchres);         //Ѱ�Ҳ���λ����Ϣ,����false˵��û�и��ڵ�
    bool _insert(Node *node, int key, int keypos, Node *child = 0); //��һ���ڵ��keys����Ӽ�ֵ
    bool split(Node *node, Node *&child);
    void _destroy(Node *node);
    bool find_earse(int key, SearchEarseResult *eraseres);     //����false���Ҳ�����,
    bool get_ltree_rnode(Node *start, int keypos, Node *&res); //�õ�keyposλ�����������ҽڵ�
    int get_childpos(Node *parent, Node *child);
    Node *combine(Node *parent, Node *brother, Node *node, int parentKeyPos); //���غϲ�֮��Ľڵ�
public:
    bool insert(int key);
    void layer_print();
    bool destroy();
    bool earse(int key);
};

int MyBTree::find_pos(Node *node, int key)
{
    if (node == nullptr)
        return -1;
    int pos = 1;
    for (; pos <= node->keycount && node->keys[pos] < key; pos++)
        ;
    return pos;
}

bool MyBTree::find_node(int key, SearchInsertResult *searchres)
{
    if (root == nullptr)
    {
        return false;
    }
    int pos = 0;
    BTree *ptmp = root;
    while (!ptmp->leaf)
    {
        pos = this->find_pos(ptmp, key);
        ptmp = ptmp->childs[pos - 1];
    }
    pos = this->find_pos(ptmp, key);
    if (searchres)
    {
        searchres->node = ptmp;
        searchres->keypos = pos;
    }
    return true;
}

bool MyBTree::_insert(Node *node, int key, int keypos, Node *child)
{
    if (node == nullptr || keypos < 1)
        return false;
    for (int i = node->keycount + 1; i >= keypos; i--)
    {
        node->keys[i] = node->keys[i - 1];
        node->childs[i] = node->childs[i - 1];
    }
    node->keys[keypos] = key;
    node->childs[keypos - 1] = child;
    if (child)
        child->parent = node;
    return true;
}

bool MyBTree::split(Node *node, Node *&child)
{
    int pos = (M + 1) / 2;
    Node *left = new Node(node->parent, node->leaf); //���ѳ����Ľڵ�ĸ��ڵ��Ҷ��������ѽڵ���ͬ
    child = left;
    left->childs[0] = node->childs[0];
    if (left->childs[0])
        left->childs[0]->parent = left;
    for (int i = 1; i < pos; i++)
    {
        left->keys[i] = node->keys[i];
        left->childs[i] = node->childs[i];
        if (left->childs[i])
            left->childs[i]->parent = left; //�����˷�ָ
        ++left->keycount;
    }
    node->childs[0] = node->childs[pos];
    for (int i = pos + 1; i < M + 1; i++)
    {
        node->childs[i - pos] = node->childs[i];
        node->keys[i - pos] = node->keys[i];
    }
    node->keycount = node->keycount - pos;

    return true;
}

/*
�������
1.ÿ�εĲ��������ʵ���ǽ���ֵ���뵽Ҷ�ӽڵ��У�keyֵ���ʵ�λ�ã�
	1.1.��������Ҷ�ӽڵ��keycount ������ keycount <= M - 1
		���ýڵ�key����ֵȡ������ӵ����ڵ��ϵ�posλ�ã�Ȼ�󽫸�
		�ڵ���ѳ����������ڵ㣬posλ�õ�key�����֧����childs[pos - 1]
		Ϊ���Ѻ����ڵ㣬�ҷ�֧����Ϊchilds[pos]Ϊ���Ѻ���ҽڵ㣬
		��Ϊ���ڵ����һ���ڵ㣬����Ҫ�жϸ��ڵ��Ƿ������������ظ���ֱ������������
		���˹����У����ĸ߶ȿ������ӣ������µĸ��ڵ㣩
	1.2.��������������ɹ�
*/

bool MyBTree::insert(int key)
{
    SearchInsertResult res;
    if (this->find_node(key, &res) == false)
    {
        root = new Node;
        res.node = root;
        res.keypos = 1;
    }
    Node *node = res.node;
    int pos = res.keypos;
    Node *child = nullptr;
    int mid = key;
    while (node)
    {
        this->_insert(node, mid, pos, child);
        ++node->keycount;
        if (node->keycount > KEY_MAX)
        { //����,����
            mid = node->keys[(M + 1) / 2];
            this->split(node, child); //����childΪ���ص��´����Ľڵ�
            if (node->parent == nullptr)
            {                                          //˵�����˸��ڵ�
                Node *ptmp = new Node(nullptr, false); //��Ϊ�²���ѣ����ﲻ��Ҷ��
                ptmp->keys[KEY_START] = mid;
                ptmp->childs[0] = child;
                ptmp->childs[1] = node;
                child->parent = ptmp;
                node->parent = ptmp;
                ++ptmp->keycount;
                this->root = ptmp; //������ڵ�
                break;
            }
            else
            {
                node = node->parent;
                pos = this->find_pos(node, mid);
            }
        }
        else
        {
            break;
        }
    }
    return true;
}

void MyBTree::layer_print() //�������
{
    if (this->root)
    {
        queue<Node *> Q;
        Q.push(root);
        while (!Q.empty())
        {
            auto ptmp = Q.front();
            Q.pop();
            for (int i = KEY_START; i <= ptmp->keycount; i++)
                cout << ptmp->keys[i] << " ";
            for (int i = 0; i <= ptmp->keycount && ptmp->keycount > 0 && !ptmp->leaf; i++)
                Q.push(ptmp->childs[i]);
        }
        cout << endl;
    }
}

void MyBTree::_destroy(Node *node)
{
    if (node == nullptr)
        return;
    if (node->leaf == false)
        for (int i = node->keycount; i >= 0; i--)
        {
            _destroy(node->childs[i]);
        }
    delete node;
    node = nullptr;
}

bool MyBTree::destroy()
{
    if (this->release == false)
    {
        this->_destroy(this->root);
        this->release = true;
    }
    return true;
}
/*
ɾ������
1.Ҫɾ����keyֵ�ڷ�Ҷ�ӽڵ��ϣ�ʹ�øýڵ�������ڵ��е�child_keyֵ��䣬ת������2
2.Ҫɾ����keyֵ��Ҷ�ӽڵ��ϣ����������B�����ʣ�(M+1)/2 - 1 <= keycount <= M - 1��,����
	2.1	����ýڵ�������ֵܽڵ��keycount > (M + 1)/2 - 1,˵��������������һ����
		�����ڵ��е�keyֵ����һ�����ýڵ��У�Ȼ����ֵܽڵ�keyֵ���һ�������ڵ��С�
	2.2	����ýڵ�������ֵܶ�������keycount > (M + 1)/2 - 1,˵���ֵܽڵ��key����
		�ոպù����Լ��ã���ʱ���ܽ��ˣ�����һ�����ڵ��е�keyֵ��ýڵ���ֵܽڵ��
		����keyֵ�ϲ����ϳ�һ���½ڵ㡣�½ڵ�ָ�򸸽ڵ㡣�����Ϊ�Ӹ��ڵ�������һ��keyֵ
		�����¸��ڵ㲻����keycount >= (M + 1)/2 - 1����������������ڵ㡣
*/
bool MyBTree::find_earse(int key, SearchEarseResult *eraseres)
{
    Node *ptmp = root;
    int pos = 1;
    while (1)
    {
        for (pos = 1; pos <= ptmp->keycount && ptmp->keys[pos] < key; pos++)
            ;
        if (pos > ptmp->keycount || ptmp->keys[pos] > key)
        { //�����ǰ�ڵ��keyֵ��С�ڸ�keyֵ����keyֵ��keys[pos - 1]��keys[pos]֮��
            if (ptmp->leaf)
            { //������keyֵ
                return false;
            }
            ptmp = ptmp->childs[pos - 1];
        }
        else if (ptmp->keys[pos] == key)
        { //�ҵ�
            eraseres->node = ptmp;
            eraseres->keypos = pos;
            return true;
        }
    }
    return true;
}
//�õ������������ҽڵ�
bool MyBTree::get_ltree_rnode(Node *start, int keypos, Node *&res)
{
    if (start == nullptr)
        return false;
    start = start->childs[keypos - 1];
    while (!start->leaf)
    {
        start = start->childs[start->keycount];
    }
    res = start;
    return true;
}

//�õ�child��parent�е�λ��
int MyBTree::get_childpos(Node *parent, Node *child)
{
    for (int i = 0; i <= CHILD_MAX; i++)
        if (child == parent->childs[i])
            return i;
    return -1;
}

MyBTree::Node *MyBTree::combine(Node *parent, Node *brother, Node *node, int parentKeyPos)
{
    int key = parent->keys[parentKeyPos];
    for (int i = parentKeyPos; i < parent->keycount; i++)
    {
        parent->keys[i] = parent->keys[i + 1];
        parent->childs[i] = parent->childs[i + 1];
    }
    --parent->keycount;

    //�ҵ���keyֵС�Ľڵ�ֱ�ӽ�keyֵ��ӵ��ýڵ��ϣ�����������
    if (node->keycount == 0 || key >= node->keys[node->keycount])
    {
        //˵��keyֵ��������node key brotherҲ����node��brother���
        node->keys[node->keycount + 1] = key;
        node->childs[node->keycount + 1] = brother->childs[0]; //ע������ҲҪ�ƶ�
        ++node->keycount;
    }
    else
    {
        brother->keys[brother->keycount + 1] = key;
        brother->childs[brother->keycount + 1] = node->childs[0];
        ++brother->keycount;
    }

    Node *mergedNode = new Node(parent, node->leaf);
    if (node->keys[1] > brother->keys[brother->keycount])
    {
        mergedNode->childs[0] = brother->childs[0];
        for (int i = 1; i <= brother->keycount; i++)
        {
            mergedNode->keys[i] = brother->keys[i];
            mergedNode->childs[i] = brother->childs[i];
            if (!mergedNode->leaf) //��Ҫ����ָ
                mergedNode->childs[i]->parent = mergedNode;
        }
        for (int i = brother->keycount + 1; i <= brother->keycount + node->keycount; i++)
        {
            mergedNode->keys[i] = node->keys[i - brother->keycount];
            mergedNode->childs[i] = node->childs[i - brother->keycount];
            if (!mergedNode->leaf) //��Ҫ����ָ
                mergedNode->childs[i]->parent = mergedNode;
        }
    }
    else
    {
        mergedNode->childs[0] = node->childs[0];
        for (int i = 1; i <= node->keycount; i++)
        {
            mergedNode->keys[i] = node->keys[i];
            mergedNode->childs[i] = node->childs[i];
            if (!mergedNode->leaf) //��Ҫ����ָ
                mergedNode->childs[i]->parent = mergedNode;
        }
        for (int i = node->keycount + 1; i <= node->keycount + brother->keycount; i++)
        {
            mergedNode->keys[i] = brother->keys[i - node->keycount];
            mergedNode->childs[i] = brother->childs[i - node->keycount];
            if (!mergedNode->leaf) //��Ҫ����ָ
                mergedNode->childs[i]->parent = mergedNode;
        }
    }
    mergedNode->keycount = node->keycount + brother->keycount;
    parent->childs[parentKeyPos - 1] = mergedNode;

    delete node;
    delete brother;
    return mergedNode;
}

bool MyBTree::earse(int key)
{
    if (this->root == nullptr)
        return false;
    SearchEarseResult eraseres;
    if (false == this->find_earse(key, &eraseres))
        return false;
    Node *node = eraseres.node;
    int pos = eraseres.keypos;
    if (!node->leaf)
    {                            //��Ҷ�ӽڵ�
        Node *replace = nullptr; //�滻keyֵ�Ľڵ�
        this->get_ltree_rnode(node, pos, replace);
        node->keys[pos] = replace->keys[replace->keycount];
        node = replace;
        --replace->keycount;
    }
    else
    {
        for (int i = pos; i < node->keycount; i++)
        {
            node->keys[i] = node->keys[i + 1];
            //Ҷ�ӽڵ�û���������Ͳ����ƶ���
        }
        --node->keycount;
    }
    while (1)
    {
        if (node->parent == nullptr)
        { //���ڵ�
            if (node->keycount == 0)
            {
                if (!node->leaf)
                { //����Ҷ�ӽڵ�˵����child,���ĸ��ڵ�
                    root = node->childs[0];
                    root->parent = nullptr;
                }
                else
                    root = nullptr;
                delete node;
            }
            return true;
        }

        if (node->keycount < KEY_MIN)
        {                                                          //������keycount => (M + 1)/2 - 1
            int childpos = this->get_childpos(node->parent, node); //�õ�node��node->parent childs�е�λ��
            //�Ƚ�
            auto parent = node->parent;
            if (childpos > 0 && parent->childs[childpos - 1]->keycount > KEY_MIN)
            { //���������ֵܽ裬�����ֵ����һ��keyֵҲЯ�����һ��child��
                //���׽ڵ�key����ǰ����ӵ���һ��λ�ã����key�����׽ڵ㣬Я����child����ǰ����һ��λ�á�
                auto left = parent->childs[childpos - 1];
                for (int i = node->keycount + 1; i >= 1; i--)
                {
                    node->keys[i] = node->keys[i - 1];
                    node->childs[i] = node->childs[i - 1];
                }
                node->keys[1] = parent->keys[childpos];
                ++node->keycount;

                node->childs[0] = left->childs[left->keycount]; //Я����child
                node->childs[0]->parent = node;

                parent->keys[childpos] = left->keys[left->keycount];
                --left->keycount;
                return true;
            }
            else if (childpos < parent->keycount && parent->childs[childpos + 1]->keycount > KEY_MIN)
            { //���������ֵܽ裬�����ֵܵĵ�һ��keyֵ��ҲЯ����һ��child
                auto right = parent->childs[childpos + 1];
                node->keys[node->keycount + 1] = parent->keys[childpos + 1];
                ++node->keycount;
                parent->keys[childpos + 1] = right->keys[1];

                node->childs[node->keycount] = right->childs[0]; //Я����child
                node->childs[0]->parent = node;

                for (int i = 0; i < right->keycount; i++)
                {
                    right->keys[i] = right->keys[i + 1];
                    right->childs[i] = right->childs[i + 1];
                }

                --right->keycount;
                return true;
            }
            else
            { //û�赽,�򸸽ڵ�Ҫ����һ��������ҽڵ�ϲ�
                Node *mergedNode = nullptr;
                if (childpos > 0)
                { //�����ֵ�
                    auto left = parent->childs[childpos - 1];
                    mergedNode = this->combine(parent, left, node, childpos);
                }
                else if (childpos < parent->keycount)
                { //�����ֵ�
                    auto right = parent->childs[childpos + 1];
                    mergedNode = this->combine(parent, right, node, childpos + 1);
                }
                node = mergedNode->parent; //����
            }
        }
        else
        { //����keycount => (M + 1)/2 - 1
            return true;
        }
    }
    return true;
}

int main()
{
    
}