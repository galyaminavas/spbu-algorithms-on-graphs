#include <iostream>
#include <vector>
#include <algorithm>
#include <bitset>
#include <set>

using namespace std;

vector<vector<pair<int, int>>> graph;
vector<int> dist;
vector<bool> used;
const int INF = 1000000;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n, m;
    cin >> n >> m;

    graph.assign(n, vector<pair<int, int>>());

    int from, to, weight;
    for (int i = 0; i < m; i++) {
        cin >> from >> to >> weight;
        graph[from - 1].push_back(make_pair(to - 1, weight));
        graph[to - 1].push_back(make_pair(from - 1, weight));
    }


    dist.assign(n, INF);
    dist[0] = 0;
    used.assign(n, false);
    set<pair<int, int>> q;
    q.insert({0, 0}); // key, vertex

    int answer_w = 0;

    while (!q.empty()) {
        auto cur_vertex = *q.begin();
        q.erase(q.begin());
        answer_w += cur_vertex.first;
        used[cur_vertex.second] = true;
        for (auto &to : graph[cur_vertex.second]) {
            if (!used[to.first] && dist[to.first] > to.second) {
                q.erase({dist[to.first], to.first});
                dist[to.first] = to.second;
                q.insert({dist[to.first], to.first});
            }
        }
    }


    cout << answer_w << "\n";

    return 0;
}
