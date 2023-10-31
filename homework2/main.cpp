#include <iostream>
#include <stack>
#include <string>
#include <queue>
#include <vector>

using namespace std;

// A(B(D,E(G,)),C(,F))#
class TreeNode {
public:
    char data;
    TreeNode* left;
    TreeNode* right;

    // 构造函数
    TreeNode(char val)
        : data(val)
        , left(nullptr)
        , right(nullptr)
    {
    }
};

class BTree {
private:
    TreeNode* root;

public:
    BTree()
    {
        // root = new TreeNode('#');
        root = nullptr;
    }
    void destroy(TreeNode* node)
    {
        if (node != nullptr) {
            destroy(node->left);
            destroy(node->right);
            delete node;
        }
    }
    ~BTree()
    {
        destroy(root);
    }

    TreeNode* getroot()
    {
        return root;
    }

    // void create(string str)
    // {
    // //A(B(D,E(G,)),C(,F))#
    //     stack<TreeNode*> father;
    //     TreeNode* curr;
    //     curr=root;
    //     for (int i = 0; i < str.length(); i++) {
    //         if (str[i]=='#') {
    //             return;
    //         }

    //         if (str[i] == '(') {
    //             father.push(curr);
    //             insertNode(curr, 0, '#');
    //             curr=curr->left;
    //         }else if (str[i]==',') {
    //             insertNode(father.top(), 1, '#');
    //             curr=father.top()->right;
    //         }else if (str[i]==')') {
    //             curr=father.top();
    //             father.pop();
    //         }else {
    //             curr->data=str[i];
    //         }
    //     }
    // }
    void create(string str)
    {
        // A(B(D,E(G,)),C(,F))#
        stack<TreeNode*> father;
        TreeNode* curr;
        bool isleft = 1;
        curr = root;
        for (int i = 0; i < str.length(); i++) {
            if (str[i] == '#') {
                return;
            }

            if (str[i] == '(') {
                father.push(curr);
                isleft = 1;

            } else if (str[i] == ',') {
                isleft = 0;
            } else if (str[i] == ')') {
                curr = father.top();
                father.pop();
            } else {
                curr = new TreeNode(str[i]);
                if (root == nullptr) {
                    root = curr;
                } else if (isleft) {
                    father.top()->left = curr;
                } else {
                    father.top()->right = curr;
                }
            }
        }
    }

    void pre_create(TreeNode*& curr, string& str, int& index)
    {
        // ABD#G###CE###
        if (index >= str.length()) {
            return;
        }
        if (str[index] == '#') {
            curr = nullptr;
            index++;
        } else {

            curr = new TreeNode(str[index]);
            index++;
            pre_create(curr->left, str, index);
            pre_create(curr->right, str, index);
        }
    }
    void pre_create(string str)
    {
        int index = 0;
        pre_create(root, str, index);
    }

    void pre(TreeNode* curr)
    {
        if (curr == nullptr) {
            return;
        }
        cout << curr->data << " ";
        pre(curr->left);
        pre(curr->right);
    }
    void in(TreeNode* curr)
    {
        if (curr == nullptr) {
            return;
        }
        in(curr->left);
        cout << curr->data << " ";
        in(curr->right);
    }
    void post(TreeNode* curr)
    {
        if (curr == nullptr) {
            return;
        }
        post(curr->left);
        post(curr->right);
        cout << curr->data << " ";
    }

    void pre_no_rec()
    {
        TreeNode* curr = root;
        stack<TreeNode*> s;
        while (!(curr == nullptr && s.empty())) {
            while (curr != nullptr) {
                cout << curr->data << " ";
                s.push(curr);
                curr = curr->left;
            }
            if (!s.empty()) {
                curr = s.top();
                s.pop();
                curr = curr->right;
            }
        }
    }

    void in_no_rec()
    {
        TreeNode* curr = root;
        stack<TreeNode*> s;
        while (!(curr == nullptr && s.empty())) {
            while (curr != nullptr) {
                s.push(curr);
                curr = curr->left;
            }
            if (!s.empty()) {
                curr = s.top();
                cout << curr->data << " ";
                s.pop();
                curr = curr->right;
            }
        }
    }

