#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class DoubleStack {
private:
    double* data;      // ���ڴ洢ջ���ݵ�����
    int capacity;      // ջ������
    int topIndex;      // ջ������

public:
    // ���캯��
    DoubleStack(int capacity) {
        this->capacity = capacity;
        this->data = new double[capacity];
        this->topIndex = -1;  // ��ʼ��ջ������Ϊ-1
    }

    // ��������
    ~DoubleStack() {
        delete[] data;
    }

    // ѹջ����
    void push(double value) {
        if (topIndex < capacity - 1) {
            data[++topIndex] = value;
        } else {
            cerr << "ջ�������޷�ѹջ!" << endl;
            exit(1);
        }
    }

    // ��ջ����
    double pop() {
        if (!isEmpty()) {
            return data[topIndex--];
        } else {
            cerr << "ջΪ�գ��޷���ջ!" << endl;
            exit(1);
        }
    }

    // ��ȡջ��Ԫ�ص�������
    double peek() {
        if (!isEmpty()) {
            return data[topIndex];
        } else {
            cerr << "ջΪ�գ��޷���ȡջ��Ԫ��!" << endl;
            exit(1);
        }
    }

    // ���ջ�Ƿ�Ϊ��
    [[nodiscard]] bool isEmpty() const {
        return topIndex == -1;
    }

    // ��ȡջ�Ĵ�С
    [[nodiscard]] int size() const {
        return topIndex + 1;
    }
};


class CharStack {
private:
    char* data;      // ���ڴ洢ջ���ݵ�����
    int capacity;    // ջ������
    int topIndex;    // ջ������

public:
    // ���캯��
    explicit CharStack(int capacity) {
        this->capacity = capacity;
        this->data = new char[capacity];
        this->topIndex = -1;  // ��ʼ��ջ������Ϊ-1
    }

    // ��������
    ~CharStack() {
        delete[] data;
    }

    // ѹջ����
    void push(char value) {
        if (topIndex < capacity - 1) {
            data[++topIndex] = value;
        } else {
            cerr << "ջ�������޷�ѹջ!" << endl;
            exit(1);
        }
    }

    // ��ջ����
    char pop() {
        if (!isEmpty()) {
            return data[topIndex--];
        } else {
            cerr << "ջΪ�գ��޷���ջ!" << endl;
            exit(1);
        }
    }

    // ��ȡջ��Ԫ�ص�������
    char peek() {
        if (!isEmpty()) {
            return data[topIndex];
        } else {
            cerr << "ջΪ�գ��޷���ȡջ��Ԫ��!" << endl;
            exit(1);
        }
    }

    // ���ջ�Ƿ�Ϊ��
    [[nodiscard]] bool isEmpty() const {
        return topIndex == -1;
    }

    // ��ȡջ�Ĵ�С
    [[nodiscard]] int size() const {
        return topIndex + 1;
    }
};

// �ж���������ȼ�
int precedence(char op) {
  if (op == '+' || op == '-') return 1;
  if (op == '*' || op == '/') return 2;
  return 0;
}

//���ļ���ȡ�������ʽ
string getString() {
    ifstream inputFile("test.txt"); // ���ļ�

    if (!inputFile) {
        cerr << "�޷����ļ�!" << endl;
        return "error";
    }

    string line;
    while (getline(inputFile, line)) {
        // cout << line << endl; // ���ж�ȡ������ļ�����
    }

    inputFile.close(); // �ر��ļ�
    return line;
}


//��׺���ʽ���׺���ʽ
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


//���ʽ���ַ��� ��Ϊ�ַ� 


int main() {
    string expression = getString();
    cout << expression << endl;

    // CharStack charstack(100);
    // int i=0;
    //ѹջ����
    // while(expression[i] != '\0') {
    //     cout << expression[i];
    //     charstack.push(expression[i]);
    //     i++;
    // }

    // cout << endl;

    //��ջ����
    // while(!charstack.isEmpty()) {
    //     cout << charstack.pop();
    // }

    string postfix = infixToPostfix(expression);
    cout << postfix;

    return 0;
}
