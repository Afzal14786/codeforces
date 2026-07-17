// رَبِّ زِدْنِي عِلْمًا
// اے میرے رب! میرے علم میں اضافہ فرما۔
#include <bits/stdc++.h>
using namespace std;

using int64 = long long;
const int MOD = 1e9 + 7;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int64 n;
    cin >> n;

    int64 ans = 0;
    for (int64 l = 1, r; l <= n; l = r + 1) {
        int64 q = n / l;
        r = n / q;
        // sum of l + (l+1) + ... + r
        int64 sum_arith = ((l + r) % MOD) * ((r - l + 1) % MOD) % MOD;
        sum_arith = sum_arith * ((MOD + 1) / 2) % MOD; // multiply by inverse of 2 modulo MOD
        ans = (ans + (q % MOD) * sum_arith) % MOD;
    }

    cout << ans << '\n';
    return 0;
}