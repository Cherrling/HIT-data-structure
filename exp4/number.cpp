#include <iostream>
#include <fstream>
#include <random>
#include <ctime>


class XORShift {
public:
    XORShift() {
        seed = time(0); // 使用当前时间作为种子
    }

    // 设置种子
    void setSeed(unsigned int newSeed) {
        seed = newSeed;
    }

    // 生成伪随机数
    unsigned int generateNumber() {
        seed ^= (seed << 13);
        seed ^= (seed >> 17);
        seed ^= (seed << 5);
        return seed;
    }

private:
    unsigned int seed;
};



int main() {
    // 打开文件以写入数据
    std::ofstream outputFile("input_1000000.txt");
    if (!outputFile.is_open()) {
        std::cerr << "Failed to open the output file." << std::endl;
        return 1;
    }


    int n = 1000000; // 数据长度

    outputFile << n << "\n"; // 写入数据长度

    XORShift xorshift;


    // 生成并写入随机整数
    for (int i = 0; i < n; i++) {
        int random_number = xorshift.generateNumber()%10000;
        outputFile << random_number;
        if (i < n - 1) {
            outputFile << " ";
        }
    }

    outputFile.close();

    std::cout << "Random data generated and saved to input.txt." << std::endl;

    return 0;
}
