#include <iostream>
#include <vector>
#include <queue>
#include <chrono>

using namespace std;
using namespace std::chrono;

typedef pair<int, int> pii;

void printPath(int v, vector<int>& parent) {
    if (parent[v] == -1) { cout << v; return; }
    printPath(parent[v], parent);
    cout << "->" << v;
}

void dijkstra(int src, int V, vector<pii> adj[], bool silent = true) {
    vector<int> dist(V, 1e9);
    vector<int> parent(V, -1); 
    priority_queue<pii, vector<pii>, greater<pii>> pq;
    
    dist[src] = 0; 
    pq.push({0, src});

    while (!pq.empty()) {
        int d = pq.top().first;
        int u = pq.top().second;
        pq.pop();
        
        if (d > dist[u]) continue; 
        
        for (auto e : adj[u]) {
            int v = e.first, w = e.second;
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                parent[v] = u; 
                pq.push({dist[v], v});
            }
        }
    }
    
    if (!silent) {
        cout << "Node\tDistance\tPath\n";
        cout << "------------------------------\n";
        for (int i = 0; i < V; i++) {
            cout << i << "\t" << dist[i] << "\t\t";
            printPath(i, parent); 
            cout << "\n";
        }
    }
}

int main() {
    vector<pii> demo[4];
    demo[0].push_back({1, 10}); demo[0].push_back({2, 3}); 
    demo[2].push_back({1, 1});  demo[1].push_back({3, 2}); 
    demo[2].push_back({3, 8});

    cout << "Made by Piyush Tiwari(5I123)\n--- Dijkstra Shortest Paths ---\n";
    dijkstra(0, 4, demo, false);

    int V = 1000;
    vector<pii> best[1000], avg[1000], worst[1000];
    
    for (int i = 0; i < V - 1; i++) best[i].push_back({i+1, 1});
    for (int i = 0; i < V; i++) 
        for (int j = 1; j <= 5; j++) avg[i].push_back({(i+j)%V, rand()%100});
    for (int i = 0; i < V; i++) 
        for (int j = 0; j < V; j++) if(i != j) worst[i].push_back({j, 1});

    auto run = [](string name, int v, vector<pii> adj[]) {
        auto t1 = high_resolution_clock::now();
        dijkstra(0, v, adj); 
        auto t2 = high_resolution_clock::now();
        cout << name << ": " << duration_cast<microseconds>(t2 - t1).count() << " us\n";
    };

    cout << "\n--- Execution Time Benchmarks (V = 1000) ---\n";
    run("Best Case", V, best);
    run("Avg Case ", V, avg);
    run("Worst Case", V, worst);

    return 0;
}