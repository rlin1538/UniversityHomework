#include <iostream>
#include <string>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;
/*
1.树的每个节点最多有M个子树
2.根节点至少有两个子树（如果不是叶子节点）
3.除根节点之外的所有非叶子节点，至少有M/2个子树（向上取整）
4.所有非叶子节点包括keycount,child[0],key[1],child[1],key[2]..key[keycount],child[keycount]
keycount为该节点包含的关键字数量
key为关键字
child为子树，子树插在各个关键字之间，所以比key多一个
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
        bool leaf;           //是否为叶子节点
        int keycount;        //键值个数,子树的个数为keycount + 1
        Node *parent;        //父节点指针
        int keys[M + 1];     //键值/数组是从1...M的
        Node *childs[M + 1]; //子树指针0...M
        Node(Node *p = 0, bool flag = true) : leaf(flag), keycount(0), parent(p)
        {
        }
    } BTree;
    typedef struct Result //查找插入节点信息
    {
        Node *node; //要将key值插入的节点
        int keypos; //要插入在node中的位置
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
    int find_pos(Node *node, int key);                              //查找一个节点上key值合适插入的位置
    bool find_node(int key, SearchInsertResult *searchres);         //寻找插入位置信息,返回false说明没有根节点
    bool _insert(Node *node, int key, int keypos, Node *child = 0); //在一个节点的keys中添加键值
    bool split(Node *node, Node *&child);
    void _destroy(Node *node);
    bool find_earse(int key, SearchEarseResult *eraseres);     //返回false查找不存在,
    bool get_ltree_rnode(Node *start, int keypos, Node *&res); //得到keypos位置左子树最右节点
    int get_childpos(Node *parent, Node *child);
    Node *combine(Node *parent, Node *brother, Node *node, int parentKeyPos); //返回合并之后的节点
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
    Node *left = new Node(node->parent, node->leaf); //分裂出来的节点的父节点和叶子性与分裂节点相同
    child = left;
    left->childs[0] = node->childs[0];
    if (left->childs[0])
        left->childs[0]->parent = left;
    for (int i = 1; i < pos; i++)
    {
        left->keys[i] = node->keys[i];
        left->childs[i] = node->childs[i];
        if (left->childs[i])
            left->childs[i]->parent = left; //别忘了反指
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
插入操作
1.每次的插入操作其实都是将键值插入到叶子节点中（key值合适的位置）
	1.1.若插入后该叶子节点的keycount 不满足 keycount <= M - 1
		将该节点key的中值取出，添加到父节点上的pos位置，然后将该
		节点分裂成左右两个节点，pos位置的key的左分支子树childs[pos - 1]
		为分裂后的左节点，右分支子树为childs[pos]为分裂后的右节点，
		因为父节点多了一个节点，所以要判断父节点是否满足条件。重复。直到满足条件。
		（此过程中，树的高度可能增加，生成新的根节点）
	1.2.若满足条件插入成功
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
        { //过大,分裂
            mid = node->keys[(M + 1) / 2];
            this->split(node, child); //分裂child为返回的新创建的节点
            if (node->parent == nullptr)
            {                                          //说明到了根节点
                Node *ptmp = new Node(nullptr, false); //因为下层分裂，这里不是叶子
                ptmp->keys[KEY_START] = mid;
                ptmp->childs[0] = child;
                ptmp->childs[1] = node;
                child->parent = ptmp;
                node->parent = ptmp;
                ++ptmp->keycount;
                this->root = ptmp; //重设根节点
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

void MyBTree::layer_print() //层序遍历
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
删除操作
1.要删除的key值在非叶子节点上，使用该节点的子树节点中的child_key值填充，转到步骤2
2.要删除的key值在叶子节点上，如果不满足B树性质（(M+1)/2 - 1 <= keycount <= M - 1）,调整
	2.1	如果该节点的左右兄弟节点的keycount > (M + 1)/2 - 1,说明可以向他“借一个”
		将父节点中的key值下移一个到该节点中，然后后兄弟节点key值填充一个到父节点中。
	2.2	如果该节点的左右兄弟都不满足keycount > (M + 1)/2 - 1,说明兄弟节点的key数量
		刚刚好够它自己用，此时不能借了，拿下一个父节点中的key值与该节点和兄弟节点的
		所有key值合并，合成一个新节点。新节点指向父节点。如果因为从父节点上拿下一个key值
		而导致父节点不满足keycount >= (M + 1)/2 - 1的条件，则调整父节点。
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
        { //如果当前节点的key值都小于该key值，或key值在keys[pos - 1]，keys[pos]之间
            if (ptmp->leaf)
            { //不存在key值
                return false;
            }
            ptmp = ptmp->childs[pos - 1];
        }
        else if (ptmp->keys[pos] == key)
        { //找到
            eraseres->node = ptmp;
            eraseres->keypos = pos;
            return true;
        }
    }
    return true;
}
//得到左子树的最右节点
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

//得到child在parent中的位置
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

    //找到比key值小的节点直接将key值添加到该节点上，方便后面操作
    if (node->keycount == 0 || key >= node->keys[node->keycount])
    {
        //说明key值的排序是node key brother也就是node在brother左侧
        node->keys[node->keycount + 1] = key;
        node->childs[node->keycount + 1] = brother->childs[0]; //注意子树也要移动
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
            if (!mergedNode->leaf) //不要忘反指
                mergedNode->childs[i]->parent = mergedNode;
        }
        for (int i = brother->keycount + 1; i <= brother->keycount + node->keycount; i++)
        {
            mergedNode->keys[i] = node->keys[i - brother->keycount];
            mergedNode->childs[i] = node->childs[i - brother->keycount];
            if (!mergedNode->leaf) //不要忘反指
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
            if (!mergedNode->leaf) //不要忘反指
                mergedNode->childs[i]->parent = mergedNode;
        }
        for (int i = node->keycount + 1; i <= node->keycount + brother->keycount; i++)
        {
            mergedNode->keys[i] = brother->keys[i - node->keycount];
            mergedNode->childs[i] = brother->childs[i - node->keycount];
            if (!mergedNode->leaf) //不要忘反指
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
    {                            //非叶子节点
        Node *replace = nullptr; //替换key值的节点
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
            //叶子节点没有子树，就不用移动了
        }
        --node->keycount;
    }
    while (1)
    {
        if (node->parent == nullptr)
        { //根节点
            if (node->keycount == 0)
            {
                if (!node->leaf)
                { //不是叶子节点说明有child,更改根节点
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
        {                                                          //不满足keycount => (M + 1)/2 - 1
            int childpos = this->get_childpos(node->parent, node); //得到node在node->parent childs中的位置
            //先借
            auto parent = node->parent;
            if (childpos > 0 && parent->childs[childpos - 1]->keycount > KEY_MIN)
            { //可以向左兄弟借，借左兄弟最后一个key值也携带最后一个child，
                //父亲节点key给当前，添加到第一个位置，这个key给父亲节点，携带的child给当前，第一个位置。
                auto left = parent->childs[childpos - 1];
                for (int i = node->keycount + 1; i >= 1; i--)
                {
                    node->keys[i] = node->keys[i - 1];
                    node->childs[i] = node->childs[i - 1];
                }
                node->keys[1] = parent->keys[childpos];
                ++node->keycount;

                node->childs[0] = left->childs[left->keycount]; //携带的child
                node->childs[0]->parent = node;

                parent->keys[childpos] = left->keys[left->keycount];
                --left->keycount;
                return true;
            }
            else if (childpos < parent->keycount && parent->childs[childpos + 1]->keycount > KEY_MIN)
            { //可以向右兄弟借，借右兄弟的第一个key值，也携带第一个child
                auto right = parent->childs[childpos + 1];
                node->keys[node->keycount + 1] = parent->keys[childpos + 1];
                ++node->keycount;
                parent->keys[childpos + 1] = right->keys[1];

                node->childs[node->keycount] = right->childs[0]; //携带的child
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
            { //没借到,向父节点要，再一起与左或右节点合并
                Node *mergedNode = nullptr;
                if (childpos > 0)
                { //有左兄弟
                    auto left = parent->childs[childpos - 1];
                    mergedNode = this->combine(parent, left, node, childpos);
                }
                else if (childpos < parent->keycount)
                { //有右兄弟
                    auto right = parent->childs[childpos + 1];
                    mergedNode = this->combine(parent, right, node, childpos + 1);
                }
                node = mergedNode->parent; //上溯
            }
        }
        else
        { //满足keycount => (M + 1)/2 - 1
            return true;
        }
    }
    return true;
}

int main()
{
    
}