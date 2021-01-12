//
// Created by leacock on 2021/1/12.
//

#ifndef STRATEGYPATTERN_STRATEGYPATTERN_H
#define STRATEGYPATTERN_STRATEGYPATTERN_H

#include <iostream>


/// Strategy（抽象策略类）： Sort

class Sort {
public:
    virtual ~Sort() = default;
    virtual void sort(int arr[], int len) = 0;
protected:
    Sort() = default;
};

/// ConcreteStrategy（具体策略类）： BubbleSort、SelectionSort、InsertionSort
class BubbleSort : public Sort {
public:
    BubbleSort() {
        std::cout << "BubbleSort Hello" << std::endl;
    }
    ~BubbleSort() override {
        std::cout << "BubbleSort Bye" << std::endl;
    }
    /**冒泡排序
       1 比较相邻的元素。如果第一个比第二个大，就交换它们两个；
       2 对每一对相邻元素作同样的工作，从开始第一对到结尾的最后一对，这样在最后的元素应该会是最大的数；
       3 针对所有的元素重复以上的步骤，除了最后一个；
       4 重复步骤1~3，直到排序完成。
     */
    /// 待排序区间 分  有序区间 无序区间， 每次循环从无序区间中两两比较并交换位置，将最大（最小）冒出来，放入有序区间
    void sort(int arr[], int len) override { // 冒泡排序
        for (int i = 0; i < len; ++i) {
            for (int j = 0; j < len - i - 1; ++j) {
                if (arr[j] > arr[j + 1]) { // 比较相邻的元素
                    auto temp = arr[j+1];        // 元素交换
                    arr[j+1] = arr[j];
                    arr[j] = temp;
                }
            }

        }
    }
};


class SelectionSort : public Sort {
public:
    SelectionSort() {
        std::cout << "SelectionSort Hello" << std::endl;
    }
    ~SelectionSort() override {
        std::cout << "SelectionSort Bye" << std::endl;
    }
    /**选择排序
        1 初始状态：无序区为R[1..n]，有序区为空；
        2 第i趟排序(i=1,2,3…n-1)开始时，当前有序区和无序区分别为R[1..i-1]和R(i..n）。
        该趟排序从当前无序区中-选出关键字最小的记录 R[k]，将它与无序区的第1个记录R交换，
        使R[1..i]和R[i+1..n)分别变为记录个数增加1个的新有序区和记录个数减少1个的新无序区；
        3 n-1趟结束，数组有序化了。
     */
    /// 待排序区间 分  有序区间 无序区间， 每次循环从无序区间找出最小数据插入有序区间尾部
    void sort(int arr[], int len) override { // 选择排序 从小到大排序
        int minIndex;
        for (int i = 0; i < len - 1; ++i) {
            minIndex = i;
            for (int j = i + 1; j < len; ++j) { // 无序区
                if (arr[j] < arr[minIndex]) {
                    minIndex = j; // 找最小
                }
            }
            auto temp = arr[i]; // 交换
            arr[i] = arr[minIndex];
            arr[minIndex] = temp;
        }
    }
};


class InsertionSort : public Sort {
public:
    InsertionSort() {
        std::cout << "InsertionSort Hello" << std::endl;
    }
    ~InsertionSort() override {
        std::cout << "InsertionSort Bye" << std::endl;
    }
    /**插入排序
        1 从第一个元素开始，该元素可以认为已经被排序；
        2 取出下一个元素，在已经排序的元素序列中从后向前扫描；
        3 如果该元素（已排序）大于新元素，将该元素移到下一位置；
        4 重复步骤3，直到找到已排序的元素小于或者等于新元素的位置；
        5 将新元素插入到该位置后；
        6 重复步骤2~5。
     */
    /// 待排序区间 分  有序区间 无序区间， 每次循环取无序区间第一个数据，在有序区间比较找到插入位置
    void sort(int arr[], int len) override { // 插入排序  从小到大排序
        int current;
        for (int i = 0; i < len - 1; i++) { // 从第一个元素开始
            current = arr[i + 1]; // 取出下一个元素 待排序
            int preIndex = i; // 已排序 最后一个元素
            while (preIndex >= 0 && arr[preIndex] > current ) { //  已排序大于待排序元素current，说明 current 在 arr[preIndex] 前面
                arr[preIndex + 1] = arr[preIndex]; // 移位 留出 插入位置
                preIndex--; // 从后向前扫描
            }
            arr[preIndex + 1] = current; // 插入
        }
    }
};

/// Context（上下文类）：Context
class Context {
public:
    Context() {
        sortStrategy = nullptr;
        arr = nullptr;
        len = 0;
        std::cout << "Context Hello" << std::endl;
    }
    ~Context() {
        delete sortStrategy;
        std::cout << "Context Bye" << std::endl;
    }
    void setSortStrategy(Sort* sort){
        delete sortStrategy;
        sortStrategy = sort;
    }
    void sort(){
        sortStrategy->sort(arr, len);
        std::cout << "输出：" << std::endl;
        printSortedArr();
    }
    void setSortArr(int arr[], int len){
        this->arr = arr;
        this->len = len;
    }

    void printSortedArr(){
        std::string arrString;
        for (int i = 0; i < len; i++){
            arrString  += std::to_string(arr[i]) + " ";
        }
        std::cout << arrString <<std::endl;
    }

private:

    Sort* sortStrategy;
    int* arr;
    int len;
};

#endif //STRATEGYPATTERN_STRATEGYPATTERN_H
