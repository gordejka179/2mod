#include <stdio.h>
#include <math.h>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

vector<long long> getDeviders(long long x) {
    vector<long long> result;
    for (long long i = 1; i * i <= x; i++) {
        if (x % i == 0) {
            result.push_back(i);
            if (i * i != x) {
                result.push_back(x / i);
            }
        }
    }
    return result;
}

int main() {
    long long n;
    cin >> n;
    vector<long long> a = getDeviders(n);
    sort(a.begin(), a.end());
    cout << "graph" << ' ' << "{" << endl;
    for (long long i : a) {
        cout << i << endl;
    }
    int size1 = size(a);
    for (long long i = size1 - 1; i > 0; i--) {
        for (long long j = i - 1; j >= 0; j--) {
            int is_it_devided = 0;
            if (a[i] % a[j] != 0) {
                is_it_devided = 1;
            }
            for (long long k = j + 1; k < i; k++) {
                if (a[k] % a[j] == 0 && (a[i] % a[k] == 0)) {
                    is_it_devided = 1;
                }
            }
            if (is_it_devided == 0) {
                cout << a[i] << "--" << a[j] << endl;
            }
        }
    }
    cout << "}";
    return 0;
}