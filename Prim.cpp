#include <stdio.h>
#include <math.h>
#include <vector>
#include <iostream>
#include <algorithm>
#include <iomanip>
using namespace std;

int main() {
	int n, m;
	cin >> n;
	cin >> m;
	vector<int> used(n, 0);
	const int max1 = 10000;
	int max2 = max1;
	vector<int> min_dist(n, max1);
	vector<vector<int>> d(n, vector<int>(n, max1));
	min_dist[0] = 0;
	int ans = 0;
	for (int i = 0; i < m; i++) {
		int from, to, price;
		cin >> from >> to >> price;
		d[from][to] = price;
		d[to][from] = price;
	}
	for (int i = 0; i < n; i++) {
		int v = -179;
		for (int j = 0; j < n; j++) {
			if ((used[j] == 0) && (min_dist[j] < max2)) {
				max2 = min_dist[j];
				v = j;
			}
		}
		used[v] = 1;
		ans += min_dist[v];
		for (int j = 0; j < n; j++) {
			if (used[j] == 0 && d[v][j] != max1) {
				//cout << j << " " << v << min_dist[v] << " " << d[v][j] << endl;
				min_dist[j] = min(min_dist[j], d[v][j]);
			}
		}
		max2 = max1;
	}
	cout << ans << endl;
}