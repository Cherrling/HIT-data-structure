#include <iostream>
#include <stack>
#include <string>

using namespace std;

#include "stack"

class TreeNode {
public:
    int data;
    TreeNode* left;
    TreeNode* right;

    // 构造函数
    TreeNode(int val)
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
    BTree(int val)
    {
        root = new TreeNode(val);
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

    void create(){
        stack<TreeNode> father;
        string str;
        for (int i=0; i<str.length(); i++) {
            i++;
            if (str[i]=='(') {
                
            }
        }        
    
    }


    TreeNode* buildTreeFromGeneralizedList(const std::string& str, int& index) {
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
    
    return 0;
}
