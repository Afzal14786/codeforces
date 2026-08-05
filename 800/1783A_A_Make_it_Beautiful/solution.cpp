// رَبِّ زِدْنِي عِلْمًا
// اے میرے رب! میرے علم میں اضافہ فرما۔
#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (auto &x : a) cin >> x;

    sort(a.begin(), a.end());

    int max_num = a[n-1];
    int min_num = a[0];

    if (max_num == min_num) {
        cout << "NO" << endl;
    } else {
        cout << "YES" << endl;
        cout << max_num << " ";
        for (int i = 0; i < n - 1; ++i) {
            cout << a[i] << " ";
        }
        cout << endl;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t; cin >> t;
    while (t--) solve();
    return 0;
}