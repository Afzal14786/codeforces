// رَبِّ زِدْنِي عِلْمًا
// اے میرے رب! میرے علم میں اضافہ فرما۔
#include <bits/stdc++.h>
using namespace std;

void solve() {
    long long n;
    cin >> n;
    vector<long long> a(n);
    for (auto &x : a) cin >> x;

    long long total_xor = 0;
    for (long long x : a) total_xor ^= x;

    if (n % 2 == 1) {
        cout << total_xor << endl;
    } else {
        if (total_xor == 0) {
            cout << total_xor << endl;
        } else {
            cout << -1 << endl;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t; cin >> t;
    while (t--) solve();
    return 0;
}