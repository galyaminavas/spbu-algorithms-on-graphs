#include <iostream>
#include <vector>

using namespace std;

const int INF = 150000;
int operations[3][INF]; //[0]: 0 - cut, 1 - ask
int dsu[INF];
int answer[INF];

int from_set(int n) {
    if (dsu[n] == n) {
        return n;
    }
    else {
        dsu[n] = from_set(dsu[n]);
        return dsu[n];
    }
}

int unite(int x, int y) {
    int x_p = from_set(x);
    int y_p = from_set(y);
    dsu[x_p] = y_p;
    return (x_p == y_p);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n, m, k;
    cin >> n >> m >> k;

    int u, v;
    for (int i = 0; i < m; i++) {
        cin >> u >> v;
    }

    char op[5];
    for (int i = 0; i < k; i++) {
        cin >> op >> operations[1][i] >> operations[2][i];
        if (op[0] == 'c') {
            operations[0][i] = 0;
        }
        else if (op[0] == 'a') {
            operations[0][i] = 1;
        }
    }

    for (int i = 0; i < n; i++) {
        dsu[i] = i;
    }

    for (int i = k - 1; i >= 0; i--) {
        if (operations[0][i] == 1) {
            answer[i] = (from_set(operations[1][i]) == from_set(operations[2][i]));

        }
        else {
            unite(operations[1][i], operations[2][i]);
        }
    }

    for (int i = 0; i < k; i++) {
        if (operations[0][i] == 1) {
            if (answer[i]) {
                cout << "YES\n";
            }
            else {
                cout << "NO\n";
            }
        }
    }

    return 0;
}
