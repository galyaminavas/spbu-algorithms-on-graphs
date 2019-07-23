#include <iostream>
#include <vector>
#include <algorithm>
#include <bitset>
#include <set>
#include <cmath>

using namespace std;

const int INF = 1000000000;
double eucl_dist[5000][5000];
int coord_x[5001], coord_y[5001];
bool used[5000];


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin >> n;

    vector<int> dist (n, INF);

    for (int i = 0; i < n; i++) {
        cin >> coord_x[i] >> coord_y[i];
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int d_x = coord_x[i] - coord_x[j];
            int d_y = coord_y[i] - coord_y[j];
            eucl_dist[i][j] = d_x * d_x + d_y * d_y;
        }
    }

    double answer_w = 0;
    dist[0] = 0;

    for (int i = 0; i < n; i++) {

        double min = INF;
        int min_index;
        for (int v = 0; v < n; v++) {
            if (!used[v] && dist[v] < min) {
                min = dist[v];
                min_index = v;
            }
        }
        int u = min_index;
        used[u] = true;
        answer_w += sqrt(dist[u]);

        for (int v = 0; v < n; v++) {
            if (!used[v] && eucl_dist[u][v] < dist[v]) {
                dist[v] = eucl_dist[u][v];
            }
        }
    }

    cout.precision(9);
    cout << answer_w << "\n";

    return 0;
}