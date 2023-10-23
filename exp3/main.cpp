#include <fstream>
#include <iostream>
#include <limits>
#include <math.h>
#include <stack>
#include <vector>

using namespace std;

const int INF = numeric_limits<int>::max(); // 代表无穷大
// const int INF = INFINITY;

// Dijkstra算法
void Dijkstra(vector<vector<int>>& graph, int source)
{
    int n = graph.size();
    vector<int> dist(n, INF);
    vector<bool> visited(n, false);
    vector<int> path(n, source);

    visited[source] = true;
    for (int i = 0; i < graph.size(); i++) {
        dist[i] = graph[source][i];
    }

    for (int i = 0; i < n - 1; i++) {
        int minDist = INF, minIndex = -1;

        // 找到距离最近且未被访问的顶点
        for (int j = 0; j < n; j++) {
            if (!visited[j] && dist[j] < minDist) {
                minDist = dist[j];
                minIndex = j;
            }
        }

        if (minIndex == -1)
            break;

        visited[minIndex] = true;

        // 更新相邻顶点的距离
        for (int j = 0; j < n; j++) {
            if (!visited[j] && graph[minIndex][j] != INF && dist[minIndex] != INF && dist[minIndex] + graph[minIndex][j] < dist[j]) {
                path[j] = minIndex;
                dist[j] = dist[minIndex] + graph[minIndex][j];
            }
        }
    }

    for (int i = 0; i < n; i++) {
        cout << path[i] << endl;
    }

    // 输出最短路径长度和路径
    stack<int> finalpath;
    int temp;
    for (int i = 0; i < n; i++) {
        if (i == source) {
            continue;
        }
        if (dist[i] == INF) {
            continue;
        }
        temp = i;
        finalpath.push(temp);
        cout << "Source to Vertex " << i << " (Distance: " << dist[i] << "): ";
        while (1) {
            temp = path[temp];
            finalpath.push(temp);
            if (temp == source) {
                // finalpath.push(source);
                break;
            }
        }
        while (1) {
            cout << finalpath.top();
            finalpath.pop();
            if (finalpath.empty()) {
                break;
            }
            cout << "->";
        }
        cout << endl;
    }
}

void search(int s, int e, vector<vector<int>> path, vector<vector<int>> graph, vector<vector<int>> dist)
{
    int k = path[s][e];
    if (graph[s][e] == dist[s][e]) {
        cout << "->" << e;
        return;
    }
    search(s, k, path, graph, dist);

    search(k, e, path, graph, dist);
}

