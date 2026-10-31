#include <iostream>
#include <vector>
#include <chrono>
#include <iomanip>
#include <algorithm>

using namespace std;
using namespace std::chrono;

void compAndSwap(vector<int>& a, int i, int j, int dir) {
    if (dir == (a[i] > a[j])) {
        swap(a[i], a[j]);
    }
}

void bitonicMerge(vector<int>& a, int low, int cnt, int dir) {
    if (cnt > 1) {
        int k = cnt / 2;
        for (int i = low; i < low + k; i++) {
            compAndSwap(a, i, i + k, dir);
        }
        bitonicMerge(a, low, k, dir);
        bitonicMerge(a, low + k, k, dir);
    }
}

void bitonicSort(vector<int>& a, int low, int cnt, int dir) {
    if (cnt > 1) {
        int k = cnt / 2;
        bitonicSort(a, low, k, 1);       
        bitonicSort(a, low + k, k, 0);   
        bitonicMerge(a, low, cnt, dir);  
    }
}

void printArray(const vector<int>& a) {
    for (int num : a) cout << num << " ";
    cout << "\n";
}

int main() {
    cout << "Made by Piyush Tiwari(5I123)\n--- Sorting Network (Bitonic Sort) ---\n\n";
    
    vector<int> demo = {3, 7, 4, 8, 6, 2, 1, 5};
    cout << "--- Demo Execution ---\n";
    cout << left << setw(15) << "Input Array" << ": ";
    printArray(demo);
    
    bitonicSort(demo, 0, demo.size(), 1); 
    
    cout << left << setw(15) << "Sorted Array" << ": ";
    printArray(demo);
    cout << "\n";

    cout << "--- Time Complexity Analysis ---\n";
    cout << string(70, '-') << "\n";
    cout << "| " << left << setw(10) << "Size (N)" 
         << "| " << setw(16) << "Best Case (us)"
         << "| " << setw(16) << "Worst Case (us)"
         << "| " << setw(18) << "Average Case (us)" << "|\n";
    cout << string(70, '-') << "\n";

    auto measureTime = [](vector<int>& arr) {
        auto t1 = high_resolution_clock::now();
        bitonicSort(arr, 0, arr.size(), 1); 
        auto t2 = high_resolution_clock::now();
        return duration_cast<microseconds>(t2 - t1).count();
    };

    auto run = [&](int size) {
        vector<int> best(size), worst(size), avg(size);
        for (int i = 0; i < size; i++) {
            best[i] = i;                   
            worst[i] = size - i;           
            avg[i] = rand() % 10000;       
        }
        
        long long tBest = measureTime(best);
        long long tWorst = measureTime(worst);
        long long tAvg = measureTime(avg);

        cout << "| " << left << setw(10) << size 
             << "| " << setw(16) << tBest 
             << "| " << setw(16) << tWorst 
             << "| " << setw(18) << tAvg << "|\n";
    };

    run(4096);
    run(8192);
    run(16384);
    
    cout << string(70, '-') << "\n";

    return 0;
}