#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<vector<int>> graph;
vector<int> color;
int cycle_start = -1;
int cycle_end = -1;
vector<int> cycle_answer;
vector<int> prev_v;


bool dfs(int cur_vertex) {
    color[cur_vertex] = 1;
    for (int i = 0; i < graph[cur_vertex].size(); i++) {
        int to = graph[cur_vertex][i];
        if (color[to] == 0) {
            prev_v[to] = cur_vertex;
            if (dfs(to))
                return true; // есть цикл
        }
        else if (color[to] == 1) {
            cycle_start = to;
            cycle_end = cur_vertex;
            return true; // есть цикл
        }
    }
    color[cur_vertex] = 2;
    return false;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n, m;
    cin >> n >> m;
    prev_v.assign(n, -1);
    color.assign(n, 0);
    graph.assign(n, vector<int>());

    int from, to;
    for (int i = 0; i < m; i++) {
        cin >> from >> to;
        graph.at(from - 1).push_back(to - 1);
    }

    for (int i = 0; i < n; i++) {
        if (dfs(i))
            break;
    }
    if (cycle_start == -1) {
        cout << "NO\n";
    }
    else {
        cout << "YES\n";
        for (int vertex = cycle_end; vertex != cycle_start; vertex = prev_v[vertex]) {
            cycle_answer.push_back(vertex);
        }
        cycle_answer.push_back(cycle_start);
        reverse(cycle_answer.begin(), cycle_answer.end());
        for (int i = 0; i < cycle_answer.size(); i++) {
            cout << cycle_answer[i] + 1 << " ";
        }
        cout << "\n";
    }

    return 0;
}