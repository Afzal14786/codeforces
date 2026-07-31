// رَبِّ زِدْنِي عِلْمًا
// اے میرے رب! میرے علم میں اضافہ فرما۔
#include <bits/stdc++.h>
using namespace std;

void solve() {
    long long n;
    cin >> n;
    string s;  // contains only 0's & 1's  ==> Binary String
    cin >> s;

    long long ans = n;
    long long left = 0, right = n-1;
    while (left <= right) {
        if (s[left] != s[right]) {
            ans -= 2;
        } else break;

        left++;
        right--;
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