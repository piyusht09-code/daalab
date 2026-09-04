#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>

using namespace std;
using namespace std::chrono;

struct Edge { int u, v, w; };
bool comp(Edge a, Edge b) { return a.w < b.w; }
int p[2005];
int find(int i) { return p[i] == i ? i : p[i] = find(p[i]); }
void kruskal(int V, vector<Edge>& edges, bool silent = true) {
    for (int i = 0; i <= V; i++) p[i] = i; 
    
    sort(edges.begin(), edges.end(), comp);
    
    int mst_wt = 0, edges_picked = 0;
    for (auto e : edges) {
        if (find(e.u) != find(e.v)) {
            p[find(e.u)] = find(e.v); 
            mst_wt += e.w;
            if (!silent) cout << "Edge: " << e.u << "-" << e.v << " Wt: " << e.w << "\n";
            if (++edges_picked == V - 1) break; 
        }
    }
    if (!silent) cout << "Total MST Weight: " << mst_wt << "\n";
}

int main() {
    vector<Edge> demo = {{1, 2, 10}, {2, 3, 15}, {1, 3, 5}, {4, 2, 2}, {4, 3, 40}};
    cout << "Made by Piyush Tiwari(5I123)\n--- MST Selected Edges (Demo Graph) ---\n";
    kruskal(4, demo, false); 
    int V = 1000;
    vector<Edge> best, avg, worst;
    
    for (int i = 1; i < V; i++) best.push_back({i, i+1, i});
    for (int i = 1; i <= V; i++) 
        for (int j = 1; j <= 5; j++) avg.push_back({i, (i+j)%V + 1, rand() % 100});
    for (int i = 1; i <= V; i++) 
        for (int j = i + 1; j <= V; j++) worst.push_back({i, j, 10000 - i - j});

    auto run = [](string name, int v, vector<Edge>& edges) {
        auto t1 = high_resolution_clock::now();
        kruskal(v, edges); 
        auto t2 = high_resolution_clock::now();
        cout << name << ": " << duration_cast<microseconds>(t2 - t1).count() << " us\n";
    };

    cout << "\n--- Execution Time Benchmarks (V = 1000) ---\n";
    run("Best Case", V, best);
    run("Avg Case ", V, avg);
    run("Worst Case", V, worst);

    return 0;
}