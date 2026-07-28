// رَبِّ زِدْنِي عِلْمًا
// اے میرے رب! میرے علم میں اضافہ فرما۔
#include <bits/stdc++.h>
using namespace std;

void solve() {
    long long a, b, c;
    cin >> a >> b >> c;
    // a = anna
    // b = ketie
    // c = either of them

    if (c % 2 == 0) {
        if (a > b) {
            cout << "First" << endl;
        } else {
            cout << "Second" << endl;
        }
    } else {
        if (b > a) {
            cout << "Second" << endl;
        } else {
            cout << "First" << endl;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    long long t; cin >> t;
    while (t--) solve();
    return 0;
}