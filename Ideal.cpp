#include<stdio.h>
#include<math.h>
#include <vector>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <map>
#include <queue>
using namespace std;

int compare(vector<int> a, vector<int> b, int size) {
    for (int i = 0; i < size; i++) {
        //cout << a[i] << " " << b[i] << endl;
        if (a[i] > b[i]) {
            return 1;
        }
        if (a[i] < b[i]) {
            return -1;
        }
    }
    return 1;
}
int find_color(int v, int w, vector<vector<int>>& g, map<pair<int, int>, int>& edges){
    pair<int, int> p = make_pair(v, w);
    auto it = edges.find(p);
    if (it != edges.end()) {
        return it->second;
    }
}


void change_way(int v, int w, int size, vector<int>& parents, vector<vector<int>>& g, map<pair<int, int>, int> & edges) {
    vector<int> cway, cway2;
    cway.push_back(find_color(v, w, g, edges));
    int copyw = w;
    int copyv = v;
    while (v != 0) {
        cway.push_back(find_color(v, parents[v], g, edges));
        v = parents[v];
    }
    while (w != 0) {
        cway2.push_back(find_color(w, parents[w], g, edges));
        w = parents[w];
    }
    reverse(cway.begin(), cway.end());
    reverse(cway2.begin(), cway2.end());
    if (compare(cway, cway2, size) == -1){
        parents[copyw] = copyv;
    }
}


int main() {
    int n, m;
    cin >> n >> m;
    vector<int> used(n, 0);
    vector<int> min_dist(n, n);
    min_dist[0] = 0;
    vector<int> parents(n, -1);
    vector<vector<int>> g(n);
    map<pair<int, int>, int> edges_and_color;
    queue<int> q;
    q.push(0);
    for (int i = 0; i < m; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        g[a - 1].push_back(b - 1);
        g[b - 1].push_back(a - 1);
        pair<int, int> p1 = make_pair(a - 1, b - 1);
        pair<int, int> p2 = make_pair(b - 1, a - 1);
        auto it = edges_and_color.find(p1);
        if (it != edges_and_color.end()) {
            it->second = min(it->second, c);
        }
        else{
            edges_and_color.insert(make_pair(p1, c));
        }
        it = edges_and_color.find(p2);
        if (it != edges_and_color.end()) {
            it->second = min(it->second, c);
        }
        else{
            edges_and_color.insert(make_pair(p2, c));
        }
    }
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        for (int w : g[v]) {
            if (min_dist[w] > min_dist[v] + 1) {
                parents[w] = v;
                min_dist[w] = min_dist[v] + 1;
                q.push(w);
            }
            else{
                if (min_dist[w] == min_dist[v] + 1) {
                    change_way(v, w, min_dist[w], parents, g, edges_and_color);
                }
            }
        }
    }
    cout << min_dist[n - 1] << endl;
    int v = n - 1;
    vector<int> way;
    while (v != 0) {
        way.push_back(find_color(v, parents[v], g, edges_and_color));
        v = parents[v];
    }
    reverse(way.begin(), way.end());
    for (int i : way) {
        cout << i << " ";
    }

}