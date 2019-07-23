#include <iostream>
#include <vector>
#include <algorithm>
#include <bitset>
#include <set>
#include <list>

using namespace std;

vector<vector<int>> graph;
vector<vector<int>> dist;
const int INF = 10000000;
vector<pair<int, int>> dist_queue;
bool used[100000];

void bfs(list<int> *queue, bool *visited) {
    int current = queue->front();
    queue->pop_front();
    for (auto i = 0; i < graph[current].size(); i++) {
        if (!visited[i]) {
            visited[i] = true;
            queue->push_back(i);
        }
    }
}

int is_intersecting(bool *from_visited, bool *to_visited, int n) {
    for (int i = 0; i < n; i++) {
        if (from_visited[i] && to_visited[i])
            return i;
    }
    return -1;
}

void bidir_bfs(int from, int to, int n) {
    bool from_visited[100000];
    bool to_visited[100000];

    list<int> from_queue, to_queue;

    int intersect_node = -1;

    for (int i = 0; i < n; i++) {
        from_visited[i] = false;
        to_visited[i] = false;
    }

    from_queue.push_back(from);
    from_visited[from] = true;

    to_queue.push_back(to);
    to_visited[to] = true;

    while (!from_queue.empty() && !to_queue.empty()) {
        //two bfs
        bfs(&from_queue, from_visited);
        bfs(&to_queue, to_visited);

        intersect_node = is_intersecting(from_visited, to_visited, n);
        if (intersect_node != -1) {

        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n, m;
    cin >> n >> m;

    graph.assign(n, vector<int>());

    int from, to;
    for (int i = 0; i < m; i++) {
        cin >> from >> to;
        graph[from - 1].push_back(to - 1);
        graph[to - 1].push_back(from - 1);
    }
    dist.assign(n, vector<int>(n, INF));

    int q;
    cin >> q;
    for (int i = 0; i < q; i++) {
        cin >> from >> to;
        dist_queue.push_back(make_pair(from - 1, to - 1));
    }

//    for (int i = 0; i < q; i++) {
//        if (used[dist_queue[i].first]) {
//            if (dist[dist_queue[i].first][dist_queue[i].second] < INF) {
//                cout << dist[dist_queue[i].first][dist_queue[i].second] << "\n";
//            }
//            else {
//                cout << "-1\n";
//            }
//        }
//        else if (used[dist_queue[i].second]) {
//            if (dist[dist_queue[i].second][dist_queue[i].first] < INF) {
//                cout << dist[dist_queue[i].second][dist_queue[i].first] << "\n";
//            }
//            else {
//                cout << "-1\n";
//            }
//
//        }
//        else {
//            dijkstra(dist_queue[i].first, n);
//            if (dist[dist_queue[i].first][dist_queue[i].second] < INF) {
//                cout << dist[dist_queue[i].first][dist_queue[i].second] << "\n";
//            }
//            else {
//                cout << "\n";
//            }
//        }
//    }


    return 0;
}
