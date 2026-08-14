#include <iostream>
#include <vector>
#include <chrono>

using namespace std;
using namespace chrono;

int linearSearch(const vector<int>& arr, int target) {
    for (int i = 0; i < arr.size(); i++) {
        if (arr[i] == target) {
            return i;
        }
    }
    return -1;
}

int binarySearch(const vector<int>& arr, int target) {
    int left = 0;
    int right = arr.size() - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (arr[mid] == target) {
            return mid;
        } 
        else if (arr[mid] < target) {
            left = mid + 1;
        } 
        else {
            right = mid - 1;
        }
    }
    return -1;
}

int main() {
    int N = 100000000;
    cout << "Generating array of " << N << " elements...\n";
    
    vector<int> arr(N);
    for (int i = 0; i < N; i++) {
        arr[i] = i + 1;
    }

    int target = N; 
    cout << "Searching for target: " << target << "\n\n";

    auto startLinear = high_resolution_clock::now();
    
    int linearResult = linearSearch(arr, target);
    
    auto stopLinear = high_resolution_clock::now();
    duration<double, milli> linearDuration = stopLinear - startLinear;

    cout << "Linear Search Result : Found at index " << linearResult << "\n";
    cout << "Linear Search Time   : " << linearDuration.count() << " ms\n\n";

    auto startBinary = high_resolution_clock::now();
    
    int binaryResult = binarySearch(arr, target);
    
    auto stopBinary = high_resolution_clock::now();
    duration<double, milli> binaryDuration = stopBinary - startBinary;

    cout << "Binary Search Result : Found at index " << binaryResult << "\n";
    cout << "Binary Search Time   : " << binaryDuration.count() << " ms\n";

    return 0;
}