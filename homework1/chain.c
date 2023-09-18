#include <stdio.h>
#include <string.h>
#include <stdlib.h>
typedef struct list
{
    int adj;
    struct list *next;
} LIST;

LIST *Build(int n, int init)
{

    LIST *prePt, *Pt, *head;

    for (int i = 0; i < n; i++)
    {
        Pt = (LIST *)malloc(sizeof(LIST));
        if (Pt == NULL)
        {
            exit(0);
        }
        else
        {
            if (!i)
            {
                head = Pt;
            }
            else
            {
                prePt->next = Pt;
                Pt->next = NULL;
            }
            prePt = Pt;
            if (init == 1)
            {
                Pt->adj = 0;
            }
            else
            {
                scanf("%d", &(Pt->adj));
            }
        }
    }
    return head;
}

void print(LIST *head)
{

    LIST *p = head;
    for (;;)
    {
        printf("%d ", p->adj);
        if (p->next == NULL)
        {
            printf("\n");
            return;
        }
        else
        {
            p = p->next;
        }
    }
}
int number(LIST *head)
{
    LIST *p;
    p = head;
    int n = 1;
    while (1)
    {
        if (p->next == NULL)
        {
            break;
        }
        else
        {
            p = p->next;
            n++;
        }
    }
    return n;
}
LIST *delete(int n, LIST *head)
{
    if (head->next == NULL)
    {
        return head;
    }
    LIST *p;
    if (head->adj == n)
    {
        head = head->next;
    }
    p = head;
    while (1)
    {
        if (p->next == NULL)
        {
            return head;
        }
        if (n == p->next->adj)
        {
            LIST *temp;
            temp = p->next;
            p->next = (p->next)->next;
            free(temp);
        }
        if (p->next == NULL)
        {
            return head;
        }
        p = p->next;
    }
}

void delete_dup(LIST *head)
{
    if (head->next == NULL)
    {
        return;
    }
    LIST *p;
    p = head;
    while (1)
    {
        if (p->next == NULL)
        {
            return;
        }
        if (p->adj == p->next->adj)
        {
            LIST *temp;
            temp = p->next;
            p->next = (p->next)->next;
            free(temp);
        }
        else
        {

            if (p->next == NULL)
            {
                return;
            }
            p = p->next;
        }
    }
}

void reverse(LIST *head)
{
    int n;
    LIST *p;
    n = number(head);
    int m = 1;
    LIST *pm;
    LIST *pn;
    while (m < n)
    {
        p = head;
        for (int i = 1; i <= n; i++)
        {
            if (i == m)
            {
                pm = p;
            }
            if (i == n)
            {
                pn = p;
            }
            if (p->next != NULL)
            {

                p = p->next;
            }
        }
        p = head;

        int temp;
        temp = pn->adj;
        pn->adj = pm->adj;
        pm->adj = temp;
        m++;
        n--;
    }
}

LIST *move_lr(int k, int right, LIST *head)
{
    int n = 1;
    LIST *p;
    p = head;
    while (1)
    {
        if (p->next != NULL)
        {
            p = p->next;
            n++;
        }
        else
        {
            p->next = head;
            break;
        }
    }
    p = head;
    LIST *prep;
    if (right == 1)
    {
        k = n - k;
    }

    for (int i = 0; i < k; i++)
    {
        prep = p;
        p = p->next;
    }
    prep->next = NULL;
    return p;
}

LIST *merge(LIST *l1, LIST *l2)
{
    int n;
    LIST *head;
    LIST *p1;
    LIST *p2;
    LIST *p;
    p1 = l1;
    p2 = l2;
    if (p1 == NULL)
    {
        p->next = p2;
        return head;
    }
    if (p2 == NULL)
    {
        p->next = p1;
        return head;
    }
    if (p1->adj < p2->adj)
    {
        head = p1;
        if (p1->next == NULL)
        {
            p->next = p2;
            return head;
        }
        p1 = p1->next;
    }
    else
    {
        head = p2;
        if (p2->next == NULL)
        {
            p->next = p1;
            return head;
        }
        p2 = p2->next;
    }
    p = head;
    while (1)
    {

        if (p1->adj < p2->adj)
        {
            p->next = p1;
            p = p->next;
            if (p1->next == NULL)
            {
                p->next = p2;
                return head;
            }
            else
            {
                p1 = p1->next;
            }
        }
        else
        {
            p->next = p2;
            p = p->next;
            if (p2->next == NULL)
            {
                p->next = p1;
                return head;
            }
            else
            {
                p2 = p2->next;
            }
        }
    }
}

int main()
{
    LIST *head;
    LIST *l1;
    LIST *l2;
    printf("in:\n");
    head = Build(6, 0);
    // l1 = Build(5, 0);
    // l2 = Build(5, 0);
    head = delete (3, head);
    // delete_dup(head);
    // print(head);
    // reverse(head);
    // head = move_lr(2, 1, head);
    // head = merge(l1, l2);
    printf("out:\n");
    print(head);
}