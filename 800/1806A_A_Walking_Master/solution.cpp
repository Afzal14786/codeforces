// رَبِّ زِدْنِي عِلْمًا
// اے میرے رب! میرے علم میں اضافہ فرما۔
#include <bits/stdc++.h>
using namespace std;

void solve() {
    int sx, sy, dx, dy;
    cin >> sx >> sy >> dx >> dy;

    if (dy < sy) {
        cout << -1 << endl;
        return;
    }

    int moves = dy - sy;
    sx += moves;

    if (sx < dx) {
        cout << -1 << endl;
        return;
    }

    moves += (sx - dx);
    cout << moves << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    long long t; cin >> t;
    while (t--) solve();
    return 0;
}