// رَبِّ زِدْنِي عِلْمًا
// اے میرے رب! میرے علم میں اضافہ فرما۔
#include <bits/stdc++.h>
using namespace std;

vector<long long> round_number;

void solve() {
    long long n;
    cin >> n;

    long long ans = 0;
    for (int i = 0; i < round_number.size(); ++i) {
        if (round_number[i] <= n) ans++;
        else break;
    }

    cout << ans << endl;
}

bool check(long long x) {
    long long count_of_digits = 0, count_of_zeros = 0;
    while (x) {
        if (x % 10 == 0) count_of_zeros++;
        count_of_digits++;
        x /= 10;
    }

    return count_of_zeros == count_of_digits - 1;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    for (int i = 1; i <= 999999; ++i) {
        if (check(i)) round_number.push_back(i);
    }

    int t; cin >> t;
    while (t--) solve();
    return 0;
}