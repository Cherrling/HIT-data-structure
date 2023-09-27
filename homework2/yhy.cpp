#include <iostream>
using namespace std;
#include <queue>
#include "stack"
//二叉树

//结点类型
template<typename T>
struct BinTreeNode {
    T data;                                                                                                        //结点中存储的数据
    BinTreeNode<T> *leftChild, *rightChild;                                                                        //左子树和右子树
    BinTreeNode(T x) : data(x), leftChild(nullptr), rightChild(nullptr) {} //带默认值的有参构造参数
};

//二叉树类
template<typename T>
class BinaryTree {
private:
    BinTreeNode<T> *root; //根节点
    T RefValue;           //数据输入停止的标志，需要一个构造函数

public:

//==========二叉树构造与析构==========//

    //构造函数
    BinaryTree() : root(nullptr) {}

    //指定结束标志的构造函数
    BinaryTree(T value) : RefValue(value), root(nullptr) {}

    //析构函数
    ~BinaryTree() { Destroy(); }

//==========二叉树的创建==========//

    //使用广义表创建二叉树，以'#'字符代表结束，如A(B(D,E(G,)),C(,F))#
    void CreateBinTree() {
        stack<BinTreeNode<T> *> s;//用栈来辅助记录二叉树的当前父节点，以方便返回上一级父节点
        BinTreeNode<T> *p;//p记录当前创建的节点
        T ch;
        int isLeft = 0;
        cin >> ch;//读取cin流中的第一个字符，防止进入循环时置空
        while (ch != RefValue) {//如果不是终止符，循环判断
            switch (ch) {
                case '(': //左括号时当前数据（父节点）压入栈，并在下一轮循环时进入左子树
                    s.push(p);
                    isLeft = 1;
                    break;
                case ')': //右括号时弹出栈顶的数据，退出子树，栈顶变为父节点
                    s.pop();
                    break;
                case ',': //，时进入右子树
                    isLeft = 2;
                    break;
                default :
                    p = new BinTreeNode(ch);
                    if (root == nullptr) {
                        root = p;
                    } else if (isLeft == 1) {
                        s.top()->leftChild = p;
                    } else {
                        s.top()->rightChild = p;
                    }
            }
            cin >> ch;
        }
    }

    //前序遍历创建二叉树(前序遍历的应用)，用#表示空结点，如ABC##DE#G##F###
    void CreateBinTree_PreOrder(BinTreeNode<T> *&BT) {
        T ch;
        cin >> ch;
        if (ch == RefValue) {
            BT = nullptr;
            return;
        }
        BT = new BinTreeNode(ch);
        if (BT == nullptr) {
            cerr << "空间分配失败" << endl;
            exit(-1);
        }
        CreateBinTree_PreOrder(BT->leftChild);
        CreateBinTree_PreOrder(BT->rightChild);
    }

    void CreateBinTree_PreOrder() { CreateBinTree_PreOrder(root); }

//==========二叉树的遍历==========//

    //先序遍历（递归）
    void PreOrder(BinTreeNode<T> *BT) {
        if (BT) {
            cout << BT->data << " ";
            PreOrder(BT->leftChild);
            PreOrder(BT->rightChild);
        }
    }

    void PreOrder() {
        PreOrder(root);
        cout << endl;
    }

    //中序遍历(递归)
    void InOrder(BinTreeNode<T> *BT) {
        if (BT) {
            PreOrder(BT->leftChild);
            cout << BT->data << " ";
            PreOrder(BT->rightChild);
        }
    }

    void InOrder() { InOrder(root); }

    //后序遍历（递归）
    void PostOrder(BinTreeNode<T> *BT) {
        if (BT) {
            PreOrder(BT->leftChild);
            PreOrder(BT->rightChild);
            cout << BT->data << " ";
        }
    }

    void PostOrder() { cout<<"后续遍历"<<endl;PostOrder(root);}

    //先序遍历(非递归)
    void PreOrder_NoRecurve() {
    cout<<"先序非递归遍历："<<endl;
        stack<BinTreeNode<T> *> s;
        BinTreeNode<T> *BT;
        BT = root;
        if (s.empty()) {
            s.push(nullptr);//这样做的好处是，到最后BT会变成栈底的nullptr，循环只需要一个条件，并且防止越界。如果检查栈是否为空，则一开始栈是空的，很麻烦。
        }
        while (BT) {
            cout << BT->data << ' ';
            if (BT->rightChild) {
                s.push(BT->rightChild);
            }
            if (BT->leftChild) {
                BT = BT->leftChild;
            } else {
                BT = s.top();
                s.pop();
            }
        }
        cout << endl;

    }

    //中序遍历(非递归)
    void InOrder_NoRecurve() {
    cout << "中序非递归遍历："<<endl;
        stack<BinTreeNode<T> *> s;
        BinTreeNode<T> *BT;
        BT = root;
        do {
            while (BT) {
                s.push(BT);
                BT = BT->leftChild;
            }
            if (!s.empty())//为什么不能用!BT
            {
                BT = s.top();
                cout << BT->data << ' ';
                s.pop();
                BT = BT->rightChild;
            }

        } while (!s.empty() || BT);
//        s.push(nullptr);
//        while(BT){//不能用while(BT)，如果是叶节点，就直接退出去了。必须同时栈也空才能退
//
//            while (BT) {
//                s.push(BT);
//                BT = BT->leftChild;
//            }
//            if (!BT) {
//                BT = s.top();
//                cout << BT->data << ' ';
//                s.pop();
//                BT = BT->rightChild;
//            }
//        }不能这样的原因是，如果push(nullptr)，此时在最后叶节点处，你需要回到栈顶元素，而此时如果栈是空的，就可以结束了，所以栈空不空和结不结束直接相关。如果压一个
//        null进去，自找麻烦，不知道空不空。
    }

