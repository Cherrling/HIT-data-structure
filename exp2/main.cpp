#include <fstream>
#include <iostream>
#include <map>
#include <math.h>
#include <queue>
#include <stack>
#include <string>
#include <vector>
using namespace std;

class TreeNode {
public:
    char ch;
    int count;
    bool isChar;
    TreeNode* left;
    TreeNode* right;

    // 构造函数
    TreeNode(char ch, int count, bool isChar)
        : ch(ch)
        , count(count)
        , isChar(isChar)
        , left(nullptr)
        , right(nullptr) {};
    TreeNode() { }
};

class BTree {
private:
    TreeNode* root;

public:
    BTree()
    {
        // root = new TreeNode('#');
        root = nullptr;
    }
    void destroy(TreeNode* node)
    {
        if (node != nullptr) {
            destroy(node->left);
            destroy(node->right);
            delete node;
        }
    }
    ~BTree()
    {
        destroy(root);
    }

    TreeNode* getroot()
    {
        return root;
    }
};

void Huffman_str(TreeNode* curr, string str, map<char, string>& m)
{
    if (curr == nullptr) {
        return;
    }
    if (curr->isChar) {
        m[curr->ch] = str;
    }
    Huffman_str(curr->left, str + '0', m);
    Huffman_str(curr->right, str + '1', m);
}

void PrintTree(TreeNode* n, bool left, string const& indent)
{
    if (n->right) {
        PrintTree(n->right, false, indent + (left ? "|     " : "      "));
    }
    cout << indent;
    // 判断当前节点为左节点还是右节点。然后使用/或者\表示左右节点
    cout << (left ? '\\' : '/');
    // 打印一个当前节点的数据 一定是序号换行的
    cout << "-----" << n->ch << endl;
    if (n->left) {
        PrintTree(n->left, true, indent + (left ? "      " : "|     "));
    }
}

void PrintTree(TreeNode* root)
{
    cout << "图形化打印二叉树" << endl;
    cout << "________________\n"
         << endl;
    if (root->right) {
        PrintTree(root->right, false, "");
    }
    cout << root->ch << endl;
    if (root->left) {
        PrintTree(root->left, true, "");
    }
    cout << "________________\n"
         << endl;
}
void PrintTree(TreeNode* root, int indent = 0)
{
    if (root == nullptr) {
        return;
    }

    // 增加缩进，以表示树的层级结构
    indent += 4;

    // 递归打印右子树
    PrintTree(root->right, indent);

    // 打印当前节点，带有缩进
    for (int i = 4; i < indent; i++) {
        std::cout << " ";
    }
    std::cout << root->count << std::endl;

    // 递归打印左子树
    PrintTree(root->left, indent);
}

void readfile(string filename, string& content)
{
    ifstream file(filename); // 打开文件以供读取

    if (!file.is_open()) {
        cerr << "无法打开文件" << endl;
    }

    string line;

    // 读取第一行内容
    if (getline(file, line)) {
        content = line;
        // cout << "第一行内容: " << line << endl;
    } else {
        // cerr << "文件为空" << endl;
    }

    file.close(); // 关闭文件
}
void readBfile(string filename, string& content)
{
    std::ifstream file(filename, std::ios::binary);
    if (!file.is_open()) {
        cerr << "无法打开文件" << endl;
    }

    string line = "";

    // 读取第一行内容
    char bit;
    while (file.get(bit)) {
        for (int i = 7; i >= 0; --i) {
            // 使用位运算检查并提取每个位的值
            char t = (bit & (1 << i)) ? '1' : '0';
            line += t;
        }
    }
    file.close(); // 关闭文件
    int NULLCount=0;
    string last8Characters = line.substr(line.length() - 8);
    int binaryBase = 1; // 二进制的基数

    // 从右到左遍历二进制字符串
    for (int i = last8Characters.length() - 1; i >= 0; --i) {
        if (last8Characters[i] == '1') {
            NULLCount += binaryBase;
        }
        binaryBase *= 2; // 更新二进制的基数，相当于左移一位
    }

    NULLCount+=8;
    content=line.substr(0, line.length() - NULLCount);
}
int getarrcnt(TreeNode* chars[], int size)
{
    int cnt = 0;
    for (int i = 0; i < size; i++) {
        if (chars[i] != nullptr) {
            cnt++;
        }
    }
    return cnt;
}

void getmin(TreeNode* chars[], int size, TreeNode*& min1, TreeNode*& min2)
{
    for (int i = 0; i < size; i++) {

        if (chars[i] == nullptr) {
            continue;
        }
        if (min1 == nullptr) {
            min1 = chars[i];
        } else if (chars[i]->count < min1->count) {
            min1 = chars[i];
        }
    }
    for (int i = 0; i < size; i++) {
        if (chars[i] == nullptr) {
            continue;
        }
        if (min2 == nullptr && chars[i] != min1) {
            min2 = chars[i];
        } else if (chars[i]->count < min2->count && chars[i] != min1) {
            min2 = chars[i];
        }
    }
}

string decode(string archive, TreeNode* root)
{
    string content = "";
    TreeNode* curr = root;
    for (auto i : archive) {
        if (i == '0') {
            curr = curr->left;
        } else {
            curr = curr->right;
        }
        if (curr->isChar) {
            content += curr->ch;
            curr = root;
            continue;
        }
    }

    return content;
}

