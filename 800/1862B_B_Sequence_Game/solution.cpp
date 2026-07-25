// رَبِّ زِدْنِي عِلْمًا
// اے میرے رب! میرے علم میں اضافہ فرما۔
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

void solve() {
    long long n;
    cin >> n;
    vector<ll> b(n);
    
    for (int i = 0; i < n; ++i) cin >> b[i];

    vector<ll> a;
    a.push_back(b[0]);  // the initial number is always there
    for (int i = 1; i < n; ++i) {
        if (b[i] >= b[i-1]) a.push_back(b[i]);
        else if (b[i] < b[i-1]) {
            a.push_back(b[i]);
            a.push_back(b[i]);
        }
    }

    cout << a.size() << endl;
    for (long long &x : a) {
        cout << x << " ";
    }
    cout << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    long long t; cin >> t;
    while (t--) solve();
    return 0;
}

