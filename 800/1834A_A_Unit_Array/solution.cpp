// رَبِّ زِدْنِي عِلْمًا
// اے میرے رب! میرے علم میں اضافہ فرما۔
#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;

    vector<int> a(n);
    for (auto &x : a) cin >> x;

    int positive = 0, negative = 0;
    for (int i = 0; i < n; ++i) {
        if (a[i] == 1) positive++;
        else negative++;
    }

    int ops = 0;
    while (positive < negative || negative % 2 == 1) {
        ops++;
        positive++;
        negative--;
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