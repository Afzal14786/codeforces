// رَبِّ زِدْنِي عِلْمًا
// اے میرے رب! میرے علم میں اضافہ فرما۔
#include <bits/stdc++.h>
using namespace std;


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    long long t; cin >> t;
    int count = 0;

    while (t != 0) {
        if (t % 10 == 4 || t % 10 == 7) count++;
        t /= 10;
    }

    if (count == 4 || count == 7) {
        cout << "YES" << endl; 
    } else {
        cout << "NO" << endl;
    }

    return 0;
}