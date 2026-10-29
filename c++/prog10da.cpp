#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include <algorithm>

using namespace std;
using namespace std::chrono;

void lcs(string X, string Y, bool silent = true) {
    int m = X.length();
    int n = Y.length();
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (X[i - 1] == Y[j - 1])
                dp[i][j] = dp[i - 1][j - 1] + 1;
            else
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
        }
    }

    if (!silent) {
        string lcs_str = "";
        int i = m, j = n;
        while (i > 0 && j > 0) {
            if (X[i - 1] == Y[j - 1]) {
                lcs_str += X[i - 1]; 
                i--; j--;
            } else if (dp[i - 1][j] > dp[i][j - 1]) {
                i--; 
            } else {
                j--; 
            }
        }
        reverse(lcs_str.begin(), lcs_str.end());
        cout << "String 1: " << X << "\nString 2: " << Y << "\n";
        cout << "LCS Length: " << dp[m][n] << "\nLCS String: " << lcs_str << "\n";
    }
}

string generateString(int len) {
    string s = "";
    for (int i = 0; i < len; i++) s += (char)('A' + rand() % 26);
    return s;
}

int main() {
    cout << "Made by Piyush Tiwari(5I123)\n--- Longest Common Subsequence (LCS) ---\n\n";
    
    string s1 = "AGGTAB";
    string s2 = "GXTXAYB";
    cout << "Demo Output:\n";
    lcs(s1, s2, false);

    auto run = [](int n) {
        string str1 = generateString(n);
        string str2 = generateString(n);
        auto t1 = high_resolution_clock::now();
        lcs(str1, str2, true); 
        auto t2 = high_resolution_clock::now();
        cout << "N = " << n << " \tTime: " << duration_cast<microseconds>(t2 - t1).count() << " us\n";
    };

    cout << "\n--- Time Complexity Analysis ---\n";
    run(1000); 
    run(2000); 
    run(3000); 

    return 0;
}