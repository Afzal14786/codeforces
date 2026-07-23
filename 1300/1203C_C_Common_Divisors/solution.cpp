// رَبِّ زِدْنِي عِلْمًا
// اے میرے رب! میرے علم میں اضافہ فرما۔
#include <bits/stdc++.h>
using namespace std;

long long countDivisors(long long x) {
    long long ans = 1;
    for (long long i = 2; i * i <= x; ++i) {
        if (x % i == 0) {
            int cnt = 0;
            while (x % i == 0) {
                x /= i;
                cnt++;
            }
            ans *= (cnt + 1);
        }
    }

    if (x > 1) {
        ans *= 2;
    }
    return ans;
}



void solve() {
    long long n;
    cin >> n;

    vector<long long> arr(n);
    for (int i = 0; i < n; ++i) {
        cin >> arr[i];
    }

    long long g = 0;
    for (int i = 0; i < n; ++i) g = gcd(g, arr[i]);

    cout << countDivisors(g) << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}