#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class DoubleStack {
private:
    double* data;      // 用于存储栈数据的数组
    int capacity;      // 栈的容量
    int topIndex;      // 栈顶索引

public:
    // 构造函数
    DoubleStack(int capacity) {
        this->capacity = capacity;
        this->data = new double[capacity];
        this->topIndex = -1;  // 初始化栈顶索引为-1
    }

    // 析构函数
    ~DoubleStack() {
        delete[] data;
    }

    // 压栈操作
    void push(double value) {
        if (topIndex < capacity - 1) {
            data[++topIndex] = value;
        } else {
            cerr << "栈已满，无法压栈!" << endl;
            exit(1);
        }
    }

    // 弹栈操作
    double pop() {
        if (!isEmpty()) {
            return data[topIndex--];
        } else {
            cerr << "栈为空，无法弹栈!" << endl;
            exit(1);
        }
    }

    // 获取栈顶元素但不弹出
    double peek() {
        if (!isEmpty()) {
            return data[topIndex];
        } else {
            cerr << "栈为空，无法获取栈顶元素!" << endl;
            exit(1);
        }
    }

    // 检查栈是否为空
    [[nodiscard]] bool isEmpty() const {
        return topIndex == -1;
    }

    // 获取栈的大小
    [[nodiscard]] int size() const {
        return topIndex + 1;
    }
};


class CharStack {
private:
    char* data;      // 用于存储栈数据的数组
    int capacity;    // 栈的容量
    int topIndex;    // 栈顶索引

public:
    // 构造函数
    explicit CharStack(int capacity) {
        this->capacity = capacity;
        this->data = new char[capacity];
        this->topIndex = -1;  // 初始化栈顶索引为-1
    }

    // 析构函数
    ~CharStack() {
        delete[] data;
    }

    // 压栈操作
    void push(char value) {
        if (topIndex < capacity - 1) {
            data[++topIndex] = value;
        } else {
            cerr << "栈已满，无法压栈!" << endl;
            exit(1);
        }
    }

    // 弹栈操作
    char pop() {
        if (!isEmpty()) {
            return data[topIndex--];
        } else {
            cerr << "栈为空，无法弹栈!" << endl;
            exit(1);
        }
    }

    // 获取栈顶元素但不弹出
    char peek() {
        if (!isEmpty()) {
            return data[topIndex];
        } else {
            cerr << "栈为空，无法获取栈顶元素!" << endl;
            exit(1);
        }
    }

    // 检查栈是否为空
    [[nodiscard]] bool isEmpty() const {
        return topIndex == -1;
    }

    // 获取栈的大小
    [[nodiscard]] int size() const {
        return topIndex + 1;
    }
};

// 判断运算符优先级
int precedence(char op) {
  if (op == '+' || op == '-') return 1;
  if (op == '*' || op == '/') return 2;
  return 0;
}

//从文件读取算数表达式
string getString() {
    ifstream inputFile("test.txt"); // 打开文件

    if (!inputFile) {
        cerr << "无法打开文件!" << endl;
        return "error";
    }

    string line;
    while (getline(inputFile, line)) {
        // cout << line << endl; // 逐行读取并输出文件内容
    }

    inputFile.close(); // 关闭文件
    return line;
}


//中缀表达式变后缀表达式
string infixToPostfix(string infix) {
    CharStack c_stack(300);
    DoubleStack db_stack(300);
    
    int i=0;
    string postfix = "";
   for(i = 0;i < infix.length(); i++) {
        char c = infix[i];
        if(c == ' ') {continue;}

        else if(c == '(') {
            c_stack.push(c);
        }

        else if(isdigit(c) || c == '.') {
            postfix += c;
        }

        else if(c == ')') {
            while(!c_stack.isEmpty() && c_stack.peek() != '(') {
                postfix += c_stack.peek();
                c_stack.pop();
            }
            c_stack.pop();
        }
        else if(c == '+' || c == '-' || c == '/' || c == '*'){
            while(!c_stack.isEmpty() && precedence(c_stack.peek()) >= precedence(c)) {
                postfix += c_stack.peek();
                c_stack.pop();
            }
            c_stack.push(c);
        }
    }
    while(!c_stack.isEmpty()) {
    postfix += c_stack.peek();
    c_stack.pop();
  }
  return postfix;

}


//表达式从字符串 变为字符 


int main() {
    string expression = getString();
    cout << expression << endl;

    // CharStack charstack(100);
    // int i=0;
    //压栈测试
    // while(expression[i] != '\0') {
    //     cout << expression[i];
    //     charstack.push(expression[i]);
    //     i++;
    // }

    // cout << endl;

    //弹栈测试
    // while(!charstack.isEmpty()) {
    //     cout << charstack.pop();
    // }

    string postfix = infixToPostfix(expression);
    cout << postfix;

    return 0;
}
