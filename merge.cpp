#include <iostream>
#include <vector>
#include <cstdlib>
#include <omp.h>
#include <chrono>
using namespace std;
using namespace chrono;

void merge(vector<int>& arr, int left, int mid, int right) {
    vector<int> leftArr(arr.begin() + left, arr.begin() + mid + 1);
    vector<int> rightArr(arr.begin() + mid + 1, arr.begin() + right + 1);

    int i = 0, j = 0, k = left;
    while (i < leftArr.size() && j < rightArr.size()) {
        if (leftArr[i] <= rightArr[j]) {
            arr[k++] = leftArr[i++];
        } else {
            arr[k++] = rightArr[j++];
        }
    }
    while (i < leftArr.size()) arr[k++] = leftArr[i++];
    while (j < rightArr.size()) arr[k++] = rightArr[j++];
}

void mergeSort(vector<int>& arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

void parallelMergeSort(vector<int>& arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        #pragma omp parallel sections
        {
            #pragma omp section
            parallelMergeSort(arr, left, mid);

            #pragma omp section
            parallelMergeSort(arr, mid + 1, right);
        }
        merge(arr, left, mid, right);
    }
}

int main() {
    int n = 10000;
    vector<int> arr(n);
    for (int i = 0; i < n; i++) arr[i] = rand() % 10000;

    vector<int> arr1 = arr, arr2 = arr;

    auto start = high_resolution_clock::now();
    mergeSort(arr1, 0, n - 1);
    auto end = high_resolution_clock::now();
    cout << "Sequential Merge Sort Time: " 
         << duration_cast<milliseconds>(end - start).count() << " ms\n";

    start = high_resolution_clock::now();
    parallelMergeSort(arr2, 0, n - 1);
    end = high_resolution_clock::now();
    cout << "Parallel Merge Sort Time: " 
         << duration_cast<milliseconds>(end - start).count() << " ms\n";

    return 0;
}

