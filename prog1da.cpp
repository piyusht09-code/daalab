#include <iostream>

using namespace std;

void bSort(int a[], int n) {
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - i - 1; j++)
            if (a[j] > a[j + 1]) swap(a[j], a[j + 1]);
}

void sSort(int a[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int m = i;
        for (int j = i + 1; j < n; j++) 
            if (a[j] < a[m]) m = j;
        swap(a[i], a[m]);
    }
}

void hfy(int a[], int n, int i) {
    int m = i, l = 2 * i + 1, r = 2 * i + 2;
    if (l < n && a[l] > a[m]) m = l;
    if (r < n && a[r] > a[m]) m = r;
    if (m != i) { swap(a[i], a[m]); hfy(a, n, m); }
}

void hSort(int a[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--) hfy(a, n, i);
    for (int i = n - 1; i > 0; i--) { swap(a[0], a[i]); hfy(a, i, 0); }
}

void qSort(int a[], int l, int h) {
    if (l >= h) return;
    int p = a[h], i = l;
    for (int j = l; j < h; j++) 
        if (a[j] < p) swap(a[i++], a[j]);
    swap(a[i], a[h]);
    qSort(a, l, i - 1); 
    qSort(a, i + 1, h);
}

int t[100];
void mSort(int a[], int l, int r) {
    if (l >= r) return;
    int m = (l + r) / 2, i = l, j = m + 1, k = l;
    mSort(a, l, m); 
    mSort(a, m + 1, r);
    while (i <= m && j <= r) t[k++] = (a[i] < a[j]) ? a[i++] : a[j++];
    while (i <= m) t[k++] = a[i++];
    while (j <= r) t[k++] = a[j++];
    for (i = l; i <= r; i++) a[i] = t[i];
}

#define TEST(name, func) \
    for (int i = 0; i < n; i++) a[i] = o[i]; \
    func; \
    cout << name; \
    for (int i = 0; i < n; i++) cout << a[i] << " "; \
    cout << "\n";

int main() {
    int o[] = {64, 25, 12, 22, 11, 90, 8, 45};
    int n = 8, a[8];
    cout<<"Made By: Piyush Tiwari(5IT123)\n";
    TEST("Bubble Sort: ", bSort(a, n))
    TEST("Select Sort: ", sSort(a, n))
    TEST("Heap Sort:   ", hSort(a, n))
    TEST("Quick Sort:  ", qSort(a, 0, n - 1))
    TEST("Merge Sort:  ", mSort(a, 0, n - 1))
    
    return 0;
}
