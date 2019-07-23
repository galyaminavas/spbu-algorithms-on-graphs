#include <iostream>
#include <vector>
#include <algorithm>
#include <bitset>
#include <set>
#include <queue>

using namespace std;

vector<vector<int>> graph;
vector<int> mt;
vector<char> used;
int cnt;


bool try_kuhn(int v) {
    if (used[v])
        return false;
    used[v] = true;
    for (int i = 0; i < graph[v].size(); i++) {
        int to = graph[v][i];
        if (mt[to] == -1 || try_kuhn(mt[to])) {
            mt[to] = v;
            return true;
        }
    }
    return false;
}

int main() {
    int n, m;
    cin >> n >> m;

    graph.assign(n, vector<int>());

    int to;
    for (int i = 0; i < n; i++) {
        cin >> to;
        while (to != 0) {
            graph[i].push_back(to - 1);
            cin >> to;
        }
    }

    mt.assign(m, -1);
    cnt = 0;
    for (int v = 0; v < n; v++) {
        used.assign(n, false);
        try_kuhn(v);
    }

    for (int i = 0; i < m; i++) {
        if (mt[i] != -1) {
            cnt++;
        }
    }

    cout << cnt << "\n";
    for (int i = 0; i < m; i++) {
        if (mt[i] != -1) {
            cout << mt[i] + 1 << " " << i + 1 << "\n";
        }
    }

    return 0;
}

