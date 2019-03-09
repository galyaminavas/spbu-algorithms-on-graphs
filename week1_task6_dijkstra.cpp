#include <iostream>
#include <vector>
#include <algorithm>
#include <bitset>
#include <set>

using namespace std;

vector<pair<int, int>> graph[1000];
vector<vector<int>> dist;
const int INF = 10000000;

void dijkstra(int start_vertex, int n) {
    dist[start_vertex][start_vertex] = 0;
    set<pair<int, int>> q;
    q.insert({dist[start_vertex][start_vertex], start_vertex});
    while (!q.empty()) {
        auto cur_vertex = *q.begin();
        q.erase(q.begin());
        for (auto &to : graph[cur_vertex.second]) {
            if (dist[start_vertex][to.first] > cur_vertex.first + to.second) {
                q.erase({dist[start_vertex][to.first], to.first});
                dist[start_vertex][to.first] = cur_vertex.first + to.second;
                q.insert({dist[start_vertex][to.first], to.first});
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n, m;
    cin >> n >> m;

    int from, to;
    for (int i = 0; i < m; i++) {
        cin >> from >> to;
        graph[from - 1].push_back(pair<int, int>(to - 1, 1));
        graph[to - 1].push_back(pair<int, int>(from - 1, 1));
    }
    dist.assign(n, vector<int>(n, INF));

    for (int i = 0; i < n; i++) {
        dijkstra(i, n);
    }

    int sum = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i < j) {
                sum += dist[i][j];
            }
        }
    }

    cout << sum << "\n";

    return 0;
}