void write_into_Bfile(const string& filename, const string& archive)
{
    ofstream binaryFile(filename, ios::binary | ios::out | ios::trunc); // 打开二进制文件并清空
    if (binaryFile.is_open()) {
        vector<char> packedData; // 用于存储打包后的数据

        char currentByte = 0; // 当前字节
        int bitCount = 0; // 记录当前字节中已经写入的位数

        for (size_t i = 0; i < archive.length(); i++) {
            char bit = archive[i];
            if (bit == '0') {
                currentByte <<= 1; // 将当前字节左移一位
            } else if (bit == '1') {
                currentByte = currentByte << 1;
                currentByte = currentByte | 1; // 在当前字节最低位置1
            } else {
                cerr << "无效的字符：" << bit << endl;
                return; // 退出函数以避免写入无效数据
            }

            bitCount++;

            // 如果当前字节已经装满8位，则将其添加到容器并重置
            if (bitCount == 8) {
                packedData.push_back(currentByte);
                currentByte = 0;
                bitCount = 0;
            }
        }

        // 如果还有未装满的字节，将其添加到容器
        if (bitCount > 0) {
            currentByte <<= (8 - bitCount);
            packedData.push_back(currentByte);
        }
        packedData.push_back(8-bitCount);

        // 将打包后的数据写入二进制文件
        binaryFile.write(packedData.data(), packedData.size());
        binaryFile.close();
        cout << "二进制文件写入成功" << endl;
    } else {
        cerr << "无法打开文件" << endl;
    }
}

double calculateCompressionRate(const string& filename, const string& archive)
{
    // 打开原始文件
    ifstream originalFile(filename, ios::binary | ios::ate);
    if (!originalFile.is_open()) {
        cerr << "无法打开原始文件" << endl;
        return -1.0;
    }

    // 获取原始文件的大小
    streampos originalFileSize = originalFile.tellg();
    originalFile.close();

    // 打开压缩后的文件
    ifstream compressedFile(archive, ios::binary | ios::ate);
    if (!compressedFile.is_open()) {
        cerr << "无法打开压缩后的文件" << endl;
        return -1.0;
    }

    // 获取压缩后文件的大小
    streampos compressedFileSize = compressedFile.tellg();
    compressedFile.close();

    // 计算压缩率（百分比）
    double compressionRate = (1.0 - static_cast<double>(compressedFileSize) / static_cast<double>(originalFileSize)) * 100.0;

    return compressionRate;
}

int main()
{

    string content;
    readfile("content.txt", content);
    cout << "源文本：" << endl
         << content << endl;
    cout << endl;
    map<char, int> charCount;
    // 遍历输入字符串
    for (char c : content) {
        // 如果字符已经在map中，增加计数，否则添加新字符并初始化计数为1
        if (charCount.find(c) != charCount.end()) {
            charCount[c]++;
        } else {
            charCount[c] = 1;
        }
    }

    // 打印每个字符和对应的计数
    for (const auto& pair : charCount) {
        cout << "字符 '" << pair.first << "' 出现了 " << pair.second << " 次" << std::endl;
    }
    cout << endl;

    int size = charCount.size();
    TreeNode* chars[size];
    int i = 0;
    for (const auto& pair : charCount) {
        TreeNode* curr = new TreeNode(pair.first, pair.second, 1);
        chars[i] = curr;
        i++;
    }

    TreeNode* examplemin = new TreeNode(-1, 99999999, 0);
    TreeNode* min1;
    TreeNode* min2;
    TreeNode* Huffman = nullptr;

    while (1) {
        if (getarrcnt(chars, size) == 1) {
            for (int i; i < size; i++) {
                if (chars[i] != nullptr) {
                    Huffman = chars[i];
                    break;
                }
            }
            break;
        }
        min1 = examplemin;
        min2 = examplemin;
        getmin(chars, size, min1, min2);
        TreeNode* curr = new TreeNode(-1, (min1->count + min2->count), 0);
        curr->left = min1;
        curr->right = min2;
        for (int i = 0; i < size; i++) {
            if (chars[i] == min1) {
                chars[i] = curr;
            } else if (chars[i] == min2) {
                chars[i] = nullptr;
            }
        }
    }
    // PrintTree(Huffman, 0);

    map<char, string> Huffmanmap;

    Huffman_str(Huffman, "", Huffmanmap);

    for (const auto& pair : Huffmanmap) {
        cout << "字符 '" << pair.first << "' 编码：" << pair.second << std::endl;
    }
    cout << endl;

    string archive = "";
    for (auto i : content) {
        archive += Huffmanmap[i];
    }
    cout << "哈夫曼编码：" << endl
         << archive << endl;
    write_into_Bfile("archive.bin", archive);
    cout << endl;
    string readfromBfile;
    readBfile("archive.bin", readfromBfile);
    // cout<<readfromBfile<<endl;

    // string txt = decode(archive, Huffman);
    string txt = decode(readfromBfile, Huffman);
    cout << "解码后源文件：" << endl
         << txt << endl;
    cout << endl;
    double compressionRate = calculateCompressionRate("content.txt", "archive.bin");
    if (compressionRate >= 0.0) {
        std::cout << "压缩率为: " << compressionRate << "%" << std::endl;
    }
    return 0;
}