#include <iostream>
#include <vector>
#include <chrono>

using namespace std;
using namespace std::chrono;

void solve(int col, int n, vector<string>& board, vector<int>& left, vector<int>& ud, vector<int>& ld, int& sol, bool silent) {

    if (col == n) {
        sol++;
        if (!silent) {
            cout << "Solution " << sol << ":\n";
            for (int i = 0; i < n; i++) cout << board[i] << "\n";
            cout << "\n";
        }
        return;
    }
    for (int row = 0; row < n; row++) {
        if (!left[row] && !ld[row + col] && !ud[n - 1 + col - row]) {
            board[row][col] = 'Q';
            left[row] = ld[row + col] = ud[n - 1 + col - row] = 1; 
            
            solve(col + 1, n, board, left, ud, ld, sol, silent); 
            
            board[row][col] = '.';
            left[row] = ld[row + col] = ud[n - 1 + col - row] = 0; 
        }
    }
}

void nQueens(int n, bool silent = true) {
    vector<string> board(n, string(n, '.'));
    vector<int> left(n, 0), ud(2 * n - 1, 0), ld(2 * n - 1, 0);
    int sol = 0;
    
    solve(0, n, board, left, ud, ld, sol, silent);
    
    if (silent) cout << "N = " << n << " -> " << sol << " solutions found. ";
}

int main() {
    cout << "Made by Piyush Tiwari(5I123)\n--- N-Queens (Backtracking) ---\n\n";
    nQueens(4, false); 
    auto run = [](int n) {
        auto t1 = high_resolution_clock::now();
        nQueens(n, true); 
        auto t2 = high_resolution_clock::now();
        cout << "Time: " << duration_cast<microseconds>(t2 - t1).count() << " us\n";
    };

    cout << "--- Execution Time Benchmarks ---\n";
    run(8);  
    run(10); 
    run(12); 

    return 0;
}