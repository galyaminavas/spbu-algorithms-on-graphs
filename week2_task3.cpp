#include <iostream>
#include <vector>
#include <algorithm>
#include <bitset>
#include <set>

using namespace std;

vector<vector<pair<int, int>>> graph;
vector<int> dist;
//vector<bool> used;
const int INF = 1000000;
vector<bool> possess;
vector<int> parent;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n, m;
    cin >> n >> m;

    graph.assign(n, vector<pair<int, int>>());

    int p;
    for (int i = 0; i < n; i++) {
        cin >> p;
        possess.push_back(p - 1);
    }

    int from, to;
    for (int i = 0; i < m; i++) {
        cin >> from >> to;
        graph[from - 1].push_back(make_pair(to - 1, possess[from - 1] != possess[to - 1]));
        graph[to - 1].push_back(make_pair(from - 1, possess[from - 1] != possess[to - 1]));
    }

    dist.assign(n, INF);
    dist[0] = 0;
    parent.resize(n);
    //used.assign(n, false);

    set<pair<int, int>> q;
    q.insert({dist[0], 0});
    while (!q.empty()) {
        auto cur_vertex = *q.begin();
        q.erase(q.begin());
        for (auto &to : graph[cur_vertex.second]) {
            if (dist[to.first] > cur_vertex.first + to.second) {
                q.erase({dist[to.first], to.first});
                dist[to.first] = cur_vertex.first + to.second;
                q.insert({dist[to.first], to.first});
                parent[to.first] = cur_vertex.second;
            }
        }
    }



    if (dist[n - 1] < INF) {
        int cost = 0;
        //int t_count = 0;
        vector<int> path;
        int curr_v = n - 1;
        while (curr_v != 0) {
            cost += possess[curr_v] != possess[parent[curr_v]];
            path.push_back(curr_v);
            curr_v = parent[curr_v];
        }
        path.push_back(0);
        reverse(path.begin(), path.end());
        cout << cost << " " << path.size() << "\n";
        for (int i = 0; i < path.size(); i++) {
            cout << path[i] + 1 << " ";
        }
        cout << "\n";
    }
    else {
        cout << "impossible\n";
    }

    return 0;
}
