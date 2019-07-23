#include <algorithm>
#include <iostream>
#include <vector>
#include <bitset>
#include <set>
#include <queue>
#include <cstring>

using namespace std;

struct Edge {
    int a, b;
    long long cap, flow;
    Edge(int a, int b, int cap) : a(a), b(b), cap(cap), flow(0) {}
    int other(int v) {
        return v == a ? b : a;
    }
    int capTo(int v) {
        return v == b ? cap - flow : flow;
    }
    void addFlowTo(int v, int f) {
        flow += (v == b ? f : -f);
    }
};

vector<Edge> edges;
int n, m, u[1010], p[1010], pos[1010];
vector<int> g[1010];

bool bfs(int v, int vTarget) {
    queue<int> q;
    u[v] = 1;
    q.push(v);
    while (!q.empty()) {
        v = q.front();
        q.pop();
        if (v == vTarget)
            return 1;
        for (int i = 0; i < g[v].size(); i++) {
            int e = g[v][i], to = edges[e].other(v);
            if (!u[to] && edges[e].capTo(to)) {
                p[to] = e;
                u[to] = u[v] + 1;
                q.push(to);
            }
        }
    }
    return 0;
}

bool dfs(int v, int vTarget) {
    if (v == vTarget)
        return 1;
    for (; pos[v] < g[v].size(); pos[v]++) {
        int e = g[v][pos[v]], to = edges[e].other(v);
        if (u[v] + 1 == u[to] && edges[e].capTo(to)) {
            p[to] = e;
            if (dfs(to, vTarget))
                return 1;
        }
    }
    return 0;
}

int main() {
    cin >> n >> m;
    //scanf("%d%d", &n, &m);
    int a, b, cap;
    for (int i = 0; i < m; i++) {
        cin >> a >> b >> cap;
        //scanf("%d%d%d", &a, &b, &cap);
        edges.push_back(Edge(a - 1, b - 1, cap));
        g[a - 1].push_back(edges.size() - 1);
        g[b - 1].push_back(edges.size() - 1);
    }

    int flow = 0;
    while (1) {
        fill(u, u + n, 0);
        if (!bfs(0, n - 1))
            break;
        fill(pos, pos + n, 0);
        while (dfs(0, n - 1)) {
            int deltaFlow = 1 << 30;
            for (int v = n - 1; v != 0; v = edges[p[v]].other(v))
                deltaFlow = min(deltaFlow, edges[p[v]].capTo(v));
            flow += deltaFlow;
            for (int v = n - 1; v != 0; v = edges[p[v]].other(v))
                edges[p[v]].addFlowTo(v, deltaFlow);
        }
    }

    cout << flow << '\n';
    for (int i = 0; i < edges.size(); i++) {
        cout << edges[i].flow << '\n';
    }
}