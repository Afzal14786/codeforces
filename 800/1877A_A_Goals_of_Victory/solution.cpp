// رَبِّ زِدْنِي عِلْمًا
// اے میرے رب! میرے علم میں اضافہ فرما۔
#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;
    int sum = 0;
    vector<int> arr(n);

    for (int i = 0; i < n-1; ++i) {
        cin >> arr[i];
    }

    for (int i = 0; i < n-1; ++i) {
        sum += arr[i];
    }

    sum = -1 * sum;
    cout << sum << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t; cin >> t;
    while (t--) solve();
    return 0;
}