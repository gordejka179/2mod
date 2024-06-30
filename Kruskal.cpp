

#include <stdio.h>
#include <math.h>
#include <vector>
#include <iostream>
#include <algorithm>
#include <iomanip>
using namespace std;

int main() {
    int m;
    int n;
    double dist = 0;
    cin >> n;
    m = n * (n - 1) / 2;
    vector<pair<double, pair<int, int>>> g;
    vector<pair<int, int>> coords(n);
    for (int i = 0; i < n; i++) {
        cin >> coords[i].first >> coords[i].second;
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i != j) {
                double dist = sqrt(pow((coords[i].first - coords[j].first), 2) + pow((coords[i].second - coords[j].second), 2));
                double coord1 = i;
                double coord2 = j;
                pair<int, int> p1 = make_pair(i, j);
                g.push_back(make_pair(dist, p1));
            }
        }
    }
    sort(g.begin(), g.end());
    vector<int> tree_id(n);
    for (int i = 0; i < n; ++i)
        tree_id[i] = i;
    for (int i = 0; i < m; ++i)
    {
        int v1 = g[i].second.first;
        int v2 = g[i].second.second;
        double length = g[i].first;
        if (tree_id[v1] != tree_id[v2])
        {
            dist += length;
            int old_id = tree_id[v2], new_id = tree_id[v1];
            for (int j = 0; j < n; ++j)
                if (tree_id[j] == old_id)
                    tree_id[j] = new_id;
        }
    }
    cout << fixed << setprecision(2) << dist;
    //реализацию алгоритма Краскала взял отсюда: http://e-maxx.ru/algo/mst_kruskal

}

