#include <iostream>
#include <vector>
#include <algorithm>
#include <bitset>
#include <set>
#include <queue>

using namespace std;

//vector<vector<int>> graph;
int graph[20][20];
const unsigned int INF = 2000000000;
int d[1 << 20][20];
int parents[1 << 20][20];

int main() {
    int n;
    cin >> n;
    //graph.assign(n, vector<int>());

    unsigned int cost;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> cost;
            graph[i][j] = cost;
            //graph[i].push_back(cost);
        }
    }
    //добавили вершину, из которой будем начинать
    for (int i = 0; i < n; i++) {
        graph[i][n] = 0;
        graph[n][i] = 0;
    }
    graph[n][n] = INF;

    //int source = 0;

    //vector<vector<pair<int, vector<int>>>> d((1 << n), vector<pair<int, vector<int>>>(n, make_pair(INT_MAX, vector<int>())));
    //pair<unsigned int, vector<int>> d[1 << n + 1][n+1];
    for (int i = 0; i < (1 << n+1); i++) {
        for (int j = 0; j < n+1; j++) {
            d[i][j] = INF;
        }
    }

    d[0][n] = 0;
    parents[0][n] = -1;
    for (int mask = 0; mask < (1 << n+1); mask++) {
        for (int i = 0; i < n+1; i++) {
            if (d[mask][i] == INF)
                continue;
            for (int j = 0; j < n+1; j++) {
                if (!(mask & (1 << j))) {
                    if (d[mask ^ (1 << j)][j] > d[mask][i] + graph[i][j]) {
                        d[mask ^ (1 << j)][j] = d[mask][i] + graph[i][j];
                        parents[mask ^ (1 << j)][j] = i;
                        //d[mask ^ (1 << j)][j].second = d[mask][i].second;
                        //d[mask ^ (1 << j)][j].second.push_back(j);
                    }
                    //d[mask ^ (1 << j)][j] = min(d[mask ^ (1 << j)][j], d[mask][i] + graph[i][j]);
                }
            }
        }
    }


    cout << d[(1 << n+1) - 1][n] << "\n";
    vector<int> path;
    int mask = (1 << n+1) - 1;
    int p = n;
    for (int i = 0; i < n; i++) {
        int c = p;
        p = parents[mask][c];
        path.push_back(p);
        mask -= (1 << c);
    }
    reverse(path.begin(), path.end());
    for (int i = 0; i < path.size(); i++) {
        cout << path[i] + 1 << " ";
    }
    cout << "\n";
//    for (int i = 0; i < d[(1 << n+1) - 1][n].second.size() - 1; i++) {
//        cout << d[(1 << n+1) - 1][n].second[i] + 1 << " ";
//    }
//    cout << "\n";

    return 0;
}
