// رَبِّ زِدْنِي عِلْمًا
// اے میرے رب! میرے علم میں اضافہ فرما۔
#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;
    vector<long long> a(n);

    for (auto &x : a) cin >> x;
    int ops = 0;

    for (int i = 1; i < n; ++i) {
        if (a[i] % 2 == 0 && a[i-1] % 2 == 0) { // means both are even  -- same parity
            a[i] = a[i] * a[i-1];
            ops++;
        } else if (a[i] % 2 != 0 && a[i-1] % 2 != 0) {  // means both are odd --same parity
            a[i] = a[i] * a[i-1];
            ops++;
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