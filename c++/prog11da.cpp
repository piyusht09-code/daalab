#include <iostream>
#include <vector>
#include <string>
#include <chrono>

using namespace std;
using namespace std::chrono;

void naiveMatch(string text, string pat, bool silent = true) {
    int N = text.length(), M = pat.length();
    for (int i = 0; i <= N - M; i++) {
        int j = 0;
        for (j = 0; j < M; j++)
            if (text[i + j] != pat[j]) break;
        if (j == M && !silent) cout << "Naive found match at index " << i << "\n";
    }
}

void rabinKarp(string text, string pat, int q = 101, bool silent = true) {
    int N = text.length(), M = pat.length();
    int d = 256; 
    int p = 0, t = 0, h = 1;

    for (int i = 0; i < M - 1; i++) h = (h * d) % q;

    for (int i = 0; i < M; i++) {
        p = (d * p + pat[i]) % q;
        t = (d * t + text[i]) % q;
    }

    for (int i = 0; i <= N - M; i++) {
        if (p == t) {
            int j = 0;
            for (j = 0; j < M; j++) if (text[i + j] != pat[j]) break;
            if (j == M && !silent) cout << "Rabin-Karp found match at index " << i << "\n";
        }
        if (i < N - M) {
            t = (d * (t - text[i] * h) + text[i + M]) % q;
            if (t < 0) t = t + q;
        }
    }
}

void computeLPS(string pat, int M, vector<int>& lps) {
    int len = 0, i = 1;
    lps[0] = 0;
    while (i < M) {
        if (pat[i] == pat[len]) {
            len++; lps[i] = len; i++;
        } else {
            if (len != 0) len = lps[len - 1];
            else { lps[i] = 0; i++; }
        }
    }
}

void kmpMatch(string text, string pat, bool silent = true) {
    int N = text.length(), M = pat.length();
    vector<int> lps(M);
    computeLPS(pat, M, lps);
    int i = 0, j = 0;
    while (i < N) {
        if (pat[j] == text[i]) { j++; i++; }
        if (j == M) {
            if (!silent) cout << "KMP found match at index " << i - j << "\n";
            j = lps[j - 1];
        } else if (i < N && pat[j] != text[i]) {
            if (j != 0) j = lps[j - 1];
            else i++;
        }
    }
}

int main() {
    cout << "Made by Piyush Tiwari(5I123)\n--- String Matching Algorithms ---\n\n";
    
    string text = "AABAACAADAABAABA";
    string pat = "AABA";
    cout << "Demo Execution (Text: " << text << ", Pattern: " << pat << "):\n";
    naiveMatch(text, pat, false);
    rabinKarp(text, pat, 101, false);
    kmpMatch(text, pat, false);
    string worstText(100000, 'A');
    string worstPat(5000, 'A');
    worstPat += 'B';

    auto run = [&](string name, void(*func)(string, string, bool)) {
        auto t1 = high_resolution_clock::now();
        func(worstText, worstPat, true); 
        auto t2 = high_resolution_clock::now();
        cout << name << ": " << duration_cast<microseconds>(t2 - t1).count() << " us\n";
    };

    cout << "\n--- Worst-Case Time Complexity Analysis ---\n";
    run("Naive      ", naiveMatch);
    run("Rabin-Karp ", [](string t, string p, bool s) { rabinKarp(t, p, 101, s); });
    run("KMP        ", kmpMatch);

    return 0;
}