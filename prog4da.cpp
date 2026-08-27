#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>

using namespace std;
using namespace std::chrono;

struct Activity {
    int id, start, finish;
};

bool comp(Activity a, Activity b) {
    return a.finish < b.finish; 
}

void activitySelection(vector<Activity>& act, bool silent = true) {
    if (act.empty()) return;
    
    sort(act.begin(), act.end(), comp);
    
    int count = 1;
    int lastEnd = act[0].finish;
    
    if (!silent) cout << "Selected Activity IDs: " << act[0].id << " ";

    for (int i = 1; i < act.size(); i++) {
        if (act[i].start >= lastEnd) {
            if (!silent) cout << act[i].id << " ";
            count++;
            lastEnd = act[i].finish;
        }
    }
    if (!silent) cout << "\nTotal Selected: " << count << "\n";
}

int main() {
    vector<Activity> demo = {{1, 1, 2}, {2, 3, 4}, {3, 0, 6}, {4, 5, 7}, {5, 8, 9}, {6, 5, 9}};
    cout << "--- Activity Selection Output ---\n";
    activitySelection(demo, false);

    cout << "\n--- Execution Time Benchmarks (10,000 activities) ---\n";
    vector<Activity> best, avg, worst;
    for (int i = 0; i < 10000; i++) {
        best.push_back({i, i, i + 1});                       
        avg.push_back({i, rand() % 5000, 5000 + rand() % 5000}); 
        worst.push_back({i, 0, 10000 - i});                 
    }

    auto run = [](string name, vector<Activity>& data) {
        auto t1 = high_resolution_clock::now();
        activitySelection(data); 
        auto t2 = high_resolution_clock::now();
        cout << name << ": " << duration_cast<microseconds>(t2 - t1).count() << " us\n";
    };

    run("Best Case  (No overlaps) ", best);
    run("Avg Case   (Random data) ", avg);
    run("Worst Case (All overlap) ", worst);

    return 0;
}