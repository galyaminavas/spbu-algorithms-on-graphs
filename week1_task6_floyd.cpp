#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int graph[1000][1000];
const int INF = 100000;


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n, m;
    cin >> n >> m;

    int from, to;
    for (int i = 0; i < m; i++) {
        cin >> from >> to;
        graph[from - 1][to - 1] = 1;
        graph[to - 1][from - 1] = 1;
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (graph[i][j] != 1)
                graph[i][j] = INF;
        }
        graph[i][i] = 0;
    }
    for (int k = 0; k < n; k++) {
        for (int j = 0; j < n; j++) {
            for (int i = 0; i < j; i++) {
                if ((graph[i][k] < INF) && (graph[k][j] < INF)) {
                    if (graph[i][j] > graph[i][k] + graph[k][j])
                        graph[i][j] = graph[j][i] = graph[i][k] + graph[k][j];
                }
            }
        }
    }

    int sum = 0;

    for (int i = 0; i < n; i ++) {
        for (int j = 0; j < n; j++) {
            if (i < j)
                sum += graph[i][j];
        }
    }
    cout << sum << "\n";

    return 0;
}
