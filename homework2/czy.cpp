#include <iostream>
#include <stack>
#include <iomanip>
#include <queue>
#include <unordered_map>

using namespace std;


template<typename T>
class Node {
public:
    T val;
    Node<T> *left;
    Node<T> *right;

    explicit Node(T val) {
        this->val = val;
        this->left = nullptr;
        this->right = nullptr;
    }

    explicit Node() {
        this->val = ' ';
        this->left = nullptr;
        this->right = nullptr;
    }
};

template<typename T>
class BinaryTree {
private:
    Node<T> *head;
    T forEnd = '#';

public:
    explicit BinaryTree() : head(nullptr) {}

    //Create以#作为结束标识
    void CreateTree() {
        stack<Node<T> *> s;//记录二叉树节点
        Node<T> *curr;//记录当前节点
        string str = "A(B(D,E(G,)),C(,F))#";
        //  cin >> str;
        int i = 0;
        T temp = str[i];
        bool isLeft = true;

        //(是进入左节点的标识  ,是进入右节点的标识   )是当前子树构建完毕的标识 #是结束的标识
        while (temp != forEnd) {
            switch (temp) {
                case '(':
                    s.push(curr);//读到括号，push进括号前的指针
                    isLeft = true;
                    break;
                case ')':
                    s.pop();
                    break;
                case ',':
                    isLeft = false;
                    break;
                default:
                    curr = new Node<T>(temp);
                    if (head == nullptr) {
                        head = curr;
                    } else if (isLeft) {
                        s.top()->left = curr;
                    } else if (!isLeft) {
                        s.top()->right = curr;
                    }
            }
            temp = str[++i];
        }
    }

    //前序遍历创建二叉树(前序遍历的应用)，用#表示空结点，如ABC##DE#G##F###
    //ATTENTION: 对一个空指针而言 是需要构建的
    //0123456
    //AB##C##
    void CreateTree(string str) {
        //非递归实现   //递归实现的过程当中暂时没想到怎么当字符串不是从cin读入的时候的解决办法
        int i = 0;
        stack<Node<T> *> s;//记录二叉树节点

        T temp = str[i];
        bool isLeft = true;
        if (str[i] == this->forEnd) {
            return;
        }
        Node<T> *curr = head = new Node<T>(temp);//记录当前节点
        Node<T> *lastPop;
        s.push(curr);
        temp = str[++i];
        while (i < str.length()) {

            switch (temp) {
                case '#':
                    isLeft = false;

                    if (!s.empty()) {
                        curr = s.top();
                        lastPop = s.top();
                        s.pop();
                    }
                    break;
                default:
                    if (isLeft && !s.empty()) {
                        curr->left = new Node<T>(temp);
                        s.push(curr->left);
                        curr = s.top();
                    } else if (!isLeft && !s.empty()) {
                        curr->right = new Node<T>(temp);
                        s.push(curr->right);
                        curr = s.top();
                        isLeft = true;
                    } else if (isLeft && s.empty()) {
                        lastPop->left = new Node<T>(temp);
                        s.push(lastPop->left);
                        curr = s.top();
                    } else if (!isLeft && s.empty()) {
                        lastPop->right = new Node<T>(temp);
                        s.push(lastPop->right);
                        curr = s.top();
                        isLeft = true;
                    }
            }
            i++;
            temp = str[i];
        }
    }

    //以图形化输出二叉树 中序（但先进右子树）
    void PrintTree(Node<T> *n, bool left, string const &indent) {
        if (n->right) {
            PrintTree(n->right, false, indent + (left ? "|     " : "      "));
        }
        cout << indent;
        //判断当前节点为左节点还是右节点。然后使用/或者\表示左右节点
        cout << (left ? '\\' : '/');
        //打印一个当前节点的数据 一定是序号换行的
        cout << "-----" << n->val << endl;
        if (n->left) {
            PrintTree(n->left, true, indent + (left ? "      " : "|     "));
        }
    }

    void PrintTree() {
        cout << "图形化打印二叉树" << endl;
        cout << "________________\n" << endl;
        if (head->right) {
            PrintTree(head->right, false, "");
        }
        cout << head->val << endl;
        if (head->left) {
            PrintTree(head->left, true, "");
        }
        cout << "________________\n" << endl;
    }

    //前序遍历 递归实现
    void Pre(Node<T> *curr) {
        if (curr == nullptr) {
            return;
        }
        cout << curr->val << " ";
        Pre(curr->left);
        Pre(curr->right);
    }

