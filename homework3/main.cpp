#include <bits/stdc++.h>
#include <vector>

using namespace std;

const int INF = numeric_limits<int>::max(); // 代表无穷大
// const int INF = INFINITY;

typedef struct tnode
{
    int data;
    struct tnode* lchild;
    struct tnode* brother;
}TREE;

class vnode {
public:
    int v;
    vnode* next;
    vnode(int x)
    {
        v = x;
        next = nullptr;
    };
    ~vnode() {};
};

class graph {
public:
    vector<vector<int>> g;
    vector<vnode*> list;
    vector<int> visited;
    vector<int> BH;
    vector<vector<int>> dfs_forest; 
    vector<vector<int>> bfs_forest; 


    int v;
    int edges;
    graph(int n, int m)
        : v(n)
        , edges(m)
        , visited(n, 0)
        , BH(n, 0)
        , g(n, vector<int>(n, 0))
        , list(n, nullptr)
    {
        for (int i = 0; i < n; i++) {
            list[i] = new vnode(i);
        }
    }
    ~graph()
    {
    }
    void addEdge(int x, int y)
    {
        g[x][y] = 1;
        g[y][x] = 1;
    }

    void trans(int print)
    {
        for (int i = 0; i < v; i++) {
            vnode* curr = list[i];
            for (int j = 0; j < v; j++) {
                if (g[i][j] == 1) {
                    vnode* p = new vnode(j);
                    curr->next = p;
                    curr = curr->next;
                }
            }
        }

        if (print) {

            for (int i = 0; i < v; i++) {
                vnode* curr = list[i];

                for (int j = 0; j < v; j++) {
                    cout << curr->v;
                    if (curr->next == nullptr) {
                        break;
                    }
                    curr = curr->next;
                    cout << "->";
                }
                cout << endl;
            }
        }
        cout << "graph to list finished" << endl;

        for (int i = 0; i < v; i++) {
            for (int j = 0; j < v; j++) {
                g[i][j] = 0;
            }
        }

        for (int i = 0; i < v; i++) {
            vnode* p = list[i]->next;
            while (p != NULL) {
                g[i][p->v] = 1;
                p = p->next;
            }
        }
        if (print) {
            display();
        }
        cout << "graph to matrix finished" << endl;
    }





    void g_dfs(int curr, int& count) // 邻接矩阵dfs递归版
    {
        visited[curr] = 1;
        cout << curr << "->";
        BH[curr] = count;
        count++;
        for (int i = 0; i < v; i++) {
            if (g[curr][i] && !visited[i]) {
                g_dfs(i, count);
            }
        }
    }

    void g_dfs(int curr)
    {
        for (int i = 0; i < v; i++) {
            visited[i] = 0;
            BH[i] = 0;
        }
        cout << "邻接矩阵深度优先序列为";
        int count = 1;
        g_dfs(curr, count);
        cout << endl;
        cout << "邻接矩阵深度优先编号为：";
        for (int i = 0; i < v; i++) {
            cout << BH[i] << "->";
        }
        cout << endl;
    }

    stack<int> s;

    void g_dfs_no_rec(int curr, int& count) // 邻接矩阵dfs非递归版
    {
        s.push(curr);
        cout << curr << "->";
        BH[curr] = count;
        count++;
        while (!s.empty()) {
            curr = s.top();
            visited[curr] = 1;
            for (int i = 0; i < v; i++) {
                if (g[curr][i] && !visited[i]) {
                    cout << i << "->";
                    BH[i] = count;
                    count++;
                    s.push(i);
                    break;
                }

                if (i == v - 1) {
                    s.pop();
                }
            }
        }
    }
    void g_dfs_no_rec(int curr)
    {
        for (int i = 0; i < v; i++) {
            visited[i] = 0;
            BH[i] = 0;
        }
        cout << "邻接矩阵深度优先序列为";
        int count = 1;
        g_dfs_no_rec(curr, count);
        cout << endl;
        cout << "邻接矩阵深度优先编号为：";
        for (int i = 0; i < v; i++) {
            cout << BH[i] << "->";
        }
        cout << endl;
    }

    queue<int> q;

    void g_bfs(int curr,int count) // 邻接矩阵bfs
    {
        for (int i = 0; i < visited.size(); i++) {
            visited[i] = 0;
        }
        q.push(curr);
        cout << curr << "->";
        BH[curr] = count;
        count++;
        visited[curr] = 1;
        while (!q.empty()) {
            curr = q.front();
            q.pop();
            for (int i = 0; i < v; i++) {
                if (!visited[i] && g[curr][i]) {
                    q.push(i);
                    visited[i] = 1;
                    cout << i << "->";
                    BH[i] = count;
                    count++;
                }
            }
        }
        cout << endl;
        for (int i = 0; i < visited.size(); i++) {
            visited[i] = 0;
        }
    }

