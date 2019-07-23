#include <iostream>
#include <vector>
#include <algorithm>
#include <bitset>
#include <set>
#include <queue>

using namespace std;

//vector<vector<int>> graph;
//vector<int> graph[13];
const unsigned int INF = 1000;
vector<int> graph;
//int d[1 << 20][20];
//int parents[1 << 20][20];

//vector<int> graph[13];

int ChromaticNumber(int n) {
    int all = 1 << n;
    vector<int> ind(all);
    vector<int> f(all, INF);
    f[0] = 0;
    ind[0] = 1;
    for (int i = 1; i < all; i ++) {
        int ctz = __builtin_ctz(i);
        ind[i] = ind[i ^ (1 << ctz)] && ((graph[ctz] & i) == 0);
    }
    for (int B = 0; B < all; B++) {
        for (int C = B; C > 0; C--, C &= B) {
            if (ind[C]) {
                f[B] = min(f[B], f[B - C] + 1);
            }
        }
    }
    return f[all - 1];
}

int main() {
    int n, m;
    cin >> n >> m;

    if (m == 0) {
        cout << 1 << "\n";
        return 0;
    }

    graph.assign(n, 0);

    int v1, v2;
    for (int i = 0; i < m; i++) {
        cin >> v1 >> v2;
        graph[v1 - 1] += (1 << (v2 - 1));
        graph[v2 - 1] += (1 << (v1 - 1));
    }

    int k = ChromaticNumber(n);
    cout << k << "\n";

    return 0;
}
