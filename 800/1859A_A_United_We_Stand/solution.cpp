// رَبِّ زِدْنِي عِلْمًا
// اے میرے رب! میرے علم میں اضافہ فرما۔
#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;
    vector<long long> a(n);
    for (int i = 0; i < n; ++i) cin >> a[i];

    long long max_elem = *max_element(a.begin(), a.end());
    vector<int> b, c;  // intial empty array
    for (int i = 0; i < n; ++i) {  // travels on the first array a
        if (a[i] != max_elem) b.push_back(a[i]);
        else c.push_back(a[i]);
    }

    if (b.size() == 0) {
        cout << -1 << endl;
    } else {
        cout << b.size() << " " << c.size() << endl;
        for (int x : b) {
            cout << x << " ";
        }
        cout << endl;
        for (int x : c) {
            cout << x << " ";
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