#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <math.h>
using namespace std;

struct Node
{
    bool isNum;
    string data;
    Node *next;
};

class STR_List
{
public:
    STR_List() : head(nullptr) {}

    // 添加一个字符串到链表的末尾
    void append(bool isNum, string value)
    {
        // cout<<value<<endl;

        Node *newNode = new Node{isNum, value, nullptr};

        if (!head)
        {
            head = newNode;
            return;
        }

        Node *current = head;
        while (current->next)
        {
            current = current->next;
        }

        current->next = newNode;
    }

    // 打印链表的内容
    void print() const
    {
        Node *current = head;
        while (current)
        {
            cout << current->data << " ";
            current = current->next;
        }
        cout<<endl;
        // cout << "nullptr" << endl;
    }
    Node *returnnext(Node *p)
    {
        if (p == NULL)
        {
            return head;
        }
        else
        {
            return p->next;
        }
    }

    // 析构函数，释放链表的内存
    ~STR_List()
    {
        while (head)
        {
            Node *temp = head;
            head = head->next;
            delete temp;
        }
    }

private:
    Node *head;
};

class FloatStack
{
private:
    float *data;  
    int capacity; 
    int topIndex; 

public:
    // 构造函数
    FloatStack(int capacity)
    {
        this->capacity = capacity;
        this->data = new float[capacity];
        this->topIndex = -1; // 初始化栈顶索引为-1
    }

    // 析构函数
    ~FloatStack()
    {
        delete[] data;
    }

    // 压栈操作
    void push(float value)
    {
        if (topIndex < capacity - 1)
        {
            data[++topIndex] = value;
        }
        else
        {
            cerr << "栈已满，无法压栈!" << endl;
            exit(1);
        }
    }

    // 弹栈操作
    float pop()
    {
        if (!isEmpty())
        {
            return data[topIndex--];
        }
        else
        {
            cerr << "栈为空，无法弹栈!" << endl;
            exit(1);
        }
    }

    // 获取栈顶元素但不弹出
    float peek()
    {
        if (!isEmpty())
        {
            return data[topIndex];
        }
        else
        {
            cerr << "栈为空!" << endl;
            exit(1);
        }
    }

    // 检查栈是否为空
    [[nodiscard]] bool isEmpty() const
    {
        return topIndex == -1;
    }

    // 获取栈的大小
    [[nodiscard]] int size() const
    {
        return topIndex + 1;
    }
};
class CharStack
{
private:
    char *data;   
    int capacity; 
    int topIndex; 

public:
    // 构造函数
    CharStack(int capacity)
    {
        this->capacity = capacity;
        this->data = new char[capacity];
        this->topIndex = -1; // 初始化栈顶索引为-1
    }

    // 析构函数
    ~CharStack()
    {
        delete[] data;
    }

    // 压栈操作
    void push(char value)
    {
        if (topIndex < capacity - 1)
        {
            data[++topIndex] = value;
        }
        else
        {
            cerr << "栈已满，无法压栈!" << endl;
            exit(1);
        }
    }

    // 弹栈操作
    char pop()
    {
        if (!isEmpty())
        {
            return data[topIndex--];
        }
        else
        {
            cerr << "栈为空，无法弹栈!" << endl;
            exit(1);
        }
    }

    // 获取栈顶元素但不弹出
    char peek()
    {
        if (!isEmpty())
        {
            return data[topIndex];
        }
        else
        {
            cerr << "栈为空，无法获取栈顶元素!" << endl;
            exit(1);
        }
    }

    // 检查栈是否为空
    [[nodiscard]] bool isEmpty() const
    {
        return topIndex == -1;
    }

    // 获取栈的大小
    [[nodiscard]] int size() const
    {
        return topIndex + 1;
    }
};
int first(char op)
{
    if (op == '+' || op == '-')
        return 1;
    if (op == '*' || op == '/')
        return 2;
    return 0;
}
bool isOperator(char c)
{
    return c == '+' || c == '-' || c == '*' || c == '/';
}

float str_float(string str)
{
    int dot = 0;
    for (auto &&i : str)
    {
        if (i == '.')
        {
            break;
        }
        else
        {
            dot++;
        }
    }
    float n = 0;
    int i = 0;
    for (auto &&c : str)
    {
        if (c != '.')
        {
            n += (int)(c - 48) * pow(10, dot - i - 1);
            i++;
        }
    }
    return n;
}

int main()
{
    string mid;
    ifstream file("index.txt"); // 打开文件以供读取

    if (!file.is_open())
    {
        cerr << "无法打开文件" << endl;
        return 1;
    }

    string line;

    // 读取第一行内容
    if (getline(file, line))
    {
        mid = line;
        cout << "第一行内容: " << line << endl;
    }
    else
    {
        cerr << "文件为空" << endl;
    }

    file.close(); // 关闭文件

    STR_List List;

    CharStack CharStack(100);

    string temp = "";
    for (int i = 0; i < mid.length(); i++)
    {
        if (mid[i] == ' ')
        {
            continue;
        }

        if (isdigit(mid[i]) || mid[i] == '.')
        {
            temp += mid[i];
        }
        else
        {
            char aaa = mid[i];
            if (temp != "")
            {
                List.append(1, temp);
                List.print();
            }
            temp = "";
            if (CharStack.isEmpty() || CharStack.peek() == '(')
            {
                CharStack.push(mid[i]);
            }
            else if (mid[i] == '(')
            {
                CharStack.push(mid[i]);
            }

            else if (mid[i] == ')')
            {
                while (!CharStack.isEmpty() && CharStack.peek() != '(')
                {
                    List.append(0, string(1, CharStack.pop()));
                    List.print();
                }
                CharStack.pop();
            }
            else if (isOperator(mid[i]))
            {
                while (!CharStack.isEmpty() && first(mid[i]) <= first(CharStack.peek()))
                {
                    List.append(0, string(1, CharStack.pop()));
                    List.print();
                }
                CharStack.push(mid[i]);
            }
        }
    }
    if (temp != "")
    {
        List.append(1, temp);
        List.print();
    }
    while (!CharStack.isEmpty())
    {
        List.append(0, string(1, CharStack.pop()));
        List.print();
    }

    // List.print();

    FloatStack FloatStack(65535);
    Node *p = List.returnnext(NULL);
    while (1)
    {
        if (p->isNum)
        {
            FloatStack.push(str_float(p->data));
        }
        else
        {
            float a, b;
            b = FloatStack.pop();
            a = FloatStack.pop();

            if (p->data == "+")
            {
                FloatStack.push(a + b);
            }
            else if (p->data == "-")
            {
                FloatStack.push(a - b);
            }
            else if (p->data == "*")
            {
                FloatStack.push(a * b);
            }
            else if (p->data == "/")
            {
                FloatStack.push(a / b);
            }
        }

        if (p->next != NULL)
        {
            p = List.returnnext(p);
        }
        else
        {
            break;
        }
    }
    cout<<"res：";
    cout << FloatStack.pop();

    return 0;
}
