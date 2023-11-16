# include <bits/stdc++.h>
# define MAX_SIZE 1000
using namespace std;

int n,m;
int v[MAX_SIZE];
int Map[MAX_SIZE][MAX_SIZE];

struct Vnode
{
    int ve;
    Vnode *next;
}Vernode;

struct node
{
    int e;
    Vnode *next;
}Edgenode[MAX_SIZE];

void readin()
{
    memset(Map , 0 , sizeof(Map));

    int x,y;
    cin>>n>>m;
    for (int i = 1 ; i <= n ; i++) {
        Edgenode[i].e = i;
        Edgenode[i].next = NULL;
    }
    for (int i = 1 ; i <= m ; i++) {
        cin>>x>>y;

        Map[x][y] = 1;//�ڽӾ���
        Map[y][x] = 1;
        
        Vnode *p = new Vnode;//�ڽӱ�
        p->ve = y;
        p->next = Edgenode[x].next;
        Edgenode[x].next = p;
        p = new Vnode;
        p->ve = x;
        p->next = Edgenode[y].next;
        Edgenode[y].next = p;
    }
}

void trans()
{
    //�ڽӾ���ת�ڽӱ�
    for (int i = 1 ; i <= n ; i++) {
        for (int j = 1 ; j <= n ; j++) {
            if (Map[i][j]) {
                Vnode *p = new Vnode;
                p->ve = j;
                p->next = Edgenode[i].next;
                Edgenode[i].next = p;
            }
        }
    }
    cout<<"�ڽӾ���ת�ڽӱ�ɹ�"<<endl;
    //�ڽӱ�ת�ڽӾ���
    for (int i = 1 ; i <= n ; i++) {
        Vnode *p = Edgenode[i].next;
        while (p != NULL) {
            Map[i][p->ve] = 1;
            p = p->next;
        }
    }
    cout<<"�ڽӱ�ת�ڽӾ���ɹ�"<<endl;
}

void Map_dfs1(int now)//�ڽӾ���dfs�ݹ��
{
    v[now] = 1;
    cout<<now<<" ";
    for (int i = 1; i <= n ; i++) {
        if (Map[now][i] && !v[i]) {
            Map_dfs1(i);
        }
    }
}

stack <int> s;

void Map_dfs2(int now)//�ڽӾ���dfs�ǵݹ��
{
    s.push(now);
    cout<<now<<" ";
    while (!s.empty()) {
        now = s.top();
        v[now] = 1;
        for (int i = 1 ; i <= n ; i++) {
            if (Map[now][i] && !v[i]) {
                cout<<i<<" ";
                s.push(i);
                break;
            }
            if (i == n) {
                s.pop();
            }
        }
    }
}

queue <int> q;

void Map_bfs(int now)//�ڽӾ���bfs
{
    q.push(now);
    cout<<now<<" ";
    v[now] = 1;
    while (!q.empty()) {
        now = q.front();
        q.pop();
        for (int i = 1 ; i <= n ; i++) {
            if (!v[i] && Map[now][i]) {
                q.push(i);
                v[i] = 1;
                cout<<i<<" ";
            }
        }
        
    }
}

void list_dfs1(int now)//�ڽӱ�dfs(�ݹ��)
{
    v[now] = 1;
    cout<<now<<" ";
    Vnode *p = Edgenode[now].next;
    while (p != NULL) {
        if (!v[p->ve]) {
            list_dfs1(p->ve);
        }
        p = p->next;
    }
}

void list_dfs2(int now)//�ڽӱ�dfs(�ǵݹ��)
{
    cout<<now<<" ";
    s.push(now);
    v[now] = 1;
    while (!s.empty()) {
        now = s.top();
        Vnode *p = Edgenode[now].next;
        while (p != NULL) {
            if (!v[p->ve]) {
                s.push(p->ve);
                v[p->ve] = 1;
                cout<<p->ve<<" ";
                break;
            }
            p = p->next;
            if (p == NULL) {
                s.pop();
            }
        }
    }
}

void list_bfs(int now)//�ڽӱ�bfs
{
    q.push(now);
    v[now] = 1;
    cout<<now<<" ";
    while (!q.empty()) {
        now = q.front();
        q.pop();
        Vnode *p = Edgenode[now].next;
        while (p != NULL) {
            if (!v[p->ve]) {
                q.push(p->ve);
                v[p->ve] = 1;
                cout<<p->ve<<" ";
            }
            p = p->next;
        }
        
    }
}

void cal()//���㶥��Ķ�
{
    int cnt = 0;
    for (int i = 1; i <= n ; i++) {
        cnt = 0;
        Vnode *p = Edgenode[i].next;
        while (p != NULL) {
            cnt++;
            p = p->next;
        }
        printf("\n%d�Ķ�Ϊ: %d" , i , cnt);
    }
}

void output()
{
    cout<<"�ڽӾ���"<<endl;
    for (int i = 1 ; i <= n ; i++) {
        for (int j = 1 ; j <= n ; j++) {
            cout<<Map[i][j]<<" ";
        }
        cout<<endl;
    }
    cout<<"�ڽӱ�"<<endl;
    for (int i = 1;  i <= n ; i++) {
        cout<<i<<": ";
        Vnode *p = Edgenode[i].next;
        while (p != NULL) {
            cout<<p->ve<<" ";
            p = p->next;
        }
        cout<<endl;
    }
}

int main()
{
    readin();
    // trans();
    output();
    
    cout<<endl<<"�ڽӾ���dfs(�ݹ��):   ";
    Map_dfs1(1);    
    memset(v , 0 , sizeof(v));
    cout<<endl<<"�ڽӾ���dfs(�ǵݹ��): ";
    Map_dfs2(1);
    memset(v , 0 , sizeof(v));
    cout<<endl<<"�ڽӾ���bfs:           ";
    Map_bfs(1);
    memset(v , 0 , sizeof(v));
    cout<<endl<<"�ڽӱ�dfs(�ݹ��):     ";
    list_dfs1(1);
    memset(v , 0 , sizeof(v));
    cout<<endl<<"�ڽӱ�dfs(�ǵݹ��):   ";
    list_dfs2(1);
    memset(v , 0 , sizeof(v));
    cout<<endl<<"�ڽӱ�bfs:             ";
    list_bfs(1);
    cal();
    system("pause");
    return 0;
}
/*
10 15
1 2
1 4
1 5
1 7
2 4
4 3
4 6
6 10
3 10
3 8
3 7
7 9
5 9
8 9
10 9
*/
/*
0 1 0 1 1 0 1 0 0 0
1 0 0 1 0 0 0 0 0 0
0 0 0 1 0 0 1 1 0 1
1 1 1 0 0 1 0 0 0 0
1 0 0 0 0 0 0 0 1 0
0 0 0 1 0 0 0 0 0 1
1 0 1 0 0 0 0 0 1 0
0 0 1 0 0 0 0 0 1 0
0 0 0 0 1 0 1 1 0 1
0 0 1 0 0 1 0 0 1 0
1: 7 5 4 2
2: 4 1
3: 7 8 10 4
4: 6 3 2 1
5: 9 1
6: 10 4
7: 9 3 1
8: 9 3
9: 10 8 5 7
10: 9 3 6
*/