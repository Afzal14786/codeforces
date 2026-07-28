// رَبِّ زِدْنِي عِلْمًا
// اے میرے رب! میرے علم میں اضافہ فرما۔
#include <bits/stdc++.h>
using namespace std;

void solve() {
    long long x, k;
    cin >> x >> k;

    if (x % k == 0) {
        cout << 2 << endl;
        cout << x-1 << " " << 1 << endl;
    } else {
        cout << 1 << endl;
        cout << x << endl;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t; cin >> t;
    while (t--) solve();
    return 0;
}