# include<bits/stdc++.h>
# include<cmath>
# include<queue>
# include<stack>
using namespace std;

string c;
int si;

typedef struct node {
    struct node *lc;
    struct node *rc;
    char v;
}BTREE;
BTREE *root;

BTREE* CreateBT(BTREE *T)//建树
{
    // printf("%c " , s[si]);
    char ci = c[si++];
    if (ci == '#')
        return NULL;
    else
    {
        T = new node;
        T -> v = ci;
        T -> lc = CreateBT(T -> lc);
        T -> rc = CreateBT(T -> rc);
    }
    return T;
}

void PreOrder(BTREE *T)//前序递归
{
    // printf("@");
    if (T != NULL)
    {
        printf("%c " , T -> v);
        PreOrder(T -> lc);
        PreOrder(T -> rc);
    }
}

void InOrder(BTREE *T)//中序递归
{
    if (T != NULL)
    {
        InOrder(T -> lc);
        printf("%c " , T -> v);
        InOrder(T -> rc);
    }
}

void PostOrder(BTREE *T)//后序递归
{
    if (T != NULL)
    {
        PostOrder(T -> lc);
        PostOrder(T -> rc);
        printf("%c " , T -> v);
    }
}

queue <BTREE*> q;

void LevelOrder(BTREE *T)//层序递归
{
    BTREE *now;
    if (T == NULL)
        return;
    q.push(T);
    while (!q.empty())
    {
        now = q.front();
        q.pop();
        printf("%c " , now -> v);
        if (now -> lc != NULL)
            q.push(now -> lc);
        if (now -> rc != NULL)
            q.push(now -> rc);
    }
}

stack <BTREE*> s;

void _PreOrder(BTREE *T)//前序非递归
{
    while (T != NULL || !s.empty())
    {
        while (T != NULL)
        {
            printf("%c " , T -> v);
            s.push(T);
            T = T -> lc;
        }
        if (!s.empty())
        {
            T = s.top();
            s.pop();
            T = T -> rc;
        }
    }
}

void _InOrder(BTREE *T)//中序非递归
{
    while (T != NULL || !s.empty())
    {
        while (T != NULL)
        {
            s.push(T);
            T = T -> lc;
        }
        if (!s.empty())
        {
            T = s.top();
            s.pop();
            printf("%c " , T -> v);
            T = T -> rc;
        }
    }
}

stack <int> s1;

void _PostOrder(BTREE *T)//后序非递归
{
    int i = 0;
    while (T != NULL || !s.empty())
    {
        while (T != NULL)
        {
            s.push(T);
            s1.push(1);
            T = T -> lc;
        }
        while (!s.empty() && s1.top() == 2)
        {
            T = s.top();
            s.pop();
            s1.pop();
            printf("%c " , T -> v);
            if (s.empty())
                return;
        }
        if (!s.empty())
        {
            T = s.top();
            s1.pop();
            s1.push(2);
            T = T -> rc;
        }
    }
}

void CompTree(BTREE *T)//判断是否完全树
{
    while (!q.empty())
        q.pop();
    BTREE *now;
    if (T == NULL)
        return;
    q.push(T);
    while (!q.empty())
    {
        now = q.front();
        if (now -> lc == NULL && now -> rc != NULL)
        {
            cout<<"不是完全二叉树"<<endl;
            return;
        }
        q.pop();
        if (now -> lc != NULL)
            q.push(now -> lc);
        if (now -> rc != NULL)
            q.push(now -> rc);
        if ((now -> lc == NULL && now -> rc == NULL) || (now -> lc != NULL && now -> rc == NULL))
            break;
    }
    while (!q.empty())
    {
        now = q.front();
        q.pop();
        if (now -> rc != NULL || now -> lc != NULL)
        {
            cout<<"不是完全二叉树"<<endl;
            return;
        }
    }
    cout<<"是完全二叉树"<<endl;
    return;
}

void CalWidth(BTREE *T)//计算宽度
{
    while (!q.empty())
        q.pop();
    BTREE *now;
    int ans = 0;
    if (T ==NULL)
        return;
    q.push(T);
    int len;
    while (!q.empty())
    {
        len = q.size();
        ans = max(ans , len);
        for (int i = 1 ; i <= len ; i++)
        {
            now = q.front();
            q.pop();
            if (now -> lc != NULL)
                q.push(now -> lc);
            if (now -> rc != NULL)
                q.push(now -> rc);
        }
        
    }
    cout<<ans<<endl;
}

void PrintTree(BTREE *T,int h)//打印二叉树		
{
	if (T == NULL)
        return;
    PrintTree(T -> rc , h+1);
    for (int i = 1 ; i <= h ; i++)
        cout<<"   ";
    cout<<T -> v<<endl;
    PrintTree(T -> lc , h+1);
}

int main()
{
    cin>>c;
    root = CreateBT(root);
    cout<<endl<<"先序遍历(递归)：  ";
    PreOrder(root);
    cout<<endl<<"先序遍历(非递归)：";
    _PreOrder(root);
    cout<<endl<<"中序遍历(递归)：  ";
    InOrder(root);
    cout<<endl<<"中序遍历(非递归)：";
    _InOrder(root);
    cout<<endl<<"后序遍历(递归)：  ";
    PostOrder(root);
    cout<<endl<<"后序遍历(非递归)：";
    _PostOrder(root);
    cout<<endl<<"层序遍历：";
    LevelOrder(root);
    cout<<endl;
    CompTree(root);
    cout<<"二叉树的宽度：";
    CalWidth(root);
    cout<<"二叉树："<<endl;
    PrintTree(root , 0);
    system("pause");
    return 0;
}
//ABDH##I##E##CF#J##G##