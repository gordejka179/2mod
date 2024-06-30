#include<stdio.h>
#include<math.h>
#include <vector>
#include <iostream>
using namespace std;


void dfs(int v, int p, int &ans, vector<int> &used, vector<int> &h, vector<int> &d, vector<vector<int>> &g) {
    used[v] = 1;
    d[v] = h[v] = (p == -1 ? 0 : h[p] + 1);
    for (int u : g[v]) {
        if (u != p) {
            if (used[u])
                d[v] = min(d[v], h[u]);
            else {
                dfs(u, v, ans, used, h, d, g);
                d[v] = min(d[v], d[u]);
                if (h[v] < d[u]) {
                    ans++;
                }
            }
        }
    }
}
int main() {
    int n, m;
    cin >> n;
    cin >> m;
    vector<int> used(n, 0);
    vector<int> h(n);
    vector<int> d(n);
    vector<vector<int>> g(n);
    int ans = 0;
    for (int i = 0; i < m; i++) {
        int v1, v2;
        cin >> v1 >> v2;
        g[v2].push_back(v1);;
        g[v1].push_back(v2);
    }
    for (int i = 0; i < n; ++i) {
        if (used[i] == 0) {
            dfs(i, -1, ans, used, h, d, g);
        }
    }
    cout << ans;
}