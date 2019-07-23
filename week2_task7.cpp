#include <iostream>
#include <vector>
#include <algorithm>
#include <bitset>
#include <set>
#include <queue>

using namespace std;

//vector<bitset<2000>> g;
vector<vector<unsigned int>> dist;

const int INF = 200000;
//int graph[100000][100000];
vector<vector<pair<int, int>>> graph;
vector<pair<int, int>> dist_queue;
//int answer[10000];
//bool used[100000];
//int dist[100000][100000];
//vector<vector<int>> dist;

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
    //dist_queue.resize(n);
    graph.assign(n, vector<pair<int,int>>());

    int from, to;
    for (int i = 0; i < m; i++) {
        cin >> from >> to;
        graph[from - 1].push_back(make_pair(to - 1, 1));
        graph[to - 1].push_back(make_pair(from - 1, 1));
    }

    dist.assign(n, vector<unsigned int>(n, INF));

//    for (int i = 0; i < n; i++) {
//        for (int j = 0; j < n; j++) {
//            cout << graph[i][j] << " ";
//        }
//        cout << "\n";
//    }

//    for (int i = 0; i < n; i++) {
//        for (int j = i + 1; j < n; j++) {
//            if (!graph[i][j]) {
//                dist[i][j] = dist[j][i] = INF;
//            }
//        }
//    }

    int q;
    cin >> q;
    for (int i = 0; i < q; i++) {
        cin >> from >> to;
        dist_queue[i] = make_pair(from - 1, to - 1);
    }

    for (int i = 0; i < n; i++) {
        dijkstra(i, n);
    }

    for (int i = 0; i < q; i++) {
        if (dist[dist_queue[i].first][dist_queue[i].second] < INF) {
            cout << dist[dist_queue[i].first][dist_queue[i].second] << "\n";
        }
        else {
            cout << "-1\n";
        }
    }

//    for (int i = 0; i < q; i++) {
//        if (!used[dist_queue[i].first] && !used[dist_queue[i].second]) {
//            dijkstra(dist_queue[i].first, n);
//            used[dist_queue[i].first] = true;
//        }
//        else {
//            if (used[dist_queue[i].first]) {
//                if (graph[dist_queue[i].first][dist_queue[i].second] < INF) {
//                    cout << graph[dist_queue[i].first][dist_queue[i].second] << "\n";
//                }
//                else {
//                    cout << "-1\n";
//                }
//            }
//            else {
//                if (graph[dist_queue[i].second][dist_queue[i].first] < INF) {
//                    cout << graph[dist_queue[i].second][dist_queue[i].second] << "\n";
//                }
//                else {
//                    cout << "-1\n";
//                }
//            }
//        }
//    }

    return 0;
}
