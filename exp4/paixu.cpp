#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <algorithm>

// 归并排序
void merge(std::vector<int>& arr, int left, int mid, int right) {
    // 计算左子数组和右子数组的大小
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // 创建临时数组来存储左右子数组
    std::vector<int> left_half(n1);
    std::vector<int> right_half(n2);

    // 将数据复制到临时数组中
    for (int i = 0; i < n1; i++) {
        left_half[i] = arr[left + i];
    }
    for (int i = 0; i < n2; i++) {
        right_half[i] = arr[mid + 1 + i];
    }

    // 合并左右子数组，排序数据
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (left_half[i] <= right_half[j]) {
            arr[k] = left_half[i];
            i++;
        } else {
            arr[k] = right_half[j];
            j++;
        }
        k++;
    }

    // 处理剩余的元素
    while (i < n1) {
        arr[k] = left_half[i];
        i++;
        k++;
    }
    while (j < n2) {
        arr[k] = right_half[j];
        j++;
        k++;
    }
}

void merge_sort(std::vector<int>& arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2; // 计算中间索引
        merge_sort(arr, left, mid); // 递归排序左半部分
        merge_sort(arr, mid + 1, right); // 递归排序右半部分
        merge(arr, left, mid, right); // 合并左右子数组
    }
}

// 快速排序
int partition(std::vector<int>& arr, int low, int high) {
    int pivot = arr[high]; // 选择最后一个元素作为主元素
    int i = (low - 1); // 初始化较小元素的索引

    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            std::swap(arr[i], arr[j]);
        }
    }

    std::swap(arr[i + 1], arr[high]); // 将主元素放在正确的位置
    return (i + 1); // 返回主元素的索引
}

void quick_sort(std::vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high); // 获取主元素的索引
        quick_sort(arr, low, pi - 1); // 递归排序左半部分
        quick_sort(arr, pi + 1, high); // 递归排序右半部分
    }
}

// 选择排序
void selection_sort(std::vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        int min_index = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[min_index]) {
                min_index = j;
            }
        }
        if (min_index != i) {
            std::swap(arr[i], arr[min_index]);
        }
    }
}

int main() {
    // 打开文本文件
    std::ifstream inputFile("input.txt");
    if (!inputFile.is_open()) {
        std::cerr << "Failed to open the input file." << std::endl;
        return 1;
    }

    int n;
    inputFile >> n;

    std::vector<int> data(n);
    for (int i = 0; i < n; i++) {
        inputFile >> data[i];
    }

    inputFile.close();

    // 复制数据以备排序
    std::vector<int> merge_sorted = data;
    std::vector<int> quick_sorted = data;
    std::vector<int> selection_sorted = data;

    // 归并排序
    auto merge_start = std::chrono::high_resolution_clock::now();
    merge_sort(merge_sorted, 0, n - 1);
    auto merge_end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> merge_time = merge_end - merge_start;

    // 快速排序
    auto quick_start = std::chrono::high_resolution_clock::now();
    quick_sort(quick_sorted, 0, n - 1);
    auto quick_end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> quick_time = quick_end - quick_start;

    // 选择排序
    auto selection_start = std::chrono::high_resolution_clock::now();
    selection_sort(selection_sorted);
    auto selection_end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> selection_time = selection_end - selection_start;

    // 输出排序结果和运行时间
    std::ofstream outputFile("output.txt");

    outputFile << "Merge Sorted: ";
    for (int num : merge_sorted) {
        outputFile << num << " ";
    }
    outputFile << "\nMerge Sort Time: " << merge_time.count() << " seconds\n";

    outputFile << "Quick Sorted: ";
    for (int num : quick_sorted) {
        outputFile << num << " ";
    }
    outputFile << "\nQuick Sort Time: " << quick_time.count() << " seconds\n";

    outputFile << "Selection Sorted: ";
    for (int num : selection_sorted) {
        outputFile << num << " ";
    }
    outputFile << "\nSelection Sort Time: " << selection_time.count() << " seconds\n";

    outputFile.close();

    return 0;
}
