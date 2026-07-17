// رَبِّ زِدْنِي عِلْمًا
// اے میرے رب! میرے علم میں اضافہ فرما۔
#include <bits/stdc++.h>
using namespace std;

void solve() {
    long long n, x;
    cin >> n >> x;
    vector<long long> fuel_stations;
    fuel_stations.push_back(0);  // we can't fuel at position 0
    for (int i = 0; i < n; ++i) {
        long long points;
        cin >> points;
        fuel_stations.push_back(points);
    }
    fuel_stations.push_back(x);  // put the last value 
    n = fuel_stations.size();

    long long min_capacity = INT_MIN;
    for (int i = 1; i < n; ++i) {
        if (i == n-1) {
            min_capacity = max(min_capacity, 2 * (fuel_stations[i] - fuel_stations[i-1]));
        } else {
            min_capacity = max(min_capacity, fuel_stations[i] - fuel_stations[i-1]);
        }
    }

    cout << min_capacity << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t; cin >> t;
    while (t--) solve();
    return 0;
}