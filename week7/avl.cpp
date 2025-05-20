#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct NODE{
    int key;
    NODE* p_left;
    NODE* p_right;
    int height;
};

NODE* createNode(int data)
{
    NODE*new_NODE = new NODE;
    new_NODE->key = data;
    new_NODE->p_left = nullptr;
    new_NODE->p_right = nullptr;
    new_NODE->height = 0;
    return new_NODE;
}
int height(NODE *n) { 
    if (n == nullptr) 
        return -1; 
    return n->height; 
} 

//xoay phải tại a
NODE *rightRotate(NODE *a) { 
    NODE *b = a->p_left; 
    a->p_left = b->p_right; 
    b->p_right = a;

    a->height = 1 + max(height(a->p_left),height(a->p_right));
    b->height = 1 + max(height(b->p_left),height(b->p_right));

    return b;
} 

// xoay trái tại a
NODE *leftRotate(NODE *a) { 
    NODE *b = a->p_right;
    a->p_right = b->p_left;
    b->p_left = a; 

    a->height = 1 + max(height(a->p_left),height(a->p_right)); 
    b->height = 1 + max(height(b->p_left),height(b->p_right)); 

    // Return new root 
    return b; 
}
//Xoay trái-phải tại a
NODE *leftRightRotate(NODE *a) { 
    a->p_left = leftRotate(a->p_left);
    return rightRotate(a);
} 
//Xoay phải-trái tại a
NODE* rightLeftRotate(NODE*a)
{
    a->p_right = rightRotate(a->p_right);
    return leftRotate(a);
}

int getBalance(NODE* p) {
    return p ? height(p->p_left) - height(p->p_right) : 0;
}

void Insert(NODE*& pRoot, int x) {
    if (!pRoot) {
        pRoot = createNode(x);
        return;
    }

    if (x < pRoot->key)
        Insert(pRoot->p_left, x);
    else if (x > pRoot->key)
        Insert(pRoot->p_right, x);
    else
        return; // đã tồn tại, bỏ qua
    //cập nhật chiều cao
    pRoot->height = 1 + max(height(pRoot->p_left), height(pRoot->p_right));
    //lấy hệ số cân bằng 
    int balance = getBalance(pRoot);

    // Left Left
    if (balance > 1 && x < pRoot->p_left->key)
        pRoot = rightRotate(pRoot);

    // Right Right
    else if (balance < -1 && x > pRoot->p_right->key)
        pRoot = leftRotate(pRoot);

    // Left Right
    else if (balance > 1 && x > pRoot->p_left->key) {
        pRoot = leftRightRotate(pRoot);
    }

    // Right Left
    else if (balance < -1 && x < pRoot->p_right->key) {
        pRoot = rightLeftRotate(pRoot);
    }
}

NODE* mostLeftNode(NODE* node) {
    NODE* current = node;
    while (current && current->p_left != nullptr)
        current = current->p_left;
    return current;
}


void Remove(NODE* &pRoot, int x) {
    if (pRoot == nullptr) return;

    if (x < pRoot->key)
        Remove(pRoot->p_left, x);
    else if (x > pRoot->key)
        Remove(pRoot->p_right, x);
    else {
        // Node cần xóa
        if (pRoot->p_left == nullptr || pRoot->p_right == nullptr) {
            NODE* temp = (pRoot->p_left) ? pRoot->p_left : pRoot->p_right;
            if (temp == nullptr) {
                // Không có con
                temp = pRoot;
                pRoot = nullptr;
                delete temp;  
            } else {
                // Có 1 con
                NODE* delNode = pRoot;
                pRoot = temp;
                delete delNode;
            }
        } else {
            // Node có 2 con
            NODE* temp = mostLeftNode(pRoot->p_right);
            pRoot->key = temp->key;
            Remove(pRoot->p_right, temp->key);
        }
    }

    if (pRoot == nullptr) return;

    // Cập nhật height
    pRoot->height = 1 + std::max(height(pRoot->p_left), height(pRoot->p_right));

    // Kiểm tra balance
    int balance = getBalance(pRoot);

    // Left Left
    if (balance > 1 && getBalance(pRoot->p_left) >= 0)
        pRoot = rightRotate(pRoot);

    // Left Right
    else if (balance > 1 && getBalance(pRoot->p_left) < 0) {
        pRoot->p_left = leftRotate(pRoot->p_left);
        pRoot = rightRotate(pRoot);
    }

    // Right Right
    else if (balance < -1 && getBalance(pRoot->p_right) <= 0)
        pRoot = leftRotate(pRoot);

    // Right Left
    else if (balance < -1 && getBalance(pRoot->p_right) > 0) {
        pRoot->p_right = rightRotate(pRoot->p_right);
        pRoot = leftRotate(pRoot);
    }
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

bool isAVL(NODE* pRoot) {
    if (pRoot == nullptr) return true;

    int balance = getBalance(pRoot);
    if (balance > 1 || balance < -1) return false;

    if (!isBST(pRoot)) return false;

    return isAVL(pRoot->p_left) && isAVL(pRoot->p_right);
}

void InsertArray(NODE*& pRoot, const vector<int>& arr) {
    for (int x : arr) {
        Insert(pRoot, x);
    }
}
