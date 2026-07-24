// رَبِّ زِدْنِي عِلْمًا
// اے میرے رب! میرے علم میں اضافہ فرما۔
#include <bits/stdc++.h>
using namespace std;

// taking out the abs minimum value 
void solve() {
    long long n;
    cin >> n;

    vector<long long> arr(n);
    for (int i = 0; i < n; ++i) {
        int x;
        cin >> x;
        arr[i] = abs(x);
    }

    int min_val = *min_element(arr.begin(), arr.end());
    cout << min_val << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}