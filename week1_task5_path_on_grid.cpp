#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <stack>

using namespace std;

vector<vector<int>> field;
vector<vector<int>> minLength;
vector<vector<int>> used;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int w, h;
    int x1, y1;
    int x2, y2;
    cin >> w >> h >> x1 >> y1 >> x2 >> y2;
    x1--;
    y1--;
    x2--;
    y2--;
    field.assign(h, vector<int>(w));
    minLength.assign(h, vector<int>(w, INT_MAX));
    used.assign(h, vector<int>(w, 0));

    for (int i = 0; i < h; i++) {
        char string1[1000];
        cin >> string1;
        for (int j = 0; j < w; j ++) {
            if (string1[j] == '.') {
                field[i][j] = 1; //проходима
            }
            else if (string1[j] == '*') {
                field[i][j] = 0; //непроходима
            }
        }
    }

    queue<pair<int, int>> q;
    q.push(make_pair(x1, y1));
    minLength[y1][x1] = 0;
    used[y1][x1] = 1;


    // bfs
    while (!q.empty())
    {
        pair<int, int> p = q.front();
        q.pop();
        int currX = p.first;
        int currY = p.second;
        int currMinLen = minLength[currY][currX];
        int dx[4] = {1, 0, -1, 0};
        int dy[4] = {0, 1, 0, -1};
        for (int k = 0; k < 4; k++)
        {
            int ix = currX + dx[k];
            int iy = currY + dy[k];
            if (ix >= 0 && iy >= 0 && ix < w && iy < h && field[iy][ix])
            {
                minLength[iy][ix] = min(minLength[iy][ix], currMinLen + 1);
                if (!used[iy][ix])
                {
                    q.push(make_pair(ix, iy));
                    used[iy][ix] = 1;
                }
            }
        }
    }

    int currLen = minLength[y2][x2];
    if (currLen == INT_MAX)
        cout << "NO\n";
    else
    {
        cout << "YES\n";

        stack<pair<int, int>> path;
        path.push(make_pair(x2, y2));
        while(currLen >= 0) {
            pair<int ,int> currCell = path.top();
            int currX = currCell.first;
            int currY = currCell.second;
            int dx[4] = {1, 0, -1, 0};
            int dy[4] = {0, 1, 0, -1};
            for (int k = 0; k < 4; k++)
            {
                int ix = currX + dx[k];
                int iy = currY + dy[k];
                if (ix >= 0 && iy >= 0 && ix < w && iy < h)
                {
                    if (minLength[iy][ix] == currLen - 1)
                    {
                        path.push(make_pair(ix, iy));
                        break;
                    }
                }
            }
            currLen--;
        }
        cout << "\n";

        while (!path.empty())
        {
            pair<int ,int> currCell = path.top();
            path.pop();
            int currX = currCell.first + 1;
            int currY = currCell.second + 1;
            cout << currX << ' ' << currY << ' ';
        }
    }

    return 0;
}
