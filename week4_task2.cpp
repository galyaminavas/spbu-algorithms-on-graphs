#include <iostream>
#include <vector>
#include <algorithm>
#include <bitset>
#include <set>
#include <queue>

using namespace std;

int n, l;
vector<vector<int>> graph;
vector<int> tin, tout;
int timer;
vector<vector<int>> up;
//vector<int> mt;
//vector<char> used;
//int cnt;

void dfs(int v, int p = 0) {
    tin[v] = timer++;
    up[v][0] = p;
    for (int i = 1; i <= l; i++) {
        up[v][i] = up[up[v][i-1]][i-1];
    }
    for (size_t i=0; i<graph[v].size(); ++i) {
        int to = graph[v][i];
        if (to != p)
            dfs (to, v);
    }
    tout[v] = timer++;
}

bool upper(int a, int b) {
    return tin[a] <= tin[b] && tout[a] >= tout[b];
}

int lca (int a, int b) {
    if (upper (a, b))  return a;
    if (upper (b, a))  return b;
    for (int i=l; i>=0; --i)
        if (! upper (up[a][i], b))
            a = up[a][i];
    return up[a][0];
}


int main() {
    int n;
    cin >> n;

    graph.assign(n, vector<int>());

    tin.resize(n);
    tout.resize(n);
    up.resize(n);


    int parent;
    for (int i = 2; i <= n; i++) {
        cin >> parent;
        graph[parent - 1].push_back(i - 1);
    }
    int m;
    cin >> m;
    vector<pair<int, int>> query;
    int x, y;
    for (int i = 0; i < m; i++) {
        cin >> x >> y;
        query.push_back(make_pair(x - 1, y - 1));
    }
    l = 1;
    while ((1 << l) <= n)
        l++;

    for (int i = 0; i < n; i++) {
        up[i].resize(l+1);
    }
    dfs(0);

    for (int i = 0; i < m; i++) {
        int res = lca(query[i].first, query[i].second);
        cout << res + 1 << "\n";
    }

    return 0;
}