    void g_bfs(int curr)
    {
        for (int i = 0; i < v; i++) {
            visited[i] = 0;
            BH[i] = 0;
        }
        cout << "邻接矩阵广度优先序列为";
        int count = 1;
        g_bfs(curr, count);
        cout << endl;
        cout << "邻接矩阵广度优先编号为：";
        for (int i = 0; i < v; i++) {
            cout << BH[i] << "->";
        }
        cout << endl;
    }





    void list_dfs(int curr,int &count)
    {
        visited[curr] = 1;
        cout << curr << "->";
        BH[curr] = count;
        count++;
        vnode* p = list[curr]->next;
        while (1) {
            if (p == nullptr) {
                break;
            }
            if (!visited[p->v]) {
                list_dfs(p->v,count);
            }
            p = p->next;
        }
    }

    void list_dfs(int curr)
    {
        for (int i = 0; i < v; i++) {
            visited[i] = 0;
            BH[i] = 0;
        }
        cout << "邻接表深度优先序列为";
        int count = 1;
        list_dfs(curr, count);
        cout << endl;
        cout << "邻接表深度优先编号为：";
        for (int i = 0; i < v; i++) {
            cout << BH[i] << "->";
        }
        cout << endl;
    }







    void list_dfs_no_rec(int curr ,int count) // 邻接表dfs(非递归版)
    {
        cout << curr << "->";
        BH[curr] = count;
        count++;
        s.push(curr);
        visited[curr] = 1;
        while (!s.empty()) {
            curr = s.top();
            vnode* p = list[curr]->next;
            while (p != NULL) {
                if (!visited[p->v]) {
                    s.push(p->v);
                    visited[p->v] = 1;
                    cout << p->v << "->";
                    BH[p->v] = count;
                    count++;
                    break;
                }
                p = p->next;
                if (p == NULL) {
                    s.pop();
                }
            }
        }
    }

    void list_dfs_no_rec(int curr)
    {
        for (int i = 0; i < v; i++) {
            visited[i] = 0;
            BH[i] = 0;
        }
        cout << "邻接表深度优先序列为";
        int count = 1;
        list_dfs_no_rec(curr, count);
        cout << endl;
        cout << "邻接表深度优先编号为：";
        for (int i = 0; i < v; i++) {
            cout << BH[i] << "->";
        }
        cout << endl;
    }





    void list_bfs(int curr,int count) // 邻接表bfs
    {
        q.push(curr);
        visited[curr] = 1;
        cout << curr << " ";
        BH[curr] = count;
        count++;
        while (!q.empty()) {
            curr = q.front();
            q.pop();
            vnode* p = list[curr]->next;
            while (p != NULL) {
                if (!visited[p->v]) {
                    q.push(p->v);
                    visited[p->v] = 1;
                    cout << p->v << "->";
                    BH[p->v] = count;
                    count++;
                }
                p = p->next;
            }
        }
    }


    void list_bfs(int curr)
    {
        for (int i = 0; i < v; i++) {
            visited[i] = 0;
            BH[i] = 0;
        }
        cout << "邻接表广度优先序列为";
        int count = 1;
        list_bfs(curr, count);
        cout << endl;
        cout << "邻接表广度优先编号为：";
        for (int i = 0; i < v; i++) {
            cout << BH[i] << "->";
        }
        cout << endl;
    }


    void g_dfs_forest(int curr, vector<int>& component)
    {
        visited[curr] = 1;
        component.push_back(curr);

        for (int i = 0; i < v; i++) {
            if (g[curr][i] && !visited[i]) {
                g_dfs_forest(i, component);
            }
        }
    }

    void g_dfs_forest()
    {
        dfs_forest.clear();
        for (int i = 0; i < v; i++) {
            visited[i] = 0;
        }
        for (int i = 0; i < v; i++) {
            if (!visited[i]) {
                vector<int> component;
                g_dfs_forest(i, component);
                dfs_forest.push_back(component);
            }
        }

        cout << "DFS Forest:" << endl;
        for (const auto& component : dfs_forest) {
            for (int vertex : component) {
                cout << vertex << "->";
            }
            cout << endl;
        }
    }

    void g_bfs_forest(int curr, vector<int>& component)
    {
        q.push(curr);
        visited[curr] = 1;
        component.push_back(curr);

        while (!q.empty()) {
            curr = q.front();
            q.pop();
            for (int i = 0; i < v; i++) {
                if (!visited[i] && g[curr][i]) {
                    q.push(i);
                    visited[i] = 1;
                    cout<<i<<" ";
                    component.push_back(i);
                }
            }
        }
    }

    void g_bfs_forest()
    {
        bfs_forest.clear();        
        for (int i = 0; i < v; i++) {
            visited[i] = 0;
        }
        for (int i = 0; i < v; i++) {
            if (!visited[i]) {
                vector<int> component;
                g_bfs_forest(i, component);
                bfs_forest.push_back(component);
            }
        }

        cout << "BFS Forest:" << endl;
        for (const auto& component : bfs_forest) {
            for (int vertex : component) {
                cout << vertex << "->";
            }
            cout << endl;
        }

    }

//深度优先生成树（森林）
void DFSTree(int i,TREE** T)
{
    visited[i]=1; //标记已访问
    int flag=1;
    TREE* p=NULL;
    int j;
    for(j=0;j<v;j++)
    {
        if(g[i][j]&&!visited[j])
        {
            TREE* temp=new tnode;
            temp->data=j;
            temp->lchild=NULL;
            temp->brother=NULL;
            if(flag) 
            {
                (*T)->lchild=temp;
                flag=0;
            }
            else
            {

                p->brother=temp;
            }
            p=temp;
            DFSTree(j,&p);
        }
    }
}
//深度优先生成森林并转化为二叉树
void DFSForest(TREE** T)
{
    (*T)=NULL;
    for(int i=0;i<v;i++) 
    {
        visited[i]=0;
    }
    TREE* p;
    for(int i=0;i<v;i++)
    {
        if(!visited[i])
        {
            TREE* temp=new tnode;
            temp->data=i;
            temp->lchild=NULL;
            temp->brother=NULL;
            if(!(*T))
            {
                (*T)=temp;
            }
            else
            {
                p->brother=temp;
            }
            p=temp;
            DFSTree(i,&temp);
        }
    }
}
//按先序打印树
void PreOrder(TREE* T)
{
    if (T)
    {
        printf("%d ",T->data);
        PreOrder(T->lchild);
        PreOrder(T->brother);
    }
    return;
}
TREE* queue2[50];
int front;
int rear;
//广度优先生成树
void BFSTree(int i,TREE** T)
{
    TREE* p=NULL;
    front=rear=-1; 
    queue2[++rear]=(*T); 
    while(front!=rear) 
    {
        int flag=1;
        p=queue2[++front]; 
        i=p->data;
        visited[i]=1;
        for(int j=0;j<v;j++)
        {
            if((!visited[j])&&g[i][j])
            {
                TREE* temp=new tnode;
                temp->data=j;
                temp->lchild=NULL;
                temp->brother=NULL;
                queue2[++rear]=temp;
                visited[j]=1;
                if(flag) 
                {
                    p->lchild=temp;
                    flag=0;
                }
                else 
                {
                    p->brother=temp;
                }
                p=temp;
            }
        }
    }
}
//广度优先生成森林
void BFSForest(TREE** T)
{
     (*T)=NULL;
     for(int i=0;i<v;i++)
     {
         visited[i]=0;
     }
     TREE* p=NULL;
     for(int i=0;i<v;i++)
     {
         if(!visited[i])
         {
             TREE* temp=new tnode;
             temp->data=i;
             temp->lchild=NULL;
             temp->brother=NULL;
             if(!(*T))
             {
                 (*T)=temp;
             }
             else
             {
                 p->brother=temp;
             }
             p=temp;
             BFSTree(i,&temp);
         }
     }
}







    void cal() // 计算顶点的度
    {
        int cnt = 0;
        for (int i = 0; i < v; i++) {
            cnt = 0;
            vnode* p = list[i]->next;
            while (p != NULL) {
                cnt++;
                p = p->next;
            }
            printf("\n%d的度为: %d", i, cnt);
        }
    }

    void display()
    {
        for (int i = 0; i < v; ++i) {
            for (int j = 0; j < v; ++j) {
                cout << g[i][j] << " ";
            }
            cout << endl;
        }
    }
};

int main()
{

    TREE* T1;
    TREE* T2;

    int n, m;

    FILE* f = fopen("graph.txt", "r");

    if (f == nullptr) {
        perror("Error opening file");
        return 1; // Indicates an error
    }

    fscanf(f, "%d %d", &n, &m);
    graph g(n, m);

    int source, dest;
    for (int i = 1; i <= m; i++) {
        fscanf(f, "%d %d", &source, &dest);
        g.addEdge(source, dest);
    }

    g.display();
    g.trans(0);
    cout<<"递归："<<endl;
    g.g_dfs(0);
    cout << endl;
    cout<<"非递归："<<endl;

    g.g_dfs_no_rec(0);
    cout << endl;

    g.g_bfs(0);
    cout << endl;
    cout<<"递归："<<endl;

    g.list_dfs(0);
    cout << endl;
    cout<<"非递归："<<endl;

    g.list_dfs_no_rec(0);
    cout << endl;

    g.list_bfs(0);
    cout << endl;

    // g.g_dfs_forest();
    // cout << endl;

    // g.g_bfs_forest();
    // cout << endl;
    cout<<"邻接矩阵的深度优先生成树:"<<endl;
    g.DFSForest(&T1);
    g.PreOrder(T1);
    cout<<endl;
    cout<<"邻接矩阵的广度优先生成树:"<<endl;
    g.BFSForest(&T2);
    g.PreOrder(T2);
    cout<<endl;

    g.cal();
    return 0;
}
