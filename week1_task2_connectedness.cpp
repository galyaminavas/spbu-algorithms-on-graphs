#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

const int MAXN = 100;
bool used[MAXN];
vector<int> g[MAXN];

void dfs(int v) {
    used[v] = true;
    for (auto to : g[v]) {
        if (!used[to]) {
            dfs(to);
        }
    }
}

int main() {

    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int from, to;
        cin >> from >> to;
        g[from - 1].push_back(to - 1);
        g[to - 1]. push_back(from - 1);
    }

    dfs(0);

    for (int i = 0; i < n; i++) {
        if (!used[i]) {
            cout << "NO" << endl;
            return 0;
        }
        else continue;
    }
    cout << "YES" << endl;

    return 0;
}