// رَبِّ زِدْنِي عِلْمًا
// اے میرے رب! میرے علم میں اضافہ فرما۔
#include <bits/stdc++.h>
using namespace std;

void solve() {
    long long a, b, k;
    cin >> a >> b >> k;

    long long g = gcd(a, b);
    if (max(a/g, b/g) <= k) {
        cout << 1 << endl;
    } else {
        cout << 2 << endl;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    long long t; cin >> t;
    while (t--) solve();
    return 0;
}