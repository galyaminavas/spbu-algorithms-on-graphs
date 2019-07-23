#include <iostream>
#include <vector>
#include <algorithm>
#include <bitset>
#include <set>

using namespace std;

vector<vector<pair<int, int>>> graph;
vector<int> dist;
const int INF = 100000000;

void dijkstra(int start_vertex) {
    dist[start_vertex] = 0;
    set<pair<int, int>> q;
    q.insert({dist[start_vertex], start_vertex});
    while (!q.empty()) {
        auto cur_vertex = *q.begin();
        q.erase(q.begin());
        for (auto &to : graph[cur_vertex.second]) {
            if (dist[to.first] > cur_vertex.first + to.second) {
                q.erase({dist[to.first], to.first});
                dist[to.first] = cur_vertex.first + to.second;
                q.insert({dist[to.first], to.first});
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n, m;
    cin >> n >> m;

    int s, t;
    cin >> s >> t;

    graph.assign(n, vector<pair<int, int>>());

    int from, to, weight;
    for (int i = 0; i < m; i++) {
        cin >> from >> to >> weight;
        graph[from - 1].push_back(pair<int, int>(to - 1, weight));
        graph[to - 1].push_back(pair<int, int>(from - 1, weight));
    }

    dist.assign(n, INF);

    dijkstra(s - 1);

    if (dist[t - 1] < INF) {
        cout << dist[t - 1] << "\n";
    } else {
        cout << "-1\n";
    }

    return 0;
}
