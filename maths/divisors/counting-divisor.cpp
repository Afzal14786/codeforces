// رَبِّ زِدْنِي عِلْمًا
// اے میرے رب! میرے علم میں اضافہ فرما۔
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1000000;
int spf[MAXN + 1];

// // naive solution
// void solve() {
//     int n;
//     cin >> n;

//     long long count = 0;
//     for (long long d = 1; d * d <= n; ++d) {
//         if (n % d == 0) {
//             count++;
//             if (d != n/d) count++; 
//         }
//     }
    
//     cout << count << endl;
// }

void buildSPF() {
    vector<int> primes;
    for (int i = 2; i <= MAXN; ++i) {
        if (!spf[i]) {
            spf[i] = i;
            primes.push_back(i);
        }
        for (int p : primes) {
            if (p > spf[i] || 1LL * i * p > MAXN) break;
            spf[i*p] = p;
        }
    }
}

void solve() {
    int n; 
    cin >> n;

    int ans = 1;

    while (n > 1) {
        int cnt = 0;
        int p = spf[n];

        while (n % p == 0) {
            n /= p;
            ++cnt;
        }
        ans *= (cnt + 1);
    }

    cout << ans << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    buildSPF();

    int t; cin >> t;
    while (t--) solve();
    return 0;
}