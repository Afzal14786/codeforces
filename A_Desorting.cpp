// رَبِّ زِدْنِي عِلْمًا
// اے میرے رب! میرے علم میں اضافہ فرما۔
#include <bits/stdc++.h>
using namespace std;


void solve() {
    int n;
    cin >> n;
    vector<long long> a(n);
    for (int i = 0; i < n; ++i) cin >> a[i];
    long long ops = INT_MAX;

    for (int i = 0; i < n-1; ++i) {
        if (a[i] <= a[i+1]) {
            long long diff = a[i+1] - a[i];
            long long ops_req = (diff/2) + 1;

            ops = min(ops, ops_req);
        } else {
            ops = 0;
        }
    }

    cout << ops << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t; cin >> t;
    while (t--) solve();
    return 0;
}