    void post_no_rec()
    {
        TreeNode* curr = root;
        TreeNode* lastvisited = nullptr;
        stack<TreeNode*> s;
        // s.push(root);
        while (curr != nullptr || !s.empty()) {
            while (curr != nullptr) {
                s.push(curr);
                curr = curr->left;
            }

            if (s.top()->right == nullptr || s.top()->right == lastvisited) {
                cout << s.top()->data << " ";
                lastvisited = s.top();
                s.pop();
            } else {
                curr = s.top()->right;
            }
        }
    }

    void up_down(){
        queue<TreeNode*> q;
        TreeNode* curr=root;
        q.push(curr);
        while (!q.empty()) {
            curr=q.front();
            q.pop();
                cout<<curr->data<<" ";
            if (curr->left!=nullptr) {
                q.push(curr->left);
            }
            if (curr->right!=nullptr) {
                q.push(curr->right);
            }
        }
    
    
    }

bool isCompleteBinaryTree(TreeNode* root) {
    if (root == nullptr) {
        return true;
    }

    std::queue<TreeNode*> q;
    q.push(root);

    bool nonFullNodeFound = false; // 用于标记是否找到了不满的节点

    while (!q.empty()) {
        TreeNode* current = q.front();
        q.pop();

        // 如果找到了不满的节点，并且当前节点不是叶子节点，那么不是完全二叉树
        if (nonFullNodeFound && (current->left || current->right)) {
            return false;
        }

        // 如果当前节点只有左孩子，没有右孩子，那么标记已找到不满的节点
        if (current->left && !current->right) {
            nonFullNodeFound = true;
        }

        // 将孩子节点入队
        if (current->left) {
            q.push(current->left);
        }
        if (current->right) {
            q.push(current->right);
        }
    }

    // 如果遍历完所有节点，没有找到不满的节点，则是完全二叉树
    return true;
}

    void calc_width()
    {
        int x=0;
        vector<int>width;
        width.push_back(0);
        queue<TreeNode*> q;
        TreeNode* curr=root;
        q.push(curr);
        q.push(nullptr);
        while (!q.empty()) {
            if (q.front()==nullptr) {
                q.pop();
                if (q.empty()) {
                    break;
                }
                q.push(nullptr);
                x++;
                width.push_back(0);
                continue;
            }
            curr=q.front();
            q.pop();
            cout<<curr->data<<" ";
            width[x]++;
            if (curr->left!=nullptr) {
                q.push(curr->left);
            }
            if (curr->right!=nullptr) {
                q.push(curr->right);
            }
        }
        for (int a : width) {
        cout<<endl;
            cout<<a<<" ";
        }
    }





    void PrintTree(TreeNode* n, bool left, string const& indent)
    {
        if (n->right) {
            PrintTree(n->right, false, indent + (left ? "|     " : "      "));
        }
        cout << indent;
        // 判断当前节点为左节点还是右节点。然后使用/或者\表示左右节点
        cout << (left ? '\\' : '/');
        // 打印一个当前节点的数据 一定是序号换行的
        cout << "-----" << n->data << endl;
        if (n->left) {
            PrintTree(n->left, true, indent + (left ? "      " : "|     "));
        }
    }

    void PrintTree()
    {
        cout << "图形化打印二叉树" << endl;
        cout << "________________\n"
             << endl;
        if (root->right) {
            PrintTree(root->right, false, "");
        }
        cout << root->data << endl;
        if (root->left) {
            PrintTree(root->left, true, "");
        }
        cout << "________________\n"
             << endl;
    }
};

int main()
{
    BTree BT;
    // BT.create("A(B(D,E(G,)),C(,F))#");
    // BT.pre_create("ABD#G###CE###");
    BT.pre_create("ABDH##I##E##CF#J##G##");
    // BT.pre(BT.getroot());
    // cout << endl;
    // BT.pre_no_rec();
    // cout << endl;
    // BT.in(BT.getroot());
    // cout << endl;
    // BT.in_no_rec();
    // cout << endl;
    // BT.post(BT.getroot());
    // cout << endl;
    // BT.post_no_rec();
    // BT.up_down();
    BT.calc_width();
    BT.PrintTree();
    return 0;
}
