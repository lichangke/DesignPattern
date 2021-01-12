#include "StrategyPattern.h"

int main() {
    auto* ctx = new Context();
    // 冒泡排序
    std::cout << "==========冒泡排序：==========" << std::endl;
    int arr1[] = { 3,40,-1,-45,44,56,9,-33 };
    ctx->setSortArr(arr1, sizeof(arr1)/sizeof(int));
    std::cout << "输入：" << std::endl;
    ctx->printSortedArr();
    ctx->setSortStrategy(new BubbleSort());
    ctx->sort();

    // 选择排序
    std::cout << "==========选择排序：==========" << std::endl;
    int arr2[] = { 13,4,-11,-5,14,6,9,-3 };
    ctx->setSortArr(arr2, sizeof(arr2)/sizeof(int));
    std::cout << "输入：" << std::endl;
    ctx->printSortedArr();
    ctx->setSortStrategy(new SelectionSort());
    ctx->sort();

    // 插入排序
    std::cout << "==========插入排序：==========" << std::endl;
    int arr3[] = { 30,-40,1,45,-4,1,-9,3 };
    ctx->setSortArr(arr3, sizeof(arr3)/sizeof(int));
    std::cout << "输入：" << std::endl;
    ctx->printSortedArr();
    ctx->setSortStrategy(new InsertionSort());
    ctx->sort();

    delete ctx;
    return 0;
}
