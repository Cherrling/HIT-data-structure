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

    void trans()
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
        display();
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

    void g_bfs(int now) // 邻接矩阵bfs
    {
        for (int i = 0; i < visited.size(); i++) {
            visited[i] = 0;
        }
        q.push(now);
        cout << now << " ";
        visited[now] = 1;
        while (!q.empty()) {
            now = q.front();
            q.pop();
            for (int i = 1; i <= v; i++) {
                if (!visited[i] && g[now][i]) {
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
    // g.g_dfs(0);
    // g.g_dfs_no_rec(0);
    // g.g_bfs(0);





    
    // g.trans();

    return 0;
    // 5 8 0 3 30 0 1 10 1 2 50 2 4 10 2 3 20 3 2 20 3 4 60 0 4 100
}
