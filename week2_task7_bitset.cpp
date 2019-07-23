#include <iostream>
#include <vector>
#include <algorithm>
#include <bitset>
#include <set>
#include <queue>

using namespace std;

vector<bitset<100000>> graph;
vector<vector<unsigned int>> dist;
vector<pair<int, int>> queries;
const int INF = 300001;

void bfs_bitset(int start_v) {
    bitset<100000> unvisited;

    unvisited.set();
    unvisited[start_v].flip();

    bitset<100000> current = graph[start_v];

    unsigned int len = 1;
    bitset<100000> next;

    while (current.any()) {
        next.reset();
        for (int i = current._Find_first(); i < current.size(); i = current._Find_next(i)) {
            next |= graph[i];
            unvisited[i] = 0;
            dist[start_v][i] = len;
        }
        next &= unvisited;
        len++;
        current = next;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n, m, q;
    cin >> n >> m;
    graph.assign(n, bitset<100000>(0));
    dist.assign(n, vector<unsigned int>(n, INF));

    int from, to;
    for (int i = 0; i < m; i++) {
        cin >> from >> to;
        graph[from - 1].set(to - 1);
        graph[to - 1].set(from - 1);
    }

    cin >> q;
    //queries.assign(n, pair<int, int>());

    for (int i = 0; i < q; i++) {
        cin >> from >> to;
        queries.push_back(make_pair(from - 1, to - 1));
    }


    for (int i = 0; i < n; i++) {
        bfs_bitset(i);
    }

    int d;
    for (int i = 0; i < q; i++) {
        d = dist[queries[i].first][queries[i].second];
        if (d < INF) {
            cout << d << "\n";
        }
        else {
            cout << "-1\n";
        }
    }

    return 0;
}
