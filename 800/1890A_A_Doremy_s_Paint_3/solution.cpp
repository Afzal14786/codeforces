// رَبِّ زِدْنِي عِلْمًا
// اے میرے رب! میرے علم میں اضافہ فرما۔
#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;
    vector<long long> arr(n);
    for (auto &x : arr) cin >> x;

    map<long long, long long> freq_map;
    for (int i = 0; i < n; ++i) freq_map[arr[i]]++;

    if (freq_map.size() >= 3) {
        cout << "No\n";
    } else {
        long long freq_1 = freq_map.begin()->second;
        long long freq_2 = freq_map.rbegin()->second;

        if (freq_1 == freq_2) {
            cout << "Yes\n";
        } else if (n % 2 == 1 && abs(freq_1 - freq_2) == 1) {
            cout << "Yes\n";
        } else {
            cout << "No\n";
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