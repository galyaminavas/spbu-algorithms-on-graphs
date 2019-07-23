#include <iostream>
#include <algorithm>
#include <bitset>
#include <cmath>
#include <map>
#include <queue>
#include <set>

using namespace std;

vector<int> g[100001], ans[100001];
int n, m, a, b, t, tin[100001], fup[100001], u[100001], c[100001], max_color;

void paint(int v, int color){
    c[v] = color;
    for (int i = 0; i < g[v].size(); i++){
        int to = g[v][i];
        if (c[to] == 0){
            if (fup[to] > tin[v] && to != g[v][i+1] && to != g[v][i-1]){
                max_color++;
                paint(to, max_color);
            } else {
                paint(to, color);
            }
        }
    }
}

void dfs(int v, int p){
    u[v] = 1;
    t++;
    tin[v] = t;
    fup[v] = t;
    for (int i = 0; i < g[v].size(); i++){
        int to = g[v][i];
        if (to == p) continue;
        if (u[to] == 0){
            dfs(to, v);
            fup[v] = min(fup[v], fup[to]);
        } else {
            fup[v] = min(fup[v], tin[to]);
        }
    }
}


int main() {
    std::ios_base::sync_with_stdio(0);
    std::cin.tie(0);

    cin >> n >> m;

    for (int i = 0; i < m; i ++){
        cin >> a >> b;
        if (a == b)
            continue;
        a--;
        b--;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    for (int i = 0; i < n; i++){
        sort(g[i].begin(), g[i].end());
    }
    for (int j = 0; j < n; j++){
        if (u[j] == 0)
            dfs(j, -1);
    }
    for (int j = 0; j < n; j++){
        if (c[j] == 0) {
            max_color++;
            paint(j, max_color);
        }
    }
    for (int i = 0; i < n; i++){
        ans[c[i] - 1].push_back(i);
    }
    cout << max_color << "\n";
    for (int i = 0; i < max_color; i++){
        sort(ans[i].begin(), ans[i].end());
    }
    sort(ans + 0, ans + max_color);
    for (int i = 0; i < max_color; i++){
        for (int j = 0; j < ans[i].size(); j++){
            cout << ans[i][j] + 1 << " ";
        }
        cout << "\n";
    }
    return 0;
}