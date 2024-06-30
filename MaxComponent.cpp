#include <iostream>;
#include <vector>;

using namespace std;
int n;
int m;
vector<vector<int>> g;
vector<int> used;
vector<int> comp;
vector<int> sizes;
vector<int> eagles;
vector<int> mini;
int cc = 0;
void dfs(int v, int key) {
    used[v] = cc;
    if (key == 0) {
        for (auto to : g[v]) {
            if (used[to] == -1) {
                dfs(to, 0);
            }
        }

    }
    else{
        mini[cc] = min(mini[cc], v);
        sizes[cc]++;
        used[v] = cc;
        for (auto to : g[v]) {
            eagles[cc]++;
            if (used[to] == -1) {
                dfs(to, 1);
            }
        }
    }
}
int main() {
    cin >> n;
    cin >> m;
    g.resize(n);
    used.resize(n, -1);
    for (int i = 0; i < m; i++) {
        int v1, v2;
        cin >> v1 >> v2;
        g[v1].push_back(v2);
        g[v2].push_back(v1);
    }
    for (int i = 0; i < n; ++i) {
        if (used[i] == -1) {
            dfs(i, 0);
            cc++;
        }
    }
    vector<vector<int>> cv(cc);
    sizes.resize(cc, 0);
    eagles.resize(cc, 0);
    mini.resize(cc, 0);
    used.resize(n, -1);
    for (int i = 0; i < n; i++) {
        used[i] = -1;
    }
    cc = 0;
    for (int i = 0; i < n; ++i) {
        if (used[i] == -1) {
            dfs(i, 1);
            cc++;
        }
    }
    for (int i = 0; i < n; i++) {
        cv[used[i]].push_back(i);
    }
    int best = 0;
    for (int i = 0; i < cc; i++) {
        if (sizes[i] > sizes[best]) {
            best = i;
        }
        else {
            if (sizes[i] == sizes[best]) {
                if (eagles[i] > eagles[best]) {
                    best = i;
                }
                else {
                    if (eagles[i] == eagles[best]) {
                        if (mini[i] < mini[best]) {
                            best = i;
                        }
                    }
                }
            }
        }
    }
    cout << "graph {" << endl;
    for (int i = 0; i < n; i++) {
        if (used[i] == best) {
            cout << i << "[color = red]" << endl;
        }
        else {
            cout << i << endl;
        }
    }
    for (int i = 0; i < cc; i++) {
        for (auto v : cv[i]) {
            for (auto v2 : g[v]) {
                if (i == best) {
                    cout << v << " -- " << v2 << "[color = red]" << endl;
                }
                else {
                    cout << v << " -- " << v2 << endl;
                }
                
            }
        }
        
    }

    cout << "}";
    return 0;


}