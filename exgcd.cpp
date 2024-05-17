#include <bits/stdc++.h>
using namespace std;

// ax + by = gcd(a,b)

long long exgcd(long long a, long long b, long long &x, long long &y) {
    if (!b) {
        x = 1; 
        y = 0;
        return a;
    }
    long long d = exgcd(b, a % b, x, y);
    long long t = x;
    x = y;
    y = t - (a / b) * y;
    return d; // gcd(a,b)
}
