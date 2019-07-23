#include <iostream>
#include <vector>
#include <algorithm>
#include <bitset>
#include <set>
#include <queue>

using namespace std;

vector<vector<int>> graph;
vector<vector<int>> graph_r;
vector<int> used;
vector<int> top;
vector<int> color;
set<pair<int, int>> s;

void dfs1(int v) {
    used[v] = 1;
    for (int i = 0; i < graph[v].size(); i++) {
        int to = graph[v][i];
        if (!used[to]) {
            dfs1(to);
        }
    }
    top.push_back(v);
}

void dfs2(int v, int c) {
    color[v] = c;
    for (int i = 0; i < graph_r[v].size(); i++) {
        int to = graph_r[v][i];
        if (color[to] == -1) {
            dfs2(to, c);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n, m;
    cin >> n >> m;

    graph.assign(n, vector<int>());
    graph_r.assign(n, vector<int>());

    int from, to;
    for (int i = 0; i < m; i++) {
        cin >> from >> to;
        graph[from - 1].push_back(to - 1);
        graph_r[to - 1].push_back(from - 1);
    }

//    for (int i = 0; i < n; i++) {
//        for (auto j : graph_r[i]) {
//            cout << j << " ";
//        }
//        cout << "\n";
//    }

    used.assign(n, 0);
//    for (int i = 0; i < n; i++) {
//        cout << used[i] << " ";
//    }
//    cout << "\n";
    for (int i = 0; i < n; i++) {
        if (!used[i]) {
            dfs1(i);
        }
    }
//    for (int i = 0; i < n; i++) {
//        cout << used[i] << " ";
//    }
//    cout << "\n";
//
    color.assign(n, -1);
    int c = 0;
    reverse(top.begin(), top.end());

//    for (int i = 0; i < top.size(); i++) {
//        cout << top[i] << " ";
//    }

    for (int i = 0; i < top.size(); i++) {
        int v = top[i];
        if (color[v] == -1) {
            dfs2(v, c);
            c++;
        }
    }

//    for (int i = 0; i < n; i++) {
//        cout << color[i] << " ";
//    }


    for (int i = 0; i < n; i ++) {
        for (int j = 0; j < graph[i].size(); j++) {
            int to = graph[i][j];
            if (color[i] != color[to]) {
                s.insert(make_pair(color[i], color[to]));
            }
        }
    }

    cout << s.size() << "\n";

    return 0;
}
