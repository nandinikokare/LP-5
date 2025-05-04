#include <iostream>
#include <vector>
#include <cstdlib>
#include <omp.h>
#include <chrono>

using namespace std;
using namespace chrono;

void bubbleSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

void parallelBubbleSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        #pragma omp parallel for
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

int main() {
    int n = 10000;
    vector<int> arr(n);
    for (int i = 0; i < n; i++) arr[i] = rand() % 10000;

    vector<int> arr1 = arr, arr2 = arr;

    auto start = high_resolution_clock::now();
    bubbleSort(arr1);
    auto end = high_resolution_clock::now();
    cout << "Sequential Bubble Sort Time: " 
         << duration_cast<milliseconds>(end - start).count() << " ms\n";

    start = high_resolution_clock::now();
    parallelBubbleSort(arr2);
    end = high_resolution_clock::now();
    cout << "Parallel Bubble Sort Time: " 
         << duration_cast<milliseconds>(end - start).count() << " ms\n";

    return 0;
}

