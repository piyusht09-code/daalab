#include <iostream>
#include <vector>
#include <chrono>

using namespace std;
using namespace std::chrono;

void multiply(int n, vector<vector<int>>& A, vector<vector<int>>& B, bool silent = true) {
    vector<vector<int>> C(n, vector<int>(n, 0)); 
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    if (!silent) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                cout << C[i][j] << "\t";
            }
            cout << "\n";
        }
    }
}

int main() {
    cout << "Made by Piyush Tiwari(5I123)\n--- Matrix Multiplication ---\n\n";

    vector<vector<int>> A = {{1, 2}, {3, 4}};
    vector<vector<int>> B = {{5, 6}, {7, 8}};
    
    cout << "Demo (2x2 Output):\n";
    multiply(2, A, B, false);
    
    auto run = [](int n) {
        vector<vector<int>> X(n, vector<int>(n, 1)); 
        auto t1 = high_resolution_clock::now();
        multiply(n, X, X); 
        auto t2 = high_resolution_clock::now();
        cout << "N = " << n << " \tTime: " << duration_cast<microseconds>(t2 - t1).count() << " us\n";
    };

    cout << "\n--- Time Complexity Analysis ---\n";
    run(100); 
    run(300); 
    run(500);
    return 0;
}