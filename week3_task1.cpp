#include <iostream>
#include <vector>
#include <algorithm>
#include <bitset>
#include <set>
#include <queue>

using namespace std;

vector<vector<int>> graph;

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

    vector<char> part(n, -1);
    bool flag = true;
    queue<int> q;
    for (int i = 0; i < n; i++) {
        if (part[i] == -1) {
            //int h = 0;
            //int t = 0;
            //q[t++] = i;
            part[i] = 0;
            q.push(i);
            while (!q.empty()) {
                int v = q.front();
                q.pop();
                for (int j = 0; j < graph[v].size(); j++) {
                    int to = graph[v][j];
                    if (part[to] == -1) {
                        part[to] = !part[v];
                        q.push(to);
                    }
                    else {
                        flag &= part[to] !=part[v];
                    }
                }
            }
        }
    }

    if (flag) {
        cout << "YES\n";
        for (int i = 0; i < n; i++) {
            cout << part[i] + 1 << " ";
        }
        cout << "\n";
    }
    else {
        cout << "NO\n";
    }

    return 0;
}
