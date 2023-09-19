# include <stdio.h>
# include <stdlib.h>
# include <windows.h>
# include <string.h>
# include <stdbool.h>

typedef struct Stack
{
    char data[100000];
    int Size;
    int top;
}Stack;
Stack s1;

void creatStack (int maxnsize)
{
    // s.data = (char*)malloc(maxnsize * sizeof(char));
    s1.top = -1;
    s1.Size = maxnsize;
    return;
}

bool Isfull()
{
    return (s1.top == s1.Size - 1);
}

bool Push(char c)
{
    if(Isfull())
    {
        printf("鏍堟弧");
        return false;
    }
    else
    {
        s1.data[++(s1.top)] = c;
        return true;
    }
}

bool Isempty()
{
    return(s1.top == -1);
}

char Pop()
{
    if (Isempty())
    {
        printf("栈空");
        system("pause");
        exit(0);
    }
    else
    {
        return s1.data[(s1.top)--];
    }
}

bool cmp(char a , char b)
{
    if (a == '+' || a == '-')
            return false;
    if (a == '*' || a == '/')
    {
        if (b == '*' || b == '/')
            return false;
        return true;
    }
}

int main()
{   
    int s3[10000];
    int s2top = -1 , s3top = -1;
    char s2[10000];
    char s0[10000];
    scanf("%s" , &s0);
    // printf("%s\n" , s0);
    // printf("%c\n" , s0[0]);
    // printf("%d\n" , strlen(s0));
    
    creatStack(strlen(s0));
    printf("中缀转后缀\n");
    for (int i = 1 ; i < strlen(s0) - 1 ; i++)
    {
        // printf("%d %c ******\n" ,i , s0[i]);
        
        if (s0[i] >= '0' && s0[i] <= '9')
        {
            int num = 0;
            while(s0[i] >= '0' && s0[i] <= '9')
            {
                num = num * 10 + (s0[i] - '0');
                i++;
            }
            // printf("@@@@@%d@@@@@\n" , num);
            s3[++s3top] = num;
            s2[++s2top] = '$';
            i--;
        }
            
        else if (s0[i] == ')')
        {
            while (s1.data[s1.top] != '(')
            {
                s2[++s2top] = Pop();
            }
            Pop();
        }
        else if (s0[i] == '(')
        {
            // printf("@");
            Push(s0[i]);
        }
            
        else
        {
            if (Isempty())
            {
                // printf("1");
                Push(s0[i]);
            }
                
            else
            {
                while (!cmp(s0[i] , s1.data[s1.top]) && !Isempty())
                {
                    if (s1.data[s1.top] == '(')
                        break;
                    s2[++s2top] = Pop();
                }
                Push(s0[i]);
            }
            
        }
        // printf("++++++\n");
        // printf("%d\n" , s1.top);
        // for (int j = 0 ; j <= s1.top ; j++)
            // printf("%c " ,s1.data[j]);
        // printf("\n");
        if (s2top < 0)
            continue;
        int k = 0;
        for (int j = 0 ; j <= s2top ; j++)
        {
            if (s2[j] == '$')
                printf("%d " , s3[k++]); 
            else
                printf("%c " ,s2[j]);
        }
            
        printf("\n");   
    }
    while (!Isempty())
        s2[++s2top] = Pop();
    // for (int j = 0 ; j <= s1.top ; j++)
        // printf("%c " ,s1.data[j]);
    // printf("\n");
    int k = 0;
    for (int i = 0 ; i <= s2top ; i++)
    {
        if (s2[i] == '$')
            printf("%d " , s3[k++]); 
        else
            printf("%c " ,s2[i]);
    }
    printf("\n后缀表达式计算\n");
    k = 0;
    for (int i = 0 ; i <= s2top ; i++)
    {
        if (s2[i] == '$')
            printf("%d " , s3[k++]); 
        else
            printf("%c " ,s2[i]);
    }
    printf("\n");
    int ans[100000] , anstop = -1;
    k = 0;
    for (int i = 0 ; i <= s2top ; i++)
    {
        if (s2[i] == '$')
        {
            ans[++anstop] = s3[k++];
        }
        else
        {
            if (s2[i] == '+')
                ans[anstop - 1] = ans[anstop - 1] + ans[anstop];
            else if (s2[i] == '-')
                ans[anstop - 1] = ans[anstop - 1] - ans[anstop];
            else if (s2[i] == '*')
                ans[anstop - 1] = ans[anstop - 1] * ans[anstop];
            else 
                ans[anstop - 1] = ans[anstop - 1] / ans[anstop];
            anstop--;
            for (int j = i - 1 ; j<= s2top - 2 ; j++)
            {
                s2[j] = s2[j + 2];
            }
            s2top -= 2;
            i -= 2;
            int h = 0;
            int s3n = k;
            for (int j = anstop + 1 ; j <= s3top ; j++)
                ans[j] = s3[s3n++];
            // printf("\n");
            for (int j = 0 ; j <= s2top ; j++)
            {
                if (s2[j] == '$')
                {
                    // if (h <= anstop)
                        printf("%d " , ans[h++]); 
                    // else
                        // printf("%d " , s3[k]);   
                }
                else
                    printf("%c " ,s2[j]);
            }
            printf("\n");
        }

    }
    // printf("%d" , ans[0]);
    printf("\n");   
    system("pause");
    return 0;
}
//#(7+15)*(23-28/4)#
//#9+(3-1)*3+8/2#