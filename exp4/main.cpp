#include <algorithm>
#include <chrono>
#include <fstream>
#include <iostream>
#include <stack>
#include <string>
#include <vector>

using namespace std;

class Sort {
public:
    Sort() { }

    ~Sort() { }

    std::vector<int> selectionSort(const std::vector<int>& arr)
    {
        std::vector<int> sortedVector = arr; // 复制输入向量以避免修改原始数据

        int n = sortedVector.size();
        for (int i = 0; i < n - 1; ++i) {
            int minIndex = i;
            for (int j = i + 1; j < n; ++j) {
                if (sortedVector[j] < sortedVector[minIndex]) {
                    minIndex = j;
                }
            }
            // 交换最小元素和当前元素
            if (minIndex != i) {
                std::swap(sortedVector[i], sortedVector[minIndex]);
            }
        }

        return sortedVector;
    }

    // 分割函数，用于选择基准并将元素分为两部分
    int partition(std::vector<int>& arr, int low, int high)
    {
        int pivot = arr[high]; // 选择数组最后一个元素作为基准
        int i = (low - 1); // 记录小于等于基准的元素的位置

        for (int j = low; j <= high - 1; j++) {
            // 如果当前元素小于等于基准，交换元素位置
            if (arr[j] <= pivot) {
                i++;
                std::swap(arr[i], arr[j]);
            }
        }

        // 交换基准元素和大于基准的元素
        std::swap(arr[i + 1], arr[high]);
        return (i + 1);
    }

    // 快速排序函数
    void quickSort(std::vector<int>& arr, int low, int high)
    {
        if (low < high) {
            // 找到基准元素的位置
            int pivotIndex = partition(arr, low, high);

            // 递归对基准左边的子数组和右边的子数组进行排序
            quickSort(arr, low, pivotIndex - 1);
            quickSort(arr, pivotIndex + 1, high);
        }
    }


    vector<int> quickSort_no_rec(std::vector<int>& arr) {
    std::vector<int> sortedVector = arr; // 复制输入向量以避免修改原始数据

    int n = sortedVector.size();
    std::stack<int> stack;
    stack.push(0);
    stack.push(n - 1);

    while (!stack.empty()) {
        int high = stack.top();
        stack.pop();
        int low = stack.top();
        stack.pop();

        int pivotIndex = partition(sortedVector, low, high);

        if (pivotIndex - 1 > low) {
            stack.push(low);
            stack.push(pivotIndex - 1);
        }
        if (pivotIndex + 1 < high) {
            stack.push(pivotIndex + 1);
            stack.push(high);
        }
    }
    return sortedVector;
}


    // 接口函数，用于调用快速排序并返回排序后的数组
    std::vector<int> quickSort(std::vector<int> arr)
    {
        std::vector<int> sortedVector = arr; // 复制输入向量以避免修改原始数据

        int n = sortedVector.size();
        quickSort(sortedVector, 0, n - 1);
        return sortedVector;
    }

    // 合并两个有序数组
    void merge(std::vector<int>& arr, int left, int middle, int right)
    {
        int n1 = middle - left + 1;
        int n2 = right - middle;

        // 创建临时数组来存储左右两部分的数据
        std::vector<int> leftArray(n1);
        std::vector<int> rightArray(n2);

        for (int i = 0; i < n1; i++) {
            leftArray[i] = arr[left + i];
        }
        for (int j = 0; j < n2; j++) {
            rightArray[j] = arr[middle + 1 + j];
        }

        // 合并临时数组到原数组
        int i = 0, j = 0, k = left;
        while (i < n1 && j < n2) {
            if (leftArray[i] <= rightArray[j]) {
                arr[k] = leftArray[i];
                i++;
            } else {
                arr[k] = rightArray[j];
                j++;
            }
            k++;
        }

        // 处理剩余的元素
        while (i < n1) {
            arr[k] = leftArray[i];
            i++;
            k++;
        }
        while (j < n2) {
            arr[k] = rightArray[j];
            j++;
            k++;
        }
    }

    // 归并排序函数
    void mergeSort(std::vector<int>& arr, int left, int right)
    {
        if (left < right) {
            int middle = left + (right - left) / 2;

            // 递归排序左右两部分
            mergeSort(arr, left, middle);
            mergeSort(arr, middle + 1, right);

            // 合并已排序的左右两部分
            merge(arr, left, middle, right);
        }
    }

    // 接口函数，用于调用归并排序并返回排序后的数组
    std::vector<int> mergeSort(std::vector<int> arr)
    {
        std::vector<int> sortedVector = arr; // 复制输入向量以避免修改原始数据

        int n = sortedVector.size();
        mergeSort(sortedVector, 0, n - 1);
        return sortedVector;
    }
};

