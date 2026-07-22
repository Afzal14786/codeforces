## 1. What is a Divisor?

A **divisor** (also called a **factor**) of an integer `n` is an integer `d` that divides `n` exactly—meaning there is **no remainder**.  

In mathematical terms:  
`d` is a divisor of `n` if there exists an integer `k` such that:  $n = d \times k$

This is written as:  
**`d | n`** (read as "d divides n").

- **Positive Divisors**: In competitive programming, we almost always consider **positive divisors** (i.e., `d > 0`).  
- Example: For `n = 12`, the positive divisors are `{1, 2, 3, 4, 6, 12}`.
- Note: Every positive integer `n` has at least two divisors: `1` and `n` itself (except `n = 1`, which has only one divisor).



## 2. Finding All Divisors of a Number

### Naive Approach – O(n)
```cpp
vector<int> divisors;
for (int i = 1; i <= n; ++i) {
    if (n % i == 0) divisors.push_back(i);
}
```  

> **Use** only when $n \leq 10^6$–$10^7$ (otherwise TLE). 


## Optimized Approach – $O(\sqrt{n})$

Divisors come in pairs: if $i$ divides $n$, then $n/i$ also divides $n$.  
We only need to iterate up to $\sqrt{n}$.  

```cpp
vector<int> divisors;
for (long long i = 1; i * i <= n; ++i) {
    if (n % i == 0) {
        divisors.push_back(i);          // small divisor
        if (i * i != n)                // avoid duplicate for perfect squares
            divisors.push_back(n / i); // large paired divisor
    }
}
sort(divisors.begin(), divisors.end());
```  

> **Works** for $n \leq 10^{14}$ easily.  


## 3. Prime Factorization

Every integer $n > 1$ can be uniquely written as

$$
n = p_1^{a_1} \cdot p_2^{a_2} \cdot \ldots \cdot p_k^{a_k}
$$

where $p_i$ are prime numbers and $a_i \geq 1$.

To factorise, trial divide by $i$ from $2$ to $\sqrt{n}$:  

```cpp
for (int i = 2; i * i <= n; ++i) {
    int cnt = 0;
    while (n % i == 0) { n /= i; cnt++; }
    // i appears cnt times
}
if (n > 1) // n is prime
```   

## 4. Counting the Number of Divisors – $\tau(n)$

If $n = \prod p_i^{a_i}$, 

then $ \tau(n) = \prod (a_i + 1)$

### Implementation (SPF based)

Precompute Smallest Prime Factor (SPF) up to MAXN using a linear sieve. Then factorise each query in $O(\log n)$.  

```cpp
const int MAXN = 1000000;
int spf[MAXN + 1];

void buildSPF() {
    vector<int> primes;
    for (int i = 2; i <= MAXN; ++i) {
        if (!spf[i]) { spf[i] = i; primes.push_back(i); }
        for (int p : primes) {
            if (p > spf[i] || 1LL * i * p > MAXN) break;
            spf[i * p] = p;
        }
    }
}

int countDivisors(int n) {
    int ans = 1;
    while (n > 1) {
        int p = spf[n], cnt = 0;
        while (n % p == 0) { n /= p; cnt++; }
        ans *= (cnt + 1);
    }
    return ans;
}
```  

## 5. Sum of All Divisors – $\sigma(n)$

Using the prime factorisation:

$$
\sigma(n) = \prod \left(1 + p_i + p_i^2 + \ldots + p_i^{a_i}\right)
$$

which can be simplified using the geometric series formula:

$$
\sigma(n) = \prod \frac{p_i^{a_i+1} - 1}{p_i - 1}
$$

### Implementation (trial division)  
```cpp
long long sumOfDivisors(long long n) {
    long long ans = 1;
    for (int i = 2; i * i <= n; ++i) {
        long long current_term = 1, p_power = 1;
        while (n % i == 0) {
            p_power *= i;          // p_power = i^k
            current_term += p_power;
            n /= i;
        }
        ans *= current_term;
    }
    if (n > 1) ans *= (1 + n);   // remaining prime factor
    return ans;
}
```  