// Floyd-Warshall算法
void FloydWarshall(vector<vector<int>>& graph)
{
    int n = graph.size();
    vector<vector<int>> dist = graph;
    vector<vector<int>> path(n, vector<int>(n, -1));

    // 计算最短路径
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (dist[i][k] != INF && dist[k][j] != INF && dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                    path[i][j] = k;
                }
            }
        }
    }

    for (int i = 0; i < n; i++) {
        dist[i][i] = 0;
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) {
                continue;
            }
            if (dist[i][j] == INF) {
                continue;
            }
            cout << "Vertex " << i << " to Vertex " << j << " (Distance: " << dist[i][j] << "): ";
            cout << i;
            search(i, j, path, graph, dist);
            cout << endl;
        }
    }

    //     for (int i=0; i<n; i++) {
    //         for (int j=0; j<n; j++) {
    //             cout<<dist[i][j]<<"  ";

    //         }
    //         cout<<endl;
    //     }

    // return;

    // 输出最短路径长度和路径
    // for (int i = 0; i < n; i++) {
    //     for (int j = 0; j < n; j++) {
    //     if (i==j) {
    //     continue;
    //     }
    //         cout << "Vertex " << i << " to Vertex " << j << " (Distance: " << dist[i][j] << "): ";
    //         vector<int> path;
    //         int v = i;
    //         while (v != j) {
    //             for (int k = 0; k < n; k++) {
    //                 if (graph[v][k] + dist[k][j] == dist[v][j]) {
    //                     path.push_back(k);
    //                     v = k;
    //                     break;
    //                 }
    //             }
    //         }
    //         cout << i;
    //         for (int p : path)
    //             cout << " -> " << p;
    //         cout << endl;
    //         // cout << " -> " << j << endl;
    //     }
    // }
}
void FloydWarshall(vector<vector<int>>& graph, int end)
{
    int n = graph.size();
    vector<vector<int>> dist = graph;
    vector<vector<int>> path(n, vector<int>(n, -1));

    // 计算最短路径
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (dist[i][k] != INF && dist[k][j] != INF && dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                    path[i][j] = k;
                }
            }
        }
    }

    for (int i = 0; i < n; i++) {
        dist[i][i] = 0;
    }

    for (int i = 0; i < n; i++) {
        if (i == end) {
            continue;
        }
        if (dist[i][end] == INF) {
            continue;
        }
        cout << "Vertex " << i << " to Vertex " << end << " (Distance: " << dist[i][end] << "): ";
        cout << i;
        search(i, end, path, graph, dist);
        cout << endl;
    }
}
void FloydWarshall(vector<vector<int>>& graph, int u, int v)
{
    if (u == v) {
        return;
    }
    int n = graph.size();
    vector<vector<int>> dist = graph;
    vector<vector<int>> path(n, vector<int>(n, -1));

    // 计算最短路径
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (dist[i][k] != INF && dist[k][j] != INF && dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                    path[i][j] = k;
                }
            }
        }
    }

    for (int i = 0; i < n; i++) {
        dist[i][i] = 0;
    }

    if (dist[u][v] != INF) {
        cout << "Vertex " << u << " to Vertex " << v << " (Distance: " << dist[u][v] << "): ";
        cout << u;
        search(u, v, path, graph, dist);
        cout << endl;
    }
    if (dist[v][u] != INF) {
        cout << "Vertex " << v << " to Vertex " << u << " (Distance: " << dist[v][u] << "): ";
        cout << v;
        search(v, u, path, graph, dist);
        cout << endl;
    }
}
int main()
{
    int n, m;


    FILE* f = fopen("graph.txt" , "r");
    fscanf(f , "%d %d" , &n , &m);
    vector<vector<int>> graph(n, vector<int>(n, INF));

    int x , y , z;
    for (int i = 1 ; i <= m ; i++)
    {
        fscanf(f , "%d %d %d", &x ,&y ,&z);
        graph[x][y]=z;
    }

    // cout << "Enter the number of vertices: ";
    // cin >> n;
    // cout << "Enter the number of edges: ";
    // cin >> m;


    // cout << "Enter edge information (source, destination, weight):" << endl;
    // for (int i = 0; i < m; i++) {
    //     int source, dest, weight;
    //     cin >> source >> dest >> weight;
    //     graph[source][dest] = weight;
    // }

while (1)
    {
        printf("1.Dijkstra 算法，输出源点及其到其他顶点的最短路径长度和最短路径。\n");
        printf("2.Floyd-Warshall算法。输出任意两个顶点间的最短路径长度和最短路径。\n");
        printf("3.Floyd-Warshall算法。找出图中每个顶点 v 到某个指定顶点 w 最短路径。\n");
        printf("4.Floyd-Warshall算法。对于某对顶点 u 和 v, 找出 u 到 v 和 v 到 u 的一条最短路径。\n");
        printf("5.退出\n");
        char c;
        scanf("%d" , &c);
        if (c == 5)
            break;        
        switch (c)
        {
        case 1:
            cout<<"Source:";
            int source;
            cin>>source;
            Dijkstra(graph, source);
            break;
        case 2:
            FloydWarshall(graph);
            break;
        case 3:
            int end;
            cout<<"Endpoint:";
            cin>>end;
            FloydWarshall(graph,end);
            break;
        case 4:
        int u,v;
        cout<<"u,v:";
        cin>>u>>v;
            FloydWarshall(graph,u,v);
        }
        printf("\n\n");

    }





    // // Dijkstra算法
    // int sourceDijkstra;
    // cout << "Enter the source vertex for Dijkstra: ";
    // cin >> sourceDijkstra;
    // Dijkstra(graph, sourceDijkstra);

    // // Floyd-Warshall算法
    // FloydWarshall(graph);

    return 0;
    // 5 8 0 3 30 0 1 10 1 2 50 2 4 10 2 3 20 3 2 20 3 4 60 0 4 100
}
