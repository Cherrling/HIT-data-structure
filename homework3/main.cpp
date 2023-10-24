#include <fstream>
#include <iostream>
#include <limits>
#include <math.h>
#include <stack>
#include <vector>

using namespace std;

const int INF = numeric_limits<int>::max(); // 代表无穷大
// const int INF = INFINITY;

int main()
{
    int n, m;

    FILE* f = fopen("graph.txt", "r");
    fscanf(f, "%d %d", &n, &m);
    vector<vector<int>> graph(n, vector<int>(n, INF));

    int source, dest, weight;
    for (int i = 1; i <= m; i++) {
        fscanf(f, "%d %d %d", &source, &dest, &weight);
        graph[source][dest] = weight;
    }

    return 0;
    // 5 8 0 3 30 0 1 10 1 2 50 2 4 10 2 3 20 3 2 20 3 4 60 0 4 100
}
