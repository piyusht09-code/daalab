#include <iostream>
#include <vector>
#include <chrono>

using namespace std;
using namespace std::chrono;

struct Edge { int u, v, w; };

void printPath(int v, vector<int>& parent) {
    if (parent[v] == -1) { cout << v; return; }
    printPath(parent[v], parent);
    cout << "->" << v;
}

void bellmanFord(int src, int V, vector<Edge>& edges, bool silent = true) {
    vector<int> dist(V, 999999);
    vector<int> parent(V, -1);
    dist[src] = 0;

    for (int i = 1; i <= V - 1; i++) {
        bool updated = false; 
        for (auto e : edges) {
            if (dist[e.u] != 999999 && dist[e.u] + e.w < dist[e.v]) {
                dist[e.v] = dist[e.u] + e.w;
                parent[e.v] = e.u;
                updated = true;
            }
        }
        if (!updated) break; 
    }

    if (!silent) {
        cout << "Node\tDistance\tPath\n------------------------------\n";
        for (int i = 0; i < V; i++) {
            cout << i << "\t" << dist[i] << "\t\t";
            printPath(i, parent); cout << "\n";
        }
    }
}

int main() {
    vector<Edge> demo = {{0, 1, 4}, {0, 2, 5}, {1, 3, -2}, {2, 3, 3}};
    
    cout << "Made by Piyush Tiwari(5I123)\n--- Bellman-Ford Shortest Paths ---\n";
    bellmanFord(0, 4, demo, false);

    int V = 500;
    vector<Edge> best, avg, worst;
    
    for (int i = 0; i < V - 1; i++) best.push_back({i, i+1, 1});
    for (int i = 0; i < V; i++) 
        for (int j = 1; j <= 5; j++) avg.push_back({i, (i+j)%V, rand()%100});
    for (int i = V - 1; i >= 0; i--) 
        for (int j = V - 1; j >= 0; j--) if (i != j) worst.push_back({i, j, 1});

    auto run = [](string name, int v, vector<Edge>& edges) {
        auto t1 = high_resolution_clock::now();
        bellmanFord(0, v, edges); 
        auto t2 = high_resolution_clock::now();
        cout << name << ": " << duration_cast<microseconds>(t2 - t1).count() << " us\n";
    };

    cout << "\n--- Execution Time Benchmarks (V = 500) ---\n";
    run("Best Case", V, best);
    run("Avg Case ", V, avg);
    run("Worst Case", V, worst);

    return 0;
}