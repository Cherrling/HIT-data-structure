#include <bits\stdc++.h>
#include <vector>
using namespace std;

// 定义二叉树节点
struct TreeNode {
    int key;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int value)
        : key(value)
        , left(nullptr)
        , right(nullptr)
    {
    }
};

// 定义二叉搜索树类
class BinarySearchTree {
public:
    TreeNode* root;

    // 插入节点
    TreeNode* insert(TreeNode* node, int key)
    {
        if (node == nullptr) {
            return new TreeNode(key);
        }

        if (key < node->key) {
            node->left = insert(node->left, key);
        } else if (key > node->key) {
            node->right = insert(node->right, key);
        }

        return node;
    }

    // 删除节点
    TreeNode* remove(TreeNode* node, int key)
    {
        if (node == nullptr) {
            return node;
        }

        if (key < node->key) {
            node->left = remove(node->left, key);
        } else if (key > node->key) {
            node->right = remove(node->right, key);
        } else {
            if (node->left == nullptr) {
                TreeNode* temp = node->right;
                delete node;
                return temp;
            } else if (node->right == nullptr) {
                TreeNode* temp = node->left;
                delete node;
                return temp;
            }

            // 有两个子节点的情况，找到右子树中的最小节点来替换当前节点
            TreeNode* temp = findMin(node->right);
            node->key = temp->key;
            node->right = remove(node->right, temp->key);
        }

        return node;
    }

    // 查找节点
    TreeNode* search(TreeNode* node, int key, int& cnt)
    {
        if (node == nullptr || node->key == key) {
            return node;
        }
        cnt++;
        if (key < node->key) {
            return search(node->left, key, cnt);
        } else {
            return search(node->right, key, cnt);
        }
    }

    // 查找最小节点
    TreeNode* findMin(TreeNode* node)
    {
        while (node->left != nullptr) {
            node = node->left;
        }
        return node;
    }

    // 中序遍历，实现排序
    void inorderTraversal(TreeNode* node, vector<int>& num)
    {
        if (node != nullptr) {
            inorderTraversal(node->left, num );
            num.push_back(node->key);
            inorderTraversal(node->right, num);
        }
    }

public:
    BinarySearchTree()
        : root(nullptr)
    {
    }

    // 对外接口：插入节点
    void insert(int key)
    {
        root = insert(root, key);
    }

    // 对外接口：删除节点
    void remove(int key)
    {
        root = remove(root, key);
    }

    // 对外接口：查找节点
    bool search(int key, int& cnt)
    {
        return search(root, key, cnt) != nullptr;
    }

    // 对外接口：中序遍历，实现排序
    void inorderTraversal(vector<int>& num)
    {
        inorderTraversal(root, num);
        cout << endl;
    }
};
// 折半查找函数
int binarySearch(const vector<int>& arr, int target, int& cnt)
{
    int left = 0;
    int right = arr.size() - 1;

    while (left <= right) {
        cnt++;
        int mid = left + (right - left) / 2;

        if (arr[mid] == target) {
            return mid; // 找到目标值，返回索引
        } else if (arr[mid] < target) {
            left = mid + 1; // 目标值在右半部分
        } else {
            right = mid - 1; // 目标值在左半部分
        }
    }

    return -1; // 目标值不存在于数组中
}

// 生成已排序的整数序列
vector<int> generateSortedSequence(int n)
{
    vector<int> sequence;
    for (int i = 1; i <= 2048; i += 2) { // 生成奇数序列
        sequence.push_back(i);
    }
    return sequence;
}

// 打乱序列
void shuffleSequence(vector<int>& sequence)
{
    random_device rd;
    mt19937 g(rd());
    shuffle(sequence.begin(), sequence.end(), g);
}

int main()
{

    // 生成第一组测试数据：已排序的整数序列
    int n = 1024;
    vector<int> sortedSequence = generateSortedSequence(n);

    // 生成第二组测试数据：随机序列
    vector<int> randomSequence = sortedSequence; // 复制第一组数据
    shuffleSequence(randomSequence); // 打乱序列

    BinarySearchTree bst1;
    BinarySearchTree bst2;

    for (int i = 0; i < sortedSequence.size(); i++) {
        bst1.insert(sortedSequence[i]);
    }
    for (int i = 0; i < randomSequence.size(); i++) {
        bst2.insert(randomSequence[i]);
    }

    int bstsucccnt1 = 0;
    int bstfailcnt1 = 0;
    int bstsucccnt2 = 0;
    int bstfailcnt2 = 0;
    int bsucc1 = 0;
    int bfail1 = 0;
    int bsucc2 = 0;
    int bfail2 = 0;
    int cnt = 0;



    vector<int> num1;
    vector<int> num2;
    bst1.inorderTraversal(num1);
    bst2.inorderTraversal(num2);

    for (int i = 0; i < 2048; i++) {
        cnt = 0;
        if (bst1.search(i, cnt)) {
            bstsucccnt1 += cnt;
        } else {
            bstfailcnt1 += cnt;
        }
    }


    cout << "数据1: " << endl;
    cout << "BST平均查找长度: 成功 " << bstsucccnt1 / 2048 << " 失败 " << bstfailcnt1 / 2048 << endl;

    for (int i = 0; i < 2048; i++) {
        cnt = 0;
        if (bst2.search(i, cnt)) {
            bstsucccnt2 += cnt;
        } else {
            bstfailcnt2 += cnt;
        }
    }
    cout << "数据2: " << endl;
    cout << "BST平均查找长度: 成功 " << bstsucccnt2 / 2048 << " 失败 " << bstfailcnt2 / 2048 << endl;



    // for (int i=0; i<num1.size(); i++) {
    // cout<<num1[i]<<" ";
    // }
    // return 0;
    for (int i = 0; i < 2048; i++) {
        cnt = 0;
        if (binarySearch(num1, i, cnt) != -1) {
            bsucc1 += cnt;
        } else {
            bfail1 += cnt;
        }
    }
    cout << "数据1: " << endl;
    cout << "二分平均查找长度: 成功 " << bsucc1 / 2048 << " 失败 " << bfail1 / 2048 << endl;

    for (int i = 0; i < 2048; i++) {
        cnt = 0;
        if (binarySearch(num2, i, cnt) != -1) {
            bsucc2 += cnt;
        } else {
            bfail2 += cnt;
        }
    }
    cout << "数据2: " << endl;
    cout << "二分平均查找长度: 成功 " << bsucc2 / 2048 << " 失败 " << bfail2 / 2048 << endl;

    return 0;
}
 