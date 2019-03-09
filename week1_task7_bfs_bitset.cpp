#include <iostream>
#include <vector>
#include <algorithm>
#include <bitset>
#include <set>
#include <queue>

using namespace std;

vector<bitset<2000>> g;
unsigned int dist[2000][2000];

void bfs_bitset(int start_v) {
    bitset<2000> unvisited;

    unvisited.set();
    unvisited[start_v].flip();

    bitset<2000> current = g[start_v];

    unsigned int len = 1;
    bitset<2000> next;

    while (current.any()) {
        next.reset();
        for (int i = current._Find_first(); i < current.size(); i = current._Find_next(i)) {
            next |= g[i];
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
    int n;
    cin >> n;

    g.assign(n, bitset<2000>(0));
    int flag;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> flag;
            if (flag == 1) {
                g[i].set(j);
            }
        }
    }


    for (int i = 0; i < n; i++) {
        bfs_bitset(i);
    }

    unsigned int sum = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i != j) {
                sum += dist[i][j];
            }
        }
    }

    cout << sum << "\n";

    return 0;
}
