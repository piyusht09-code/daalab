#include <iostream>
#include <queue>
#include <unordered_map>
#include <chrono>
#include <string>

using namespace std;
using namespace std::chrono;

struct Node {
    char ch; int f; Node *l, *r;
    Node(char c, int f, Node* l = NULL, Node* r = NULL) : ch(c), f(f), l(l), r(r) {}
};

struct Comp {
    bool operator()(Node* a, Node* b) { return a->f > b->f; }
};

void freeTree(Node* root) {
    if (!root) return;
    freeTree(root->l);
    freeTree(root->r);
    delete root;
}

void printCodes(Node* root, string str) {
    if (!root) return;
    if (!root->l && !root->r) cout << root->ch << ": " << str << "\n";
    printCodes(root->l, str + "0");
    printCodes(root->r, str + "1");
}

void huffman(string s, bool show_codes = false) {
    unordered_map<char, int> freq;
    for (char c : s) freq[c]++;

    priority_queue<Node*, vector<Node*>, Comp> pq;
    for (auto p : freq) pq.push(new Node(p.first, p.second)); 

    if (pq.empty()) return;

    while (pq.size() > 1) {
        Node *l = pq.top(); pq.pop();
        Node *r = pq.top(); pq.pop();
        pq.push(new Node('\0', l->f + r->f, l, r));
    }
    
    Node* root = pq.top();
    if (show_codes) printCodes(root, "");
    
    freeTree(root); 
}

int main() {
    cout << "--- Huffman Codes(Piyush Tiwari(5I123))---\n";
    huffman("made by piyush tiwari(5i123)", true);
    
    cout << "\n--- Execution Time ---\n";
    string best(5000, 'a'); best.append(5000, 'b'); 
    string avg; for(int i=0; i<500; i++) avg += "made by piyush tiwari(5i123)"; 
    string worst; for(int i=0; i<10000; i++) worst += (char)(i % 256);  
    
    auto run = [](string name, string text) {
        auto t1 = high_resolution_clock::now();
        huffman(text, false);
        auto t2 = high_resolution_clock::now();
        cout << name << ": " << duration_cast<microseconds>(t2 - t1).count() << " us\n";
    };

    run("Best Case", best);
    run("Avg Case", avg);
    run("Worst Case", worst);

    return 0;
}