    //中序遍历 递归实现
    void In(Node<T> *curr) {
        if (curr == nullptr) {
            return;
        }
        In(curr->left);
        cout << curr->val << " ";
        In(curr->right);
    }

    //后序遍历 递归实现
    void Post(Node<T> *curr) {
        if (curr == nullptr) {
            return;
        }
        Post(curr->left);
        Post(curr->right);
        cout << curr->val << " ";
    }


    //前序遍历 迭代实现 规定弹出即打印
    // 栈保留递归路线，并且栈顶为上一个访问的节点
    // 整个递归方式还是可以理解的，确保在每一个子树的范围内都是头节点到左孩子到右孩子，所以在不断向下的过程中尽可能的
    // 将上层的右孩子压入栈中，能保留右孩子的出栈顺序
    void PreNoRecursive() {
        if (head == nullptr) return;

        stack<Node<T> *> s;
        Node<T> *curr = head;
        s.push(curr);

        while (!s.empty()) {
            curr = s.top();
            s.pop();
            cout << curr->val << " ";
            if (curr->right != nullptr) {
                s.push(curr->right);
            }
            if (curr->left != nullptr) {
                s.push(curr->left);
            }
        }
    }

    //后续遍历 迭代实现
    //用了一个比较奇怪的想法，后续遍历就是让每个子树都是左右根的顺序来遍历
    //按上面前序的方法，改成中右左，也就是对每个子树来说都是这个顺序，并且一定是到最右的子树，这和后续的最左子树恰好对应左右中
    //完全相反就是我们需要的东西
    void PostNoRecursive2() {
        if (head == nullptr) return;

        stack<Node<T> *> s;
        stack<Node<T> *> help;
        Node<T> *curr = head;
        s.push(curr);

        while (!s.empty()) {
            curr = s.top();
            help.push(curr);
            s.pop();//因为原本弹出打印，我们只要把全部压入到另一个栈中，反向打印，任务就完成了
            //  cout << curr->val << " ";
            if (curr->left != nullptr) {
                s.push(curr->left);
            }
            if (curr->right != nullptr) {
                s.push(curr->right);
            }
        }
        while (!help.empty()) {
            Node<T> *n = help.top();
            help.pop();
            cout << n->val << " ";
        }
    }

    //后续遍历 迭代实现
    //较为正常的实现方式
    void PostNoRecursive() {
        if (head == nullptr) return;

        stack<Node<T> *> s;
        Node<T> *curr = head;
        s.push(curr);
        Node<T> *help = head;
        while (!s.empty()) {
            curr = s.top();
            //右边进过就别进左边了  毕竟是先进的左边
            //所有的所有都是进栈然后才打印的
            if (curr->left != nullptr && curr->left != help && curr->right != help) {
                curr = curr->left;
                s.push(curr);
            } else if (curr->right != nullptr && curr->right != help) {
                curr = curr->right;
                s.push(curr);
            } else {
                help = s.top();
                s.pop();
                cout << help->val << " ";
            }
        }
    }

    //中序遍历 迭代实现
    // 先左 再中 再右
    // 左空 则pop根 打印根 然后进右，这样子栈顶是子树根的父节点
    void InNoRecursive() {
        stack<Node<T> *> s;
        Node<T> *curr = head;
        if (head == nullptr) return;
        while (!s.empty() || curr != nullptr) {
            //我们写递归的本质是考虑当前部分 和 当前部分 的父部分
            //当前部分能否各司其职，当前部分执行完 能否回到父部分继续执行，这是我们最需要关心的东西
            //左树全部进栈，在左树的每个节点上 依次处理好各自的右子树 每次弹栈的时候都回到了右子树的位置  进右子树的时候，子树根节点已经弹出打印了

            //pop总是pop掉一个左树节点，然后就剩了这个左树节点的父节点，于是这时进入这个左树节点的右树。完成右树（假设右树为空，最简单的情况），
            //当前这个左树节点的父节点的左子树完成，pop回到这个父节点，继续进行其他步骤，这会到curr为空 栈空为结束标识
            if (curr != nullptr) {
                s.push(curr);
                curr = curr->left;//无论如何都是先进左树，左树无法遍历之后进入else，直接开始pop打印
            } else {
                curr = s.top();
                s.pop();
                cout << curr->val << " ";
                curr = curr->right;
                //接连两次进else语句就意味着
            }
        }
    }

