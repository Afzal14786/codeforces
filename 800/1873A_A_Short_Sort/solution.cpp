// رَبِّ زِدْنِي عِلْمًا
// اے میرے رب! میرے علم میں اضافہ فرما۔
#include <bits/stdc++.h>
using namespace std;


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t; cin >> t;

    while (t--) {
        string str;
        cin >> str;

        cout << ((str == "cab" || str == "bca") ? "NO\n" : "YES\n");
    }

    return 0;
}