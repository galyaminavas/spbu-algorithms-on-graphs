#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<vector<int>> graph;
vector<int> color;
vector<int> answer;
int cycle = 0;


void dfs(int cur_vertex) {
    color[cur_vertex] = 1;
    for (int i = 0; i < graph[cur_vertex].size(); i++) {
        int to = graph[cur_vertex][i];
        if (color[to] == 0) {
            dfs(to);
        }
        else if (color[to] == 1) {
            cycle = 1;
        }
    }
    color[cur_vertex] = 2;
    answer.push_back(cur_vertex + 1);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n, m;
    cin >> n >> m;
    color.resize(n, 0);
    graph.resize(n, vector<int>());

    int from, to;
    for (int i = 0; i < m; i++) {
        cin >> from >> to;
        graph.at(from - 1).push_back(to - 1);
    }

    for (int i = 0; i < n; i++) {
        if (color[i] == 0) {
            dfs(i);
            if (cycle == 1) {
                cout << "-1\n";
                return 0;
            }
        }
    }
    reverse(answer.begin(), answer.end());
    for (int i = 0; i < answer.size(); i++) {
        cout << answer[i] << " ";
    }
    cout << "\n";

    return 0;
}
