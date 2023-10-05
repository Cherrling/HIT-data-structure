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
        root = new TreeNode('#');
    }
    ~BTree() { }

    void insertNode(TreeNode* p, int lr, int val)
    {
        TreeNode* tree = new TreeNode(val);
        if (lr) {
            p->right = tree;
        } else {
            p->left = tree;
        }
    }

    void create(string str)
    {
    //A(B(D,E(G,)),C(,F))#
        stack<TreeNode*> father;
        TreeNode* curr;
        curr=root;
        for (int i = 0; i < str.length(); i++) {
            if (str[i]=='#') {
                return;
            }

            if (str[i] == '(') {
                father.push(curr);
                insertNode(curr, 0, '#');
                curr=curr->left;
            }else if (str[i]==',') {
                insertNode(father.top(), 1, '#');
                curr=father.top()->right;
            }else if (str[i]==')') {
                curr=father.top();
                father.pop();
            }else {
                curr->data=str[i];
            }
        }
    }


    void PrintTree(TreeNode *n, bool left, string const &indent) {
        if (n->right) {
            PrintTree(n->right, false, indent + (left ? "|     " : "      "));
        }
        cout << indent;
        //判断当前节点为左节点还是右节点。然后使用/或者\表示左右节点
        cout << (left ? '\\' : '/');
        //打印一个当前节点的数据 一定是序号换行的
        cout << "-----" << n->data << endl;
        if (n->left) {
            PrintTree(n->left, true, indent + (left ? "      " : "|     "));
        }
    }

    void PrintTree() {
        cout << "图形化打印二叉树" << endl;
        cout << "________________\n" << endl;
        if (root->right) {
            PrintTree(root->right, false, "");
        }
        cout << root->data << endl;
        if (root->left) {
            PrintTree(root->left, true, "");
        }
        cout << "________________\n" << endl;
    }















    TreeNode* buildTreeFromGeneralizedList(const std::string& str, int& index)
    {
        if (index >= str.length()) {
            return nullptr;
        }

        // 跳过左括号
        index++;

        // 处理元素或子表
        if (str[index] != '(') {
            // 读取元素值
            int val = 0;
            while (isdigit(str[index])) {
                val = val * 10 + (str[index] - '0');
                index++;
            }
            return new TreeNode(val);
        } else {
            // 创建当前节点
            TreeNode* node = new TreeNode(-1); // -1 表示空节点
            index++; // 跳过左括号

            // 构建左子树
            node->left = buildTreeFromGeneralizedList(str, index);

            // 构建右子树
            node->right = buildTreeFromGeneralizedList(str, index);

            // 跳过右括号
            index++;

            return node;
        }
    }
};

int main()
{
    BTree BT;
    BT.create("A(B(D,E(G,)),C(,F))#");
    BT.PrintTree();
    return 0;
}
