#include <stdio.h>
#include <math.h>
#include <vector>
#include <iostream>
#include <algorithm>
#include <iomanip>
#include <queue>
using namespace std;


vector<int> bfs(int s, int n, vector<vector<int>> g) {
    queue<int> q;
    q.push(s);
    vector<int> d(n, -1);
    d[s] = 0;
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        for (int u : g[v]) {
            if (d[u] == -1) {
                q.push(u);
                d[u] = d[v] + 1;
            }
        }
    }
    return d;
}
int main() {
    int n, m, k;
    cin >> n >> m;
    vector<vector<int>> g(n);
    for (int i = 0; i < m; i++) {
        int v1, v2;
        cin >> v1 >> v2;
        g[v1].push_back(v2);
        g[v2].push_back(v1);
    }
    cin >> k;
    vector<int> a(k);
    for (int i = 0; i < k; i++) {
        cin >> a[i];
    }
    vector<vector<int>> dist(k, vector<int> (n));
    vector<int> used(n, -1);
    for (int i = 0; i < k; i++) {
        dist[i] = bfs(a[i], n, g);
    }
    int are_there_vert = 0;
    for (int i = 0; i < n; i++) {
        int is_vertexeq = 1;
        for (int v1 = 0; v1 < k; v1++) {
            for (int v2 = 0; v2 < k; v2++) {
                if ((dist[v1][i] != dist[v2][i]) || (dist[v1][i] == -1)) {
                    is_vertexeq = 0;
                    break;
                }
            }
            if (is_vertexeq == 0) {
                break;
            }
        }
        if (is_vertexeq == 1) {
            are_there_vert = 1;
            cout << i << ' ';
        }     
    }
    if (are_there_vert == 0) {
        cout << "-";
    }
}