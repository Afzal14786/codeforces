// رَبِّ زِدْنِي عِلْمًا
// اے میرے رب! میرے علم میں اضافہ فرما۔
#include <bits/stdc++.h>
using namespace std;

void solve() {
    long long n;
    cin >> n;

    if (n == 10) {
        cout << "-1" << endl;
        return;
    }

    long long A, B;

    A = n % 12;
    B = (n - A);

    if (A == 10) {
        A += 12;
        B -= 12;
    }

    cout << A << " " << B << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t; cin >> t;
    while (t--) solve();
    return 0;
}