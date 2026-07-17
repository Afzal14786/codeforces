// رَبِّ زِدْنِي عِلْمًا
// اے میرے رب! میرے علم میں اضافہ فرما۔
#include <bits/stdc++.h>
using namespace std;

void printArr(const vector<int> & nums, const string & msg) {
    cout << msg << ": ";
    for (size_t i = 0; i < nums.size(); ++i) {
        cout << nums[i] << (i == nums.size() - 1 ? "" : ", ");
    }
    cout << endl;
}

// prime factorization...
// calculating number of factors

long long countDivisor(long long n) {
    long long ans = 1;
    for (int i = 1; i * i <= n; ++i) {
        int count = 0;
        while (n % i  == 0) {
            n /= i;
            count++;
        }
        ans *= (count + 1);
    }

    return (n > 1) ? ans *= 2 : ans;
}

// sum of all the factors

long long sumOfFactores(long long n) {
    long long ans = 1;

    for (int i = 2; i * i <= n; ++i) {
        long long current_term = 1;
        long long p_power = 1;


        while (n % i == 0) {
            p_power *= i;
            current_term += p_power;
            n /= i;
        }

        ans *= current_term;
    }

    return (n > 1) ? ans *= (1 + n) : ans;
}


// pre-computing Divisor for all numbers
vector<vector<int>> allDivisors(long long n) {
    vector<vector<int>> divisors(n+1);

    for (int i = 1; i <= n; ++i) {  // N times
        for (int j = i; j <= n; j += i) {  // log N times
            divisors[j].push_back(i);
        }
    }

    return divisors;
}

// product of factors of a given number
long long product(long long n) {
    long long orignal_n = n;
    long long total_factors =  1;
    for (int i = 2; i * i <= n; ++i) {
        int count = 0;
        while (n % i == 0) {
            n /= i;
            count++;
        }

        total_factors *= (count + 1);
    }
    
    long long res = 1;

    if (n > 1) total_factors *= 2;
    long long power = total_factors / 2;

    for (int i = 0; i < power; ++i)  res *= orignal_n;
    if (total_factors % 2 != 0)  res *= sqrt(orignal_n);

    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    long long n; // Changed to long long to support up to 10^12
    if (!(cin >> n)) return 0;
    
    // --- Brute Force Approach ---
    // Time Complexity: O(n)
    // Works for: n <= 10^8 (Within 1-second time limit)
    vector<int> divisors;
    if (n <= 1000000) { // Safety check to prevent TLE during local tests
        for (int i = 1; i <= n; ++i) {
            if (n % i == 0) 
                divisors.push_back(i);
        }
        printArr(divisors, "Brute Force Approach For Calculating Divisors");
    } else {
        cout << "Brute Force skipped to prevent Time Limit Exceeded (TLE).\n";
    }

    // --- Optimized Approach ---
    // Time Complexity: O(sqrt(n))
    // Works for: n <= 10^14+ 
    // Best and most efficient for CP
    vector<int> divisors2;
    for (long long i = 1; i * i <= n; ++i) {
        if (n % i == 0) {
            divisors2.push_back(i);       // Small divisor
            if (i * i != n) {             // Prevent duplicate for perfect squares (e.g., 4*4 = 16)
                divisors2.push_back(n / i); // Large paired divisor
            }
        }
    }

    // Divisors are found in pairs, so they must be sorted to look identical to brute force
    sort(divisors2.begin(), divisors2.end());

    printArr(divisors2, "Optimized Approach For Calculating Divisors");
    
    return 0;
}