    //后序遍历(非递归)
    void PostOrder_NoRecurve() {
        cout<<"后序非递归遍历："<< endl;
        stack<BinTreeNode<T> *> s;
        s.push(root);   //先把根放入栈中，方便后面用栈空来判定结束，因为根一定最后一个弹出
        BinTreeNode<T> *lastPop = nullptr;
        do {
            while (s.top()->leftChild != nullptr)    //遍历到最左节点
            {
                s.push(s.top()->leftChild);
            }
            while (!s.empty())   //这个循环的作用是将所有的右分枝遍历完，弹栈至最前面节点，如右斜树
            {
                if (lastPop == s.top()->rightChild || s.top()->rightChild == nullptr)
                    //当前节点左右子树都遍历完｜｜为右叶子节点，即右子树遍历完成
                {
                    cout << s.top()->data << ' ';   //输出弹出当前栈顶数据并lastPop暂存
                    lastPop = s.top();
                    s.pop();
                } else if (s.top()->rightChild != nullptr) //右子树不为空，进入右子树
                {
                    s.push(s.top()->rightChild);
                    break;  //进入右子树后开始遍历右子树中的左子树
                }
            }
        } while (!s.empty());
    }

    //层次遍历(非递归)
    void LevelOrder()
    {
        BinTreeNode<T> *p = root;
        queue<BinTreeNode<T>*> Q;
        Q.push(p);
        BinTreeNode<T>* t;
        while(!Q.empty())
        {
            t = Q.front();
            Q.pop();
            cout << t->data << " ";
            if (t->leftChild != nullptr)
            {
                Q.push(t->leftChild);
            }
            if (t->rightChild != nullptr)
            {
                Q.push(t->rightChild);
            }
        }
    }

//==========获取结点==========//

    //获取二叉树的根节点
    BinTreeNode<T> *getRoot() const {
        return root;
    }

    //获取current结点的父节点
    BinTreeNode<T> *Parent(BinTreeNode<T> *current) {
        return (root == NULL || root == current) ? NULL : Parent(root, current); //如果没有根节点或current结点就是root结点，就没有父节点
    }

    //获取current结点的左结点
    BinTreeNode<T> *LeftChild(BinTreeNode<T> *current) {
        return (current != NULL) ? current->leftChild : NULL;
    }

    //获取current结点的右结点
    BinTreeNode<T> *RightChild(BinTreeNode<T> *current) {
        return (current != NULL) ? current->rightChild : NULL;
    }

//==========成员函数==========//

    //销毁函数
    void Destroy(BinTreeNode<T> *&BT)    //使用后序递归销毁
    {
        if (BT != nullptr) {
            Destroy(BT->leftChild);
            Destroy(BT->rightChild);
            delete BT;
            BT = nullptr;
        }
    }
    void Destroy(){Destroy (root);}

    //拷贝二叉树(前序遍历的应用)
    BinaryTree(BinaryTree<T> &s) {
        root = Copy(s.getRoot());
    }

    //判断两颗二叉树是否相等(前序遍历的应用)
    bool operator==(BinaryTree<T> &s) {
        return (equal(this->getRoot(), s.getRoot()));
    }

    //计算二叉树的结点的个数(后序遍历的应用)
    int Size() { return Size(root); }

    //计算二叉树的高度（后序遍历的应用）
    int Height() { return Height(root); }

    //判断二叉树是否为空
    bool Empty() { return (root == NULL) ? true : false; }

    //以广义表的形式输出二叉树(前序遍历的应用)
    void PrintBinTree() { PrintBinTree(root); }

    //以图形化输出二叉树
    void PrintTree_Graphics(BinTreeNode<T> *n, bool left, string const &indent)//用递归的方法图形化输出
    {
        if (n->rightChild) {
            PrintTree_Graphics(n->rightChild, false, indent + (left ? "|     " : "      "));
        }
        cout << indent;
        cout << (left ? '\\' : '/');
        cout << "-----";
        cout << n->data << endl;
        if (n->leftChild) {
            PrintTree_Graphics(n->leftChild, true, indent + (left ? "      " : "|     "));
        }
    }

    void PrintTree_Graphics() {
        if (root->rightChild) {
            PrintTree_Graphics(root->rightChild, false, "");
        }
        cout << root->data << endl;
        if (root->leftChild) {
            PrintTree_Graphics(root->leftChild, true, "");
        }
    }
};


int main() {
    BinaryTree<char> BT('#');
//    BT.CreateBinTree();
    BT.CreateBinTree_PreOrder();
    BT.PrintTree_Graphics();
//    BT.PreOrder();
    BT.PreOrder_NoRecurve();
    BT.InOrder_NoRecurve();
    return 0;
}

