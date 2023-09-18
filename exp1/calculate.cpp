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
char* convert(string origin) {\
    CharStack 
    int i=0;
    while(origin[i] != '\0') {
        if(origin[i] > '')
    }

}


//表达式从字符串 变为字符 


int main() {
    string expression = getString();
    cout << expression << endl;

    CharStack charstack(100);
    int i=0;
    //压栈测试
    while(expression[i] != '\0') {
        cout << expression[i];
        charstack.push(expression[i]);
        i++;
    }

    cout << endl;


    //弹栈测试
    while(!charstack.isEmpty()) {
        cout << charstack.pop();
    }

    return 0;
}
