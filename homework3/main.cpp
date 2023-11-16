# include <bits/stdc++.h>

using namespace std;

const int INF = numeric_limits<int>::max(); // 代表无穷大
// const int INF = INFINITY;

class graph {
public:
    vector<vector<int>> g;
    int v;
    int edges;
    graph(int n, int m)
        : g(n, vector<int>(n, 0))
    {
        v = n;
        edges = m;
    };
    ~graph()
    {
    }
    void addEdge(int x, int y)
    {
        g[x][y] = 1;
        g[y][x] = 1;
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
        return 1;  // Indicates an error
    }

    fscanf(f, "%d %d", &n, &m);
    graph g(n,m);

    int source, dest;
    for (int i = 1; i <= m; i++) {
        fscanf(f, "%d %d", &source, &dest);
        g.addEdge(source, dest);
    }
    g.display();

    return 0;
    // 5 8 0 3 30 0 1 10 1 2 50 2 4 10 2 3 20 3 2 20 3 4 60 0 4 100
}