    //判断是否为 完整二叉树
    //判断也就是基于当前空指针后面有没有一个实的
    bool isCompleteBinaryTree() {
        queue<Node<T> *> q;
        Node<T> *curr = head;
        q.push(curr);
        while (!q.empty()) {
            curr = q.front();
            q.pop();
            if (curr == nullptr && !q.empty()) {
                if (q.front() != nullptr) {
                    return false;
                }
            } else if (curr != nullptr) {
                q.push(curr->left);
                q.push(curr->right);
            }
        }
        return true;
    }

    //计算二叉树宽度
    //使用哈希表
    int getTreeWidth() {
        if (head == nullptr) {
            return -1;
        }
        //层序遍历 通过hashmap来保存每个节点的 层数
        Node<T> *curr = head;
        //hashmap 第一个参数保存节点， 第二个参数保存当前节点的层数
        unordered_map<Node<T> *, int> levelmap;
        levelmap.insert({curr, 1});
        queue<Node<T> *> q;
        q.push(curr);
        int currLevel = 1;//当前层树
        int currLevelWidth = 0;//当前层宽度
        int maxWidth = 1;//已遍历层最大宽度
        while (!q.empty()) {
            curr = q.front();
            q.pop();
            int currNodeLevel = levelmap.at(curr);// 当前节点所在层
            if (curr->left != nullptr) {
                q.push(curr->left);
                levelmap.insert({curr->left, currNodeLevel + 1});
            }
            if (curr->right != nullptr) {
                q.push(curr->right);
                levelmap.insert({curr->right, currNodeLevel + 1});
            }
            if (currNodeLevel == currLevel) {
                currLevelWidth++;
            } else {
                maxWidth = max(maxWidth, currLevelWidth);
                currLevel++;
                currLevelWidth = 1;
            }
        }
        maxWidth = max(maxWidth, currLevelWidth);
        return maxWidth;
    }

    //计算二叉树宽度
    //不使用哈希表
    //在每一层 使用一个end节点标注下一层的 最右侧节点位置
    int getTreeWidth2() {
        if (head == nullptr) {
            return -1;
        }
        Node<T> *curr = head;
        queue<Node<T> *> q;
        q.push(curr);
        Node<T> *nextEnd = nullptr;//下一层最右节点
        Node<T> *currLevelEnd = head;//当前层最右节点
        int maxWidth = 1;
        int currLevelWidth = 0;
        while(!q.empty()) {
            curr = q.front();
            q.pop();
            if(curr->left != nullptr) {
                q.push(curr->left);
                nextEnd = curr->left;//调整最右
            }
            if(curr->right) {
                q.push(curr->right);
                nextEnd = curr->right;
            }
            currLevelWidth++;//不能在上面那两个语句内，上面两个语句是下一行
            if(curr == currLevelEnd) {
                maxWidth = max(maxWidth, currLevelWidth);
                currLevelWidth = 0;
                currLevelEnd = nextEnd;
            }
        }
        return maxWidth;//不需要做while外处理，每次比较都是当前行的操作
    }

    Node<T> *getHead() {
        return this->head;
    }

    ~BinaryTree() {
        destroy(head);
    }

    void destroy(Node<T> *node) {
        if (node != nullptr) {
            destroy(node->left);
            destroy(node->right);
            delete node;
        }
    }
};

int main() {
    BinaryTree<char> biTree;
    biTree.CreateTree();
    biTree.PrintTree();

    cout << "递归前序:";
    biTree.Pre(biTree.getHead());
    cout << endl;
    cout << "非递归前序:";
    biTree.PreNoRecursive();

    cout << endl;
    cout << "递归中序:";
    biTree.In(biTree.getHead());
    cout << endl;
    cout << "非递归中序:";
    biTree.InNoRecursive();

    cout << endl;
    cout << "递归后序:";
    biTree.Post(biTree.getHead());
    cout << endl;
    cout << "非递归后序1:";
    biTree.PostNoRecursive();
    cout << endl;
    cout << "非递归后序2:";
    biTree.PostNoRecursive2();

    BinaryTree<char> biTree3;
    biTree3.CreateTree("ABD#G###CE###");
    cout << endl;
    biTree3.PrintTree();

    BinaryTree<char> biTree4;
    biTree4.CreateTree("ABD#G##M##CE###");
    cout << endl;
    biTree4.PrintTree();
    cout << endl;
    if (biTree4.isCompleteBinaryTree()) {
        cout << "为完整二叉树";
    } else {
        cout << "不是完全二叉树";
    }
    cout << endl;
    cout << " 树的宽度为:";
    cout << biTree4.getTreeWidth();
    cout << endl;
    cout << " 树的宽度为:";
    cout << biTree4.getTreeWidth2();
    return 0;
}