#include <iostream>
#include <vector>
using namespace std;

struct NODE{
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

NODE* Search(NODE* pRoot, int x)
{
    if (pRoot==nullptr) return nullptr;
    NODE*current_node = pRoot;
    while (current_node!=nullptr)
    {
        if (current_node->key==x)
            return current_node;

        if (current_node->key<x)
            current_node = current_node->p_right;
        else
            current_node = current_node->p_left;
    }
    return nullptr;
}

void Insert(NODE* &pRoot, int x)
{
    if (pRoot==nullptr)
    {
        pRoot = createNode(x);
        return;
    }

    NODE* current_node = pRoot;
    while (1)
    {
        if (current_node->key<x)
        {
            if (current_node->p_right==nullptr)
            {
                current_node->p_right = createNode(x);
                return;
            }
            current_node = current_node->p_right;
        }
        else if (current_node->key>x)
        {
            if (current_node->p_left==nullptr)
            {
                current_node->p_left = createNode(x);
                return;
            }
            current_node = current_node->p_left;
        }
        else//đã tồn tại key này trong cây
            return;
    }
}


void Remove(NODE* &pRoot, int x)
{
    if (pRoot==nullptr)
        return;

    NODE*prev=nullptr;
    NODE*curr = pRoot;
    while (curr!=nullptr&&curr->key!=x)
    {
        //prev đi theo sau curr;
        prev = curr;
        if (curr->key>x)
            curr = curr->p_left;
        else
            curr = curr->p_right;
    }

    //không tồn tại
    if(curr==nullptr) return;
    //node cần xoá curr là lá
    
    //có 1 hoặc 0 con
    if (curr->p_left==nullptr||curr->p_right==nullptr)
    {
        NODE* new_curr;
        if (curr->p_left==nullptr) new_curr = curr->p_right;
        else new_curr = curr->p_left;

        if (prev==nullptr)
        {
            pRoot=new_curr;
            delete curr;
            return;
        } 
        if (prev->p_left==curr) prev->p_left = new_curr;
        else prev->p_right = new_curr;

        delete curr;
        return;
    }
    else
    {
        //tìm node kế thừa aka node thế mạng cho node cần xoá (curr);
        NODE*m_prev=nullptr;
        NODE*successor=curr->p_right;
        while (successor!=nullptr&&successor->p_left!=nullptr)
        {
            m_prev = successor;
            successor=successor->p_left;
        }
        curr->key = successor->key;
        //nếu con phải có con trái
        if (m_prev!=nullptr)
            m_prev->p_left=successor->p_right;
        else
            curr->p_right = successor->p_right;
        delete successor;
    }

}

NODE* createTree(int a[], int n)
{
    NODE*root=nullptr;
    for (int i = 0;i<n;i++)
    {
        Insert(root,a[i]);
    }
    return root;
}

void removeTree(NODE* &pRoot)
{
    if (pRoot == nullptr) return;
    removeTree(pRoot->p_left);
    removeTree(pRoot->p_right);
    delete pRoot;
    pRoot = nullptr;
}

int Height(NODE* pRoot)
{
    if(pRoot==nullptr) return -1;
    int height_left = Height(pRoot->p_left);
    int height_right= Height(pRoot->p_right);
    //chiều cao nút cha = chiều cao lớn nhất nút con + 1
    return (height_left>height_right?height_left:height_right)+1;
}
void printInOrder(NODE* root)
{
    if (root == nullptr) return;
    printInOrder(root->p_left);
    cout << root->key << " ";
    printInOrder(root->p_right);
}

int countNode(NODE* pRoot)
{
    if (pRoot==nullptr) return 0;
    return 1+countNode(pRoot->p_left)+countNode(pRoot->p_right);
}
int countLess(NODE* pRoot, int x)
{
    if(pRoot==nullptr) return 0;
    //xét cây con bên trái
    if(x<pRoot->key)
        return countLess(pRoot->p_left,x);

    NODE*root_subtree_greater = pRoot;

    while (root_subtree_greater!=nullptr&&x>root_subtree_greater->key)
    {
        root_subtree_greater=root_subtree_greater->p_right;
    }
    int result=0;
    if (pRoot!=root_subtree_greater)
        result = countNode(pRoot) - countNode(root_subtree_greater);
    if (root_subtree_greater->key==x)
        result+= countNode(root_subtree_greater->p_left);
    return result;
}

int countGreater(NODE* pRoot, int x)
{
    if(pRoot==nullptr) return 0;
    
    int result =  countNode(pRoot) - countLess(pRoot,x);
    //nếu có x trong cây->giảm 1 đơn vị
    if(Search(pRoot,x)!=nullptr) result--;
    return result;
}

bool isPerfectIncrease(const vector<int>&v)
{   
    int len = v.size();
    for (int i =0;i<len;i++)
    {
        if (i>0&&v[i]<=v[i-1])
            return false;
    }
    return true;
}
void LNR_AUX(NODE*pRoot, vector<int>&res)
{
    if (pRoot==nullptr)    return;
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
bool isBST(NODE* pRoot)
{
    vector<int>tree_to_vector = LNR(pRoot);
    return isPerfectIncrease(tree_to_vector);
}
bool isFullBST(NODE* pRoot)
{
    if (pRoot==nullptr) return true;
    //nếu là lá
    if (pRoot->p_left == nullptr && pRoot->p_right == nullptr)
        return true;
    // Nếu có đủ hai con
    if (pRoot->p_left != nullptr && pRoot->p_right != nullptr)
        return isFullBST(pRoot->p_left) && isFullBST(pRoot->p_right);
    //Nếu có 1 con
    return false;
}
