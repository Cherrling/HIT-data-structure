#include <iostream>
#include <stack>
#include <string>

using namespace std;

#include "stack"
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
    BT.create("A(B(D,E(G,)),C(,F))#");
    BT.PrintTree();
    return 0;
}
