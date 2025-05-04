#include <iostream>
#include <vector>
#include <omp.h>
#include <climits>
using namespace std;

void min_reduction(const vector<int>& arr) {
    int min_value = INT_MAX;
    #pragma omp parallel for reduction(min:min_value)
    for (int i = 0; i < arr.size(); i++) {
        min_value = min(min_value, arr[i]);  // No need for explicit if
    }
    cout << "Minimum value: " << min_value << endl;
}

void max_reduction(const vector<int>& arr) {
    int max_value = INT_MIN;
    #pragma omp parallel for reduction(max:max_value)
    for (int i = 0; i < arr.size(); i++) {
        max_value = max(max_value, arr[i]);  // No need for explicit if
    }
    cout << "Maximum value: " << max_value << endl;
}

void sum_reduction(const vector<int>& arr) {
    int sum = 0;
    #pragma omp parallel for reduction(+:sum)
    for (int i = 0; i < arr.size(); i++) {
        sum += arr[i];
    }
    cout << "Sum: " << sum << endl;
}

void average_reduction(const vector<int>& arr) {
    int sum = 0;
    #pragma omp parallel for reduction(+:sum)
    for (int i = 0; i < arr.size(); i++) {
        sum += arr[i];
    }
    double average = static_cast<double>(sum) / arr.size();
    cout << "Average: " << average << endl;
}

int main() {
    // Replace interactive input with hardcoded test data
    vector<int> arr = {10, 20, 5, 7, 30, 1};

    min_reduction(arr);
    max_reduction(arr);
    sum_reduction(arr);
    average_reduction(arr);

    return 0;
}
