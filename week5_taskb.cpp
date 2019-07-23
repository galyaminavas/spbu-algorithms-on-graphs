#include <iostream>
#include <vector>
#include <algorithm>
#include <bitset>
#include <set>
#include <queue>
#include <cstring>

using namespace std;

#define MAX 501
#define MAXM 10001
#define INF 1000000000
long long c[MAX][MAX];
long long c_e[MAXM];
long long f[MAX][MAX];
int ptr[MAX], d[MAX];
int n;
int q[MAX];

long long bfs(int s) {
    //cout << "bfs\n";
    int qh = 0;
    int qt = 0;
    q[qt++] = s;
    memset(d, -1, sizeof(d));
    d[s] = 0;
    while (qh < qt) {
        int v = q[qh++];
        for (int to = 1; to <= n; to++)
            if ((d[to] == -1) && (f[v][to] < c[v][to]))
            {
                q[qt++] = to;
                d[to] = d[v] + 1;
            }
    }
    return d[n] != -1;
}

long long dfs(int v, long long flow) {
    //cout << "dfs\n";
    if (!flow)
        return 0;
    if (v == n)
        return flow;
    for (int &to = ptr[v]; to <= n; to++) {
        if (d[to] != d[v] + 1)
            continue;
        long long pushed = dfs(to, min(flow, c[v][to] - f[v][to]));
        if (pushed) {
            f[v][to] += pushed;
            f[to][v] -= pushed;
            return pushed;
        }
    }
    return 0;
}

long long dinic(int s){
    //cout << "dinic\n";
    long long flow = 0;
    for (;;) {
        if (!bfs(s))
            break;
        memset(ptr, 0, n * sizeof ptr[0]);
        for (int i = 1; i <= n; i++)
            ptr[i] = 1;
        while (long long pushed = dfs(s, INF))
            flow += pushed;
    }
    return flow;
}

int main() {
    std::ios_base::sync_with_stdio(0);
    std::cin.tie(0);
    int m;
    cin >> n >> m;
    memset(c, 0, sizeof(c));

    int from, to;
    long long cap;
    vector<pair<int, int>> edges;
    for (int i = 0; i < m; i++) {
        cin >> from >> to >> cap;
        c_e[i] = cap;
        c[from][to] += cap;
        c[to][from] += cap;
        edges.push_back(make_pair(from, to));
    }

    long long max_flow = dinic(1);
    cout << max_flow << '\n';
//    for (int i = 1; i <= n; i++) {
//        for (int j = 1; j <= n; j++) {
//            cout << f[i][j] << ' ';
//        }
//        cout << '\n';
//    }
    for(int i = 0; i < edges.size(); i++) {
        int a = edges[i].first;
        int b = edges[i].second;

        if (c_e[i] < abs(f[a][b]) && f[a][b] > 0) {
            cout << c_e[i] << '\n';
            f[a][b] -= c_e[i];
            f[b][a] += c_e[i];
        } else if (c_e[i] < abs(f[a][b])) {
            cout << -c_e[i] << '\n';
            f[a][b] += c_e[i];
            f[b][a] -= c_e[i];
        }
//        } else if (f[a][b] > 0) {
//            cout << f[a][b] << '\n';
//            f[a][b] = 0;
//            f[b][a] = 0;
//        }
        else {
            cout << f[a][b] << '\n';
            f[a][b] = 0;
            f[b][a] = 0;
        }
//        cout << f[a][b] << '\n';
//        f[a][b] = 0;
//        f[b][a] = 0;
    }

    return 0;
}
