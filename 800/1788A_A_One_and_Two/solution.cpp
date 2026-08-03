// رَبِّ زِدْنِي عِلْمًا
// اے میرے رب! میرے علم میں اضافہ فرما۔
#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (auto &x : a) cin >> x;

    int total_2_count = 0;
    for (int x : a) if (x == 2) total_2_count++;

    int curr_no_of_2 = 0;
    int ans = -1;

    for (int i = 0; i < n; ++i) {
        if (a[i] == 2) curr_no_of_2++;
        if (curr_no_of_2 == (total_2_count - curr_no_of_2)) {
            ans = i + 1;
            break;
        }
    }

    cout << ans << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t; cin >> t;
    while (t--) solve();
    return 0;
}