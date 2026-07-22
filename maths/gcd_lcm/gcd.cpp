// رَبِّ زِدْنِي عِلْمًا
// اے میرے رب! میرے علم میں اضافہ فرما۔

#include <bits/stdc++.h>
using namespace std;

// gcd - greatest common divisor 

// time complexity - O(log min(a, b))
// space complexity - O(1)

long long gcd_euclied(long long a, long long b) {
    a = llabs(a), b = llabs(b);

    while (b != 0) {
        long long r = a % b;
        a = b;
        b = r;
    }

    return a;
}

// time complexity : O(log min(a, b))
// space complexity : O(log min(a, b))   -- recursive call stack
long long gcd_rec(long long a, long long b) {
    
    a = llabs(a), b = llabs(b);
    return (b == 0) ? a : gcd_rec(b, a % b);
}

// same time and space complexity 
int lcm(long long a, long long b) {
    if (a == 0 || b == 0) return 0;
    a = llabs(a), b = llabs(b);
    return a / gcd_euclied(a, b) * b;
}
