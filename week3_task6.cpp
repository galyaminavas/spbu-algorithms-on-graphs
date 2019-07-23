#include <iostream>
#include <bitset>
#include <queue>
#include <set>
#include <vector>

using namespace std;

int n, g[1001][1001], a[1001][1001], u1[1001], u2[1001];

void dfs1(int v){
    u1[v] = 1;
    for (int i = 0; i < n; i++)
        if (g[v][i]!=0 && u1[i]==0)
            dfs1(i);
}
void dfs2(int v){
    u2[v] = 1;
    for (int i = 0; i < n; i++)
        if (g[i][v]!=0 && u2[i]==0)
            dfs2(i);
}
bool visited1(){
    for (int i = 0; i < n; i++){
        if (u1[i]==0) {
            return 0;
        }
    }
    return 1;
}
bool visited2(){
    for (int i = 0; i < n; i++) {
        if (u2[i] == 0)
            return 0;
    }
    return 1;
}
int main() {
    std::ios_base::sync_with_stdio(0);
    std::cin.tie(0);
    cin >> n;
    int l = 0, r = 1000000000, mid;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            cin >> a[i][j];
            l = min(l, a[i][j]);
            r = max(r,a[i][j]);
        }
    }
    while(l < r){
        mid = (l + r)/2;
        for(int i = 0; i < n; i++){
            u1[i] = 0;
            u2[i] = 0;
            for(int j = 0; j < n; j++){
                if (a[i][j] > mid)
                    g[i][j] = 0;
                else g[i][j] = 1;
            }
        }
        dfs1(0);
        bool flag = 0;
        if (visited1()) {
            dfs2(0);
            if (!visited2())
                flag = 1;
        }
        else {
            flag = 1;
        }
        if (flag == 0) {
            r = mid;
        }
        else {
            l = mid + 1;
        }
    }
    cout << l;

    return 0;
}