void origin()
{

    string filename;
    int x;
    while (1) {
        cout << "0.  Exit" << endl;
        cout << "1.  Sort5000" << endl;
        cout << "2.  Sort100000" << endl;
        cout << "3.  Sort1000000" << endl;
        cin >> x;
        if (x == 0) {
            return;
        } else if (x == 1) {
            filename = "input_5000.txt";
            break;

        } else if (x == 2) {
            filename = "input_100000.txt";
            break;
        } else if (x == 3) {
            filename = "input_1000000.txt";
            break;
        } else {
        }
    }
    // 打开文本文件
    std::ifstream inputFile(filename);
    if (!inputFile.is_open()) {
        std::cerr << "Failed to open the input file." << std::endl;
        return;
    }

    int n;
    inputFile >> n;

    std::vector<int> data(n);
    for (int i = 0; i < n; i++) {
        inputFile >> data[i];
    }
    inputFile.close();

    Sort s;
    std::vector<int> merge_sorted(n);
    std::vector<int> quick_sorted(n);
    std::vector<int> selection_sorted(n);

    // 测量选择排序的执行时间（毫秒）
    auto selectionSortStartTime = std::chrono::high_resolution_clock::now();
    selection_sorted = s.selectionSort(data);
    auto selectionSortEndTime = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> selectionSortTime = selectionSortEndTime - selectionSortStartTime;
    std::cout << "选择排序执行时间: " << selectionSortTime.count() << " 毫秒" << std::endl;

    // 测量归并排序的执行时间（毫秒）
    auto mergeSortStartTime = std::chrono::high_resolution_clock::now();
    merge_sorted = s.mergeSort(data);
    auto mergeSortEndTime = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> mergeSortTime = mergeSortEndTime - mergeSortStartTime;
    std::cout << "归并排序执行时间: " << mergeSortTime.count() << " 毫秒" << std::endl;

    // 测量快速排序的执行时间（毫秒）
    auto quickSortStartTime = std::chrono::high_resolution_clock::now();
    quick_sorted = s.quickSort(data);
    auto quickSortEndTime = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> quickSortTime = quickSortEndTime - quickSortStartTime;
    std::cout << "快速排序执行时间: " << quickSortTime.count() << " 毫秒" << std::endl;
    // 输出排序结果和运行时间
    std::ofstream outputFile("output.txt");

    outputFile << "\nMerge Sort Time: " << mergeSortTime.count() << " \n";

    outputFile << "\nQuick Sort Time: " << quickSortTime.count() << " \n";

    outputFile << "\nSelection Sort Time: " << selectionSortTime.count() << " \n";

    outputFile.close();

    return;
}

void calc_and_draw()
{

    int n;
    vector<int> nums;
    nums.push_back(1000);
    nums.push_back(5000);
    nums.push_back(10000);
    nums.push_back(20000);
    nums.push_back(50000);
    nums.push_back(100000);
    // nums.push_back(150000);

    for (int i = 0; i < nums.size(); i++) {
        n = nums[i];
        // 打开文本文件
        std::ifstream inputFile("input_100000.txt");
        if (!inputFile.is_open()) {
            std::cerr << "Failed to open the input file." << std::endl;
            return;
        }

        std::vector<int> data(n);
        for (int i = 0; i < n; i++) {
            inputFile >> data[i];
        }
        inputFile.close();

        Sort s;
        std::vector<int> merge_sorted(n);
        std::vector<int> quick_sorted(n);
        std::vector<int> selection_sorted(n);

        // 测量选择排序的执行时间（毫秒）
        auto selectionSortStartTime = std::chrono::high_resolution_clock::now();
        // selection_sorted = s.selectionSort(data);
        auto selectionSortEndTime = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> selectionSortTime = selectionSortEndTime - selectionSortStartTime;
        std::cout << "选择排序执行时间: " << selectionSortTime.count() << " 毫秒" << std::endl;

        // 测量归并排序的执行时间（毫秒）
        auto mergeSortStartTime = std::chrono::high_resolution_clock::now();
        // merge_sorted = s.mergeSort(data);
        auto mergeSortEndTime = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> mergeSortTime = mergeSortEndTime - mergeSortStartTime;
        std::cout << "归并排序执行时间: " << mergeSortTime.count() << " 毫秒" << std::endl;

        // 测量快速排序的执行时间（毫秒）
        auto quickSortStartTime = std::chrono::high_resolution_clock::now();
        quick_sorted = s.quickSort(data);
        // quick_sorted = s.quickSort_no_rec(data);
        auto quickSortEndTime = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> quickSortTime = quickSortEndTime - quickSortStartTime;
        std::cout << "快速排序执行时间: " << quickSortTime.count() << " 毫秒" << std::endl;
        // 输出排序结果和运行时间
        // 打开CSV文件以追加数据
        std::ofstream csvFile;
        csvFile.open("data.csv", std::ios::app);

        if (!csvFile.is_open()) {
            std::cerr << "无法打开CSV文件" << std::endl;
            return;
        }

        // 追加数据到CSV文件
        csvFile <<n<<","<< selectionSortTime.count() << "," << mergeSortTime.count() << "," << quickSortTime.count() << std::endl;

        // 关闭文件
        csvFile.close();

        data.clear();
    }

    return;
}

int main()
{
    calc_and_draw();
}