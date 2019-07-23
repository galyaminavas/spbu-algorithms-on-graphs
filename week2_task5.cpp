#include <iostream>
#include <vector>

using namespace std;

vector<long long> dist;
vector<bool> used;
const long long INF = 6000000000000000000;
vector<vector<pair<int, long long>>> graph; //to, dist

void dfs(int v) {
    used[v] = true;
    for (auto to : graph[v]) {
        if (!used[to.first]) {
            dfs(to.first);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n, m, s;
    cin >> n >> m >> s;
    s--;

    dist.assign(n, INF);
    used.assign(n, false);
    graph.assign(n, vector<pair<int, long long>>());

    int u, v;
    long long weight;
    for (int i = 0; i < m; i++) {
        cin >> u >> v >> weight;
        graph[u - 1].push_back(make_pair(v - 1, weight));
    }

//    for (int i = 0; i < n; i++) {
//        cout << i << ": ";
//        for (auto to : graph[i]) {
//            cout << to.first << " ";
//        }
//        cout << "\n";
//    }


    dist[s] = 0;
    bool relaxed = true;
    for (int i = 0; i < n; i++) {
        if (!relaxed) {
            break;
        }
        relaxed = false;
        for (int j = 0; j < n; j++) {
            for (auto to: graph[j]) {
                if (dist[j] < INF && (dist[to.first] > dist[j] + to.second)) {
                    dist[to.first] = max(-INF, dist[j] + to.second);
                    relaxed = true;
                }
            }
        }
    }


    for (int i = 0; i < n; i++) {
        for (auto to: graph[i]) {
            if (dist[i] < INF && (dist[to.first] > dist[i] + to.second)) {
                used[to.first] = true;
                dfs(to.first);
            }
        }
    }

//    for (int i = 0; i < n; i++) {
//        cout << used[i] << " ";
//    }
//    cout << "\n";

    for (int i = 0; i < n; i++) {
        if (dist[i] == INF) {
            cout << "*\n";
        }
        else if (used[i]) {
            cout << "-\n";
        }
        else {
            cout << dist[i] << "\n";
        }
    }

    return 0;
}
