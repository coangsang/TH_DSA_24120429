#include <iostream>
#include <vector>
#include <queue>
#include <stack>

#define endl '\n'
using namespace std;


struct NODE
{
    int key;
    NODE* p_left;
    NODE* p_right;
};

NODE* createNode(int data)
{
    NODE*new_NODE = new NODE;
    new_NODE->key = data;
    new_NODE->p_left = nullptr;
    new_NODE->p_right = nullptr;
    return new_NODE;
}

void NLR_AUX(NODE*pRoot, vector<int>&res)
{
    if (pRoot==nullptr)    return;
    res.push_back(pRoot->key);
    NLR_AUX(pRoot->p_left,res);
    NLR_AUX(pRoot->p_right,res);
}
vector<int> NLR(NODE*pRoot)
{
    vector<int> res;
    NLR_AUX(pRoot,res);
    return res;
}

void LNR_AUX(NODE*pRoot, vector<int>&res)
{
    if (pRoot==nullptr) return;
    LNR_AUX(pRoot->p_left,res);
    res.push_back(pRoot->key);
    LNR_AUX(pRoot->p_right,res);
}
vector<int> LNR(NODE*pRoot)
{
    vector<int> res;
    LNR_AUX(pRoot,res);
    return res;
}

void LRN_AUX(NODE*pRoot, vector<int>&res)
{
    if (pRoot==nullptr)    return;
    LRN_AUX(pRoot->p_left,res);
    LRN_AUX(pRoot->p_right,res);
    res.push_back(pRoot->key);
}

vector<int> LRN(NODE*pRoot)
{
    vector<int>res;
    LRN_AUX(pRoot,res);
    return res;
}

vector<vector<int>> LevelOrder(NODE* pRoot)
{
    vector<vector<int>> res;
    queue<NODE*> q;
    q.push(pRoot);
    int current_lvl = 0;
    while (!q.empty())
    {
        int quantity_node = q.size();
        //tạo 1 ô với cho vector res để có thể dùng chỉ số truy cập vào.
        res.push_back({});

        for (int i = 0;i<quantity_node;i++)
        {
            NODE* current_node = q.front();
            q.pop();

            res[current_lvl].push_back(current_node->key);

            if (current_node->p_left!=nullptr)
            {
                q.push(current_node->p_left);
            }
            if (current_node->p_right!=nullptr)
            {
                q.push(current_node->p_right);
            }
        }
        current_lvl++;
    }
    return res;
}
int countNode(NODE* pRoot)
{
    if (pRoot==nullptr) return 0;
    return 1+countNode(pRoot->p_left)+countNode(pRoot->p_right);
}

int sumNode(NODE* pRoot)
{
    if (pRoot==nullptr) return 0;
    return pRoot->key+sumNode(pRoot->p_left)+sumNode(pRoot->p_right);
}

int countLeaf(NODE* pRoot)
{
    if (pRoot==nullptr) return 0;
    int count = 0;
        count+=countLeaf(pRoot->p_left);
        count+=countLeaf(pRoot->p_right);
    if (pRoot->p_left==nullptr&&pRoot->p_right==nullptr)
        count++;
    return count;
}

int Level(NODE* pRoot, NODE* p)
{
    if (pRoot==p)
    {
        return 0;
    }

    int lvl = 1;
    queue<NODE*>q;
    q.push(pRoot);

    while (!q.empty())
    {
        int quantity_node = q.size();

        for (int i = 0; i<quantity_node;i++)
        {
            NODE* current_node = q.front();
            if (current_node==p)
            {
                return lvl;
            }
            q.pop();

            if (current_node->p_left!=nullptr)
            {
                q.push(current_node->p_left);
            }
            if (current_node->p_right!=nullptr)
            {
                q.push(current_node->p_right);
            }
        }
        lvl++;
    }
    return -1;
}
int Height(NODE* pRoot)
{
    if (pRoot == nullptr) return -1;
    int h_left = Height(pRoot->p_left);
    int h_right = Height(pRoot->p_right);
    return 1 + max(h_left, h_right);
}

int heightNode(NODE* pRoot, int value) 
{
    if (pRoot == nullptr) return -1;

    if (value < pRoot->key)
        return heightNode(pRoot->p_left, value);
    else if (value > pRoot->key)
        return heightNode(pRoot->p_right, value);
    else
        return Height(pRoot);  // Tính chiều cao tại node tìm thấy
}

