#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void print(int *arr, int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("%d", arr[i]);
    }
    printf("\n");
}

int delete(int x, int *arr, int n)
{
    for (int i = 0; i < n;)
    {
        if (arr[i] == x)
        {
            n--;
            for (int j = i; j < n; j++)
            {
                arr[j] = arr[j + 1];
            }
        }
        else
        {
            i++;
        }
    }
    return n;
}

int del_dup(int *arr, int n)
{
    for (int i = 0; i < n - 1;)
    {
        if (arr[i] == arr[i + 1])
        {
            n--;
            for (int j = i + 1; j < n; j++)
            {
                arr[j] = arr[j + 1];
            }
        }
        else
        {

            i++;
        }
    }
    return n;
}
void reverse(int *arr, int n)
{
    for (int i = 0; i < n - i - 1; i++)
    {
        int t;
        t = arr[i];
        arr[i] = arr[n - i - 1];
        arr[n - i - 1] = t;
    }
}

void move_lr(int x, int right, int *arr, int n)
{
    x = x % n;
    if (right == 1)
    {
        x = n - x;
    }
    int arr2[x];
    for (int i = 0; i < x; i++)
    {
        arr2[i] = arr[i];
    }
    for (int i = 0; i < n-x; i++)
    {
        arr[i] = arr[i + x];
    }
    int j=0;
    for (int i = n-x; i < n; i++)
    {
        arr[i] = arr2[j];
        j++;
    }
}
void merge(int *arr, int *arr1, int *arr2, int n1, int n2)
{
    int j = 0;
    int k = 0;
    for (int i = 0; i < n1 + n2; i++)
    {
        if (j >= n1)
        {
            arr[i] = arr2[k];
            k++;
        }
        else if (k >= n2)
        {
            arr[i] = arr1[j];
            j++;
        }
        else if (arr1[j] < arr2[k])
        {
            arr[i] = arr1[j];
            j++;
        }
        else
        {
            arr[i] = arr2[k];
            k++;
        }
    }
}
int main()
{
    int arr1[5] = {1, 3, 3, 7, 9};
    int arr2[5] = {2, 4, 6, 8, 10};
    int n = 5;
    // printf("in:\n");
    // print(arr1, 5);
    // print(arr2, 5);
    // n=delete(3,arr1,n);
    // n = del_dup(arr1, n);
    // reverse(arr1, n);
    // move_lr(2,1,arr1,n);
    int arr[5+5];
    merge(arr,arr1,arr2,5,5);
    printf("out:\n");
    // print(arr1, n);
    print(arr, 10);
}
