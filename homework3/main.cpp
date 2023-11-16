#include <bits/stdc++.h>
#include <vector>

using namespace std;

const int INF = numeric_limits<int>::max(); // 代表无穷大
// const int INF = INFINITY;

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

    int v;
    int edges;
    graph(int n, int m)
        : v(n)
        , edges(m)
        , visited(n, 0)
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

    void g_dfs(int curr) // 邻接矩阵dfs递归版
    {
        visited[curr] = 1;
        cout << curr << "->";
        for (int i = 0; i < v; i++) {
            if (g[curr][i] && !visited[i]) {
                g_dfs(i);
            }
        }
    }

    stack<int> s;

    void g_dfs_no_rec(int curr) // 邻接矩阵dfs非递归版
    {
        s.push(curr);
        cout << curr << " ";
        while (!s.empty()) {
            curr = s.top();
            visited[curr] = 1;
            for (int i = 0; i < v; i++) {
                if (g[curr][i] && !visited[i]) {
                    cout << i << " ";
                    s.push(i);
                    break;
                }

                if (i == v - 1) {
                    s.pop();
                }
            }
        }
    }

    queue<int> q;

    void g_bfs(int curr) // 邻接矩阵bfs
    {
        for (int i = 0; i < visited.size(); i++) {
            visited[i] = 0;
        }
        q.push(curr);
        cout << curr << "->";
        visited[curr] = 1;
        while (!q.empty()) {
            curr = q.front();
            q.pop();
            for (int i = 0; i < v; i++) {
                if (!visited[i] && g[curr][i]) {
                    q.push(i);
                    visited[i] = 1;
                    cout << i << "->";
                }
            }
        }
        cout << endl;
        for (int i = 0; i < visited.size(); i++) {
            visited[i] = 0;
        }
    }

    void list_dfs(int curr)
    {
        visited[curr] = 1;
        cout << curr << "->";
        vnode* p = list[curr]->next;
        while (1) {
            if (p == nullptr) {
                break;
            }
            if (!visited[p->v]) {
                list_dfs(p->v);
            }
            p = p->next;
        }
    }

void list_dfs_no_rec(int curr)//邻接表dfs(非递归版)
{
    cout<<curr<<"->";
    s.push(curr);
    visited[curr] = 1;
    while (!s.empty()) {
        curr = s.top();
        vnode *p = list[curr]->next;
        while (p != NULL) {
            if (!visited[p->v]) {
                s.push(p->v);
                visited[p->v] = 1;
                cout<<p->v<<"->";
                break;
            }
            p = p->next;
            if (p == NULL) {
                s.pop();
            }
        }
    }
}



void list_bfs(int curr)//邻接表bfs
{
    q.push(curr);
    visited[curr] = 1;
    cout<<curr<<" ";
    while (!q.empty()) {
        curr = q.front();
        q.pop();
        vnode *p = list[curr]->next;
        while (p != NULL) {
            if (!visited[p->v]) {
                q.push(p->v);
                visited[p->v] = 1;
                cout<<p->v<<" ";
            }
            p = p->next;
        }
        
    }
}


void cal()//计算顶点的度
{
    int cnt = 0;
    for (int i = 0; i < v ; i++) {
        cnt = 0;
        vnode *p = list[i]->next;
        while (p != NULL) {
            cnt++;
            p = p->next;
        }
        printf("\n%d的度为: %d" , i , cnt);
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
    // g.g_dfs(0);
    cout << endl;
    // g.g_dfs_no_rec(0);
    // g.g_bfs(0);
    // g.list_dfs(0);
    // g.list_dfs_no_rec(0);
    g.list_bfs(0);
    g.cal();
    return 0;
    // 5 8 0 3 30 0 1 10 1 2 50 2 4 10 2 3 20 3 2 20 3 4 60 0 4 100
}
