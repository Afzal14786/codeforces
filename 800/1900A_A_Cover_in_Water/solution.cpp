// رَبِّ زِدْنِي عِلْمًا
// اے میرے رب! میرے علم میں اضافہ فرما۔
#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;
    string str;
    cin >> str;

    bool continuous_cell = false;
    int empty_cells = 0;

    for (int i = 0; i < n; ++i) {
        if (str[i] == '.' && i  < n && str[i+1] == '.' && i + 1 < n && str[i+2] == '.' && i+2 < n) {
            continuous_cell = true;
            break;
        }
        if (str[i] == '.') empty_cells++;
    }

    if (continuous_cell) {
        cout << 2 << endl;
    } else {
        cout << empty_cells << endl;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t; cin >> t;
    while (t--) solve();
    return 0;
}