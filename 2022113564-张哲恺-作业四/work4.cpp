# include <bits\stdc++.h>
# define MAX_SIZE 10000
using namespace std;

int n , m , cnt;
int a[MAX_SIZE] , num1[MAX_SIZE] , num2[MAX_SIZE];

typedef struct node {
    int data;
    struct node *lc , *rc;
}BST;

BST *root1 , *root2;

BST* CreatBST(BST *p , int x) {
    if (p == NULL) {
        p = new node;
        p->data = x;
        p->lc = NULL;
        p->rc = NULL;
    }
    else if (x < p->data)
        p->lc = CreatBST(p->lc , x);
    else if (x > p->data)
        p->rc = CreatBST(p->rc , x);
    return p;
}

void readin() {
    root1 = NULL;
    for (int i = 1 ; i <= 2048 ; i++)
        if (i % 2)
            a[m++] = i;

    for (int i = 0 ; i < m ; i++)
        root1 = CreatBST(root1 , a[i]);
    
    for(int i = m; i > 1 ; i--) 
    {
    	srand((unsigned)time(NULL));
        int random_position=m-i+(rand()%i);
        swap(a[random_position], a[m - i]);
    }
            
    root2 = NULL;
    for (int i = 0 ; i < m ; i++)
        root2 = CreatBST(root2 , a[i]);
}

int erfen(int l , int r , int x , int num[]) {
    cnt++;
    if (l > r)
        return -1;
    int mid = (l + r) / 2;
    if (x == num[mid])
        return mid;
    else if (x > num[mid])
        return erfen(mid + 1 , r , x , num);
    else
        return erfen(l , mid - 1 , x , num);
    return -1;
}

BST* BST_search(BST *p , int x) {
    cnt++;
    if (p == NULL || x == p->data)
        return p;
    else if (x > p->data)
        return BST_search(p->rc , x);
    else if (x < p->data)
        return BST_search(p->lc , x);
    return NULL;
}

void mid_search(BST *p , int num[]) {
    if (p == NULL)
        return;
    mid_search(p->lc , num);
    num[++n] = p->data;
    mid_search(p->rc , num);
}

void _search()
{
    int cal1 = 0, uncal1 = 0 , cal2 = 0 , uncal2 = 0;
    for (int i = 1 ; i <= 2048 ; i++) {
        cnt = 0;
        if (BST_search(root1 , i) != NULL)
            cal1 += cnt;
        else
            uncal1 += cnt;
        // cout<<cnt<<endl;
        cnt = 0;
        if (erfen(1 , n , i , num1) != -1)
            cal2 += cnt;
        else
            uncal2 += cnt;
    }
    cout<<"数据一: "<<endl;
    cout<<"BST平均查找长度: 成功 "<<cal1/2048<<" 失败 "<<uncal1/2048<<endl;
    cout<<"折半查找平均查找长度 成功 "<<cal2/2048<<" 失败 "<<uncal2/2048<<endl;

    cal1 = 0, uncal1 = 0 , cal2 = 0 , uncal2 = 0;
    for (int i = 1 ; i <= 2048 ; i++) {
        cnt = 0;
        if (BST_search(root2 , i) != NULL)
            cal1 += cnt;
        else
            uncal1 += cnt;
        // cout<<cnt<<endl;
        cnt = 0;
        if (erfen(1 , n , i , num2) != -1)
            cal2 += cnt;
        else
            uncal2 += cnt;
    }
    cout<<"数据二: "<<endl;
    cout<<"BST平均查找长度: 成功 "<<cal1/2048<<" 失败 "<<uncal1/2048<<endl;
    cout<<"折半查找平均查找长度 成功 "<<cal2/2048<<" 失败 "<<uncal2/2048<<endl;
}

int deletemin(BST *p) {
    if (p->lc == NULL) {
        int tmp = p->data;
        BST *q = p;
        p = p->rc;
        delete(q);
        return tmp;
    }
    else
        return deletemin(p->lc);
}

BST* _delete(BST *p , int x) {
    if (p == NULL)
        return NULL;
    else if (x > p->data)
        p->rc = _delete(p->rc , x);
    else if (x < p->data)
        p->lc = _delete(p->lc , x);
    else {
        BST *q;
        if (p->rc == NULL) {
            q = p;
            p = p->lc;
            delete(q);
        }
        else if (p->lc == NULL) {
            q = p;
            p = p->rc;
            delete(q);
        }
        else {
            p->data = deletemin(p->lc);
        }
    }
    return p;
}

int main() {
    readin();
    mid_search(root1 , num1);
    mid_search(root2 , num2);
    _search();
    // _delete(root1 , 3); //删除操作
    // _delete(root2 , 3);

    system("pause");
    return 0;
}