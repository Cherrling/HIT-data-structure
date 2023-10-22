#include<bits/stdc++.h>
#define MAX_SIZE 1000
using namespace std;
int n , m , v0 = 0;
int d[MAX_SIZE],p[MAX_SIZE],r[MAX_SIZE];
int a[MAX_SIZE][MAX_SIZE] , pf[MAX_SIZE][MAX_SIZE] , fy[MAX_SIZE][MAX_SIZE];
bool v[MAX_SIZE];

void readin()
{
    memset(r , 0 , sizeof(r));
    memset(a , 0x3f , sizeof(a));
    FILE* f = fopen("3\\map.txt" , "r");
    fscanf(f , "%d %d" , &n , &m);
    int x , y , z;
    for (int i = 1 ; i <= m ; i++)
    {
        fscanf(f , "%d %d %d", &x ,&y ,&z);
        r[y]++;
        a[x][y] = z;
    }
    for (int i = 1 ; i <= n ; i++)
    {
        a[i][i] = 0;
    }
            
    // for (int i = 1 ; i <= n ; i++)
    // {
    //     for (int j = 1 ; j <= n ; j++)
    //         printf("%d " , a[i][j]);
    //     printf("\n");
    // }
        
}

void init()
{
    bool flag;
    for (int i = 1 ; i <= n ; i++)
    {
        if (!r[i])
            v0 = i;
    }
    if (!v0)
        v0 = 1;
    memset(v , 0 , sizeof(v));
    memset(d , 0x3f , sizeof(d));
    memset(p , -1 , sizeof(p));
}

void dij()
{
    printf("源点： %d\n" , v0);
    int t;
    d[v0] = 0;
    p[v0] = -1;
    for (int i = 1 ; i <= n ; i++)
    {
        t = 0;
        for (int j = 1 ; j <= n ; j++)
            if (!v[j] && (!t || d[j] < d[t]))
                t = j;
        v[t] = 1;
        for (int j = 1 ; j <= n ; j++)
            if (d[j] > d[t] + a[t][j])
            {
                p[j] = t;
                d[j] = d[t] + a[t][j];
            }   
    }
    for (int i = 1 ; i <= n ; i++)
    {
        printf("%d --> %d weight = %d" , v0 , i , d[i]);
        int j = p[i];
        printf(" path: %d" , i);
        while (j != -1)
        {
            printf(" <-- %d", j);
            j = p[j];
        }
        printf("\n");
    }
}

void floyd()
{
    for (int i = 1 ; i <= n ; i++)
    {
        for (int j = 1 ; j <= n ; j++)
        {
            pf[i][j] = j;
        }
    }
    for (int k = 1 ; k <= n ; k++)
    {
        for (int i = 1 ; i <= n ; i++)
        {
            for (int j = 1 ; j <= n ; j++)
            {
                if (a[i][j] > a[i][k] + a[k][j])
                {
                    a[i][j] = a[i][k] + a[k][j];
                    pf[i][j] = pf[i][k];
                }
            }
        }
    }
    printf("最短路径矩阵：\n");
    for (int i = 1 ; i <= n ; i++)
    {
        for (int j = 1 ; j <= n ; j++)
        {
            if (a[i][j] != 1061109567)
                printf("%d " , a[i][j]);
            else
                printf("∞ ");
        }
            
        printf("\n");
    }
    printf("任意两个顶点间的最短路径：\n");
    int k;
    for (int i = 1 ; i <= n ; i++)
    {
        for (int j = 1 ; j <= n ; j++)
        {
            if (a[i][j] != 1061109567)
            {
                printf("%d ---> %d weight = %d path :%d" , i , j , a[i][j] , i);
                k = i;
                while (k != j)
                {
                    k = pf[k][j];
                    printf(" --> %d" , k);
                }
                printf("\n");
            }
            else
                printf("%d到%d没有路\n", i , j);   
        }
    }
}

void floyd1()
{
    for (int i = 1 ; i <= n ; i++)
    {
        for (int j = 1 ; j <= n ; j++)
        {
            pf[i][j] = j;
        }
    }
    for (int k = 1 ; k <= n ; k++)
    {
        for (int i = 1 ; i <= n ; i++)
        {
            for (int j = 1 ; j <= n ; j++)
            {
                if (a[i][j] > a[i][k] + a[k][j])
                {
                    a[i][j] = a[i][k] + a[k][j];
                    pf[i][j] = pf[i][k];
                }
            }
        }
    }
    int w;
    while (1)
    {
        printf("1.输入单目标：2.输入0退出\n");
        scanf("%d" , &w);
        if (w == 0)
            break;
        int k;
        for (int i = 1 ; i <= n ; i++)
        {
            if (a[i][w] != 1061109567)
            {
                printf("%d ---> %d weight = %d path :%d" , i , w , a[i][w] , i);
                k = i;
                while (k != w)
                {
                    k = pf[k][w];
                    printf(" --> %d" , k);
                }
                printf("\n");
            }
            else
                printf("%d到%d间没有路\n", i , w);   
        }
        printf("\n\n");
    }
}

void floyd2()
{
    for (int i = 1 ; i <= n ; i++)
    {
        for (int j = 1 ; j <= n ; j++)
        {
            pf[i][j] = j;
        }
    }
    for (int k = 1 ; k <= n ; k++)
    {
        for (int i = 1 ; i <= n ; i++)
        {
            for (int j = 1 ; j <= n ; j++)
            {
                if (a[i][j] > a[i][k] + a[k][j])
                {
                    a[i][j] = a[i][k] + a[k][j];
                    pf[i][j] = pf[i][k];
                }
            }
        }
    }
    int x , y , k;
    while (1)
    {
        printf("1.输入两个顶点可求解最短路径 2.输入两个0可退出\n");
        scanf("%d %d" , &x , &y);
        if(x == 0 && y == 0)
            break;
        if (a[x][y] != 1061109567)
        {
            printf("%d ---> %d weight = %d path :%d" , x , y , a[x][y] , x);
            k = x;
            while (k != y)
            {
                k = pf[k][y];
                printf(" --> %d" , k);
            }
            printf("\n");
        }
        else
            printf("%d到%d没有路\n", x , y);   
        if (a[y][x] != 1061109567)
        {
            printf("%d ---> %d weight = %d path :%d" , y , x , a[y][x] , y);
            k = y;
            while (k != x)
            {
                k = pf[k][x];
                printf(" --> %d" , k);
            }
            printf("\n");
        }
        else
            printf("%d到%d没有路\n", y , x); 
        printf("\n\n\n");
    }
}

int main()
{
    readin();
    init();
    int c;
    while (1)
    {
        printf("1.使用Dijkstra算法，输出源点及其到其他顶点的最短路径长度和最短路径。\n");
        printf("2.使用Floyd-Warshall算法。计算任意两个顶点间的最短距离矩阵和最短路径矩阵，并输出任意两个顶点间的最短路径长度和最短路径。\n");
        printf("3.利用Floyd-Warshall算法解决单目标最短路径问题：找出图中每个顶点 v 到某个指定顶点 w 最短路径。\n");
        printf("4.利用Floyd-Warshall算法解决单顶点对间最短路径问题：对于某对顶点 u 和 v， 找出 u 到 v 和 v 到 u 的一条最短路径。\n");
        printf("5.退出\n");
        scanf("%d" , &c);
        if (c == 5)
            break;        
        switch (c)
        {
        case 1:
            dij();
            break;
        case 2:
            floyd();
            break;
        case 3:
            floyd1();
            break;
        case 4:
            floyd2();
        }
        printf("\n\n\n\n\n");

    }
    system("pause");
    return 0;
}
