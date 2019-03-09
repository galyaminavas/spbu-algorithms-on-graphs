#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <stack>
#include <bitset>

using namespace std;

vector<vector<int>> graph;
vector<int> dist;

int bfs(int start_v, int n) {
    vector<int> used = vector<int>(n, 0);
    dist = vector<int>(n, 0);
    vector<int> parent = vector<int>(n);
    queue<int> q;
    q.push(start_v);
    used[start_v] = 1;
    dist[start_v] = 0;
    parent[start_v] = -1;
    while (!q.empty()) {
        int curr_v = q.front();
        q.pop();
        for (int to : graph[curr_v]) {
            if (used[to] == 0) {
                used[to] = 1;
                dist[to] = dist[curr_v] + 1;
                parent[to] = curr_v;
                q.push(to);
            }
        }
    }
    int far_v = start_v;
    for (int i = 0; i < n; i++) {
        if (dist[far_v] < dist[i]) {
            far_v = i;
        }
    }
    return far_v;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n, m;
    cin >> n >> m;

    graph.assign(n, vector<int>());

    int from, to;
    for (int i = 0; i < n - 1; i++) {
        cin >> from >> to;
        graph[from - 1].push_back(to - 1);
        graph[to - 1].push_back(from - 1);
    }

    int first_v = bfs(0, n);
    int second_v = bfs(first_v, n);
    int dist_f_s = dist[second_v];

    if (dist_f_s == m) {
        cout << dist_f_s + 1 << "\n";
    }
    else if (dist_f_s < m) {
        int cities_count = dist_f_s + (m - dist_f_s) / 2 + 1;
        if (cities_count > n) {
            cities_count = n;
        }
        cout << cities_count << "\n";
    }
    else {
        cout << m + 1 << "\n";
    }

    return 0;
}