## 6. Product of All Divisors

If $n$ has $\tau(n)$ divisors, their product is:

$$
\text{product} = n^{\tau(n)/2}
$$

- If $\tau(n)$ is even, the exponent is an integer.
- If $\tau(n)$ is odd (only when $n$ is a perfect square), the formula still works: $n^{\tau/2}$.

### Implementation  
```cpp
long long productOfDivisors(long long n) {
    long long original = n, total_factors = 1;
    // compute total_factors = τ(n)
    for (int i = 2; i * i <= n; ++i) {
        int cnt = 0;
        while (n % i == 0) { n /= i; cnt++; }
        total_factors *= (cnt + 1);
    }
    if (n > 1) total_factors *= 2;

    long long res = 1;
    long long power = total_factors / 2;
    while (power--) res *= original;
    if (total_factors % 2 == 1) res *= sqrt(original);
    return res;
}
```   

## 7. Sum of σ(i) for i = 1 to n (Prefix Sum of Divisor Sums)

Often we need

$$
S(n) = \sum_{i=1}^n \sigma(i)
$$

**Derivation:**

$$
S(n) = \sum_{i=1}^n \sum_{d|i} d = \sum_{d=1}^n d \cdot \left\lfloor \frac{n}{d} \right\rfloor
$$

We can compute this in $O(\sqrt{n})$ using the harmonic lemma (grouping by equal $\left\lfloor \frac{n}{d} \right\rfloor$ values).

For a given $l$, let

$$
q = \left\lfloor \frac{n}{l} \right\rfloor, \quad r = \left\lfloor \frac{n}{q} \right\rfloor
$$

Then for all $d \in [l, r]$, we have $\left\lfloor \frac{n}{d} \right\rfloor = q$.

Contribution from this block is:

$$
q \cdot \left( \sum_{d=l}^{r} d \right)
$$

### Implementation (modulo $10^9+7$)  

```cpp
const int MOD = 1e9 + 7;
long long sumDivisorPrefix(long long n) {
    long long ans = 0;
    for (long long l = 1, r; l <= n; l = r + 1) {
        long long q = n / l;
        r = n / q;
        long long sum_arith = ((l + r) % MOD) * ((r - l + 1) % MOD) % MOD;
        sum_arith = sum_arith * ((MOD + 1) / 2) % MOD; // multiply by inverse of 2
        ans = (ans + (q % MOD) * sum_arith) % MOD;
    }
    return ans;
}
```  

## 8. Precomputing Divisors for All Numbers up to $N$

A common sieve-like method:

```cpp
vector<vector<int>> allDivisors(int n) {
    vector<vector<int>> divisors(n + 1);
    for (int i = 1; i <= n; ++i) {
        for (int j = i; j <= n; j += i) {
            divisors[j].push_back(i);
        }
    }
    return divisors;
}
```  

- **Complexity:** $O(N \log N)$
- Useful when $N \leq 10^6$.
 

## 9. Summary of Key Formulas  

| Quantity | Formula |
| :--- | :--- |
| Number of divisors $\tau(n)$ | $\prod (a_i + 1)$ |
| Sum of divisors $\sigma(n)$ | $\prod \frac{p_i^{a_i+1} - 1}{p_i - 1}$ |
| Product of divisors | $n^{\tau(n)/2}$ |
| Prefix sum of divisor sums | $\sum_{d=1}^n d \cdot \left\lfloor \frac{n}{d} \right\rfloor$ |


## 10. Practice Problems

- **SPOJ:** DIVCNT (Count Divisors), DIVSUM (Sum of Divisors)
- **Codeforces:** `1475A`, `1366A`, `1374B` (typical divisor problems)
- **CSES:** Sum of Divisors (hard version)

## 11. Final Tips

- Use `long long` for $n$ up to $10^{12}$.
- Precompute SPF if you have many queries.
- The harmonic lemma is a powerful tool for range-sum problems.
- Always sort divisors if you need them in increasing order.
