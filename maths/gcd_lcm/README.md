# Greatest Common Divisor (GCD)

The **Greatest Common Divisor (GCD)** of two integers $a$ and $b$ is the largest positive integer that divides both $a$ and $b$.

---

## Prime Factorisation Method

Find the prime factorisation of each number, then take the lowest power of each common prime factor.

### Example

* $36 = 2^2 \times 3^2$
* $60 = 2^2 \times 3 \times 5$

**Common prime factors:** $2$ and $3$.

Take the lowest exponent for each:
$$\gcd(36, 60) = 2^2 \times 3^1 = 4 \times 3 = 12$$

---  

# Properties of GCD

## GCD with Zero

* $\gcd(a, 0) = |a|$ for $a \neq 0$
  * Every non-zero integer divides $0$, so the largest divisor of $0$ and $a$ is $|a|$.
* $\gcd(0, 0) = 0$ (by convention).

---

## Sign Does Not Matter

$$\gcd(a, b) = \gcd(|a|, |b|)$$

---

## Divisibility Property

If $a \mid b$ (i.e., $a$ divides $b$), then:
$$\gcd(a, b) = |a|$$

* **Example:** $\gcd(12, 6) = 6$ because $6 \mid 12$.

---

## Subtraction Property (Euclidean Subtraction)

For $a > b$:
$$\gcd(a, b) = \gcd(a - b, b)$$

### Proof

1. Let $d$ divide both $a$ and $b$. Write $a = d \cdot m$ and $b = d \cdot n$.
2. Then $a - b = d(m - n)$, so $d$ divides $a - b$ as well.
3. Conversely, any common divisor of $a - b$ and $b$ also divides their sum $(a - b) + b = a$.
4. Hence, the set of common divisors is identical.  

---  

Euclidean Algorithm
Subtraction‑based version

Repeatedly subtract the smaller number from the larger until one becomes 0; the other number is the GCD.

Example: gcd⁡(48,18)gcd(48,18)
48→(48−18,18)=(30,18)→(12,18)→(12,6)→(6,6)→(0,6)
48→(48−18,18)=(30,18)→(12,18)→(12,6)→(6,6)→(0,6)

Thus gcd⁡(48,18)=6gcd(48,18)=6.

Drawback: Very slow when one number is much larger than the other (many subtractions needed).
Optimised version: modulo operation

Instead of repeated subtraction, we use the remainder:
a=q⋅b+r(0≤r<b)
a=q⋅b+r(0≤r<b)

Then:
gcd⁡(a,b)=gcd⁡(b,r)
gcd(a,b)=gcd(b,r)

because a−q⋅b=ra−q⋅b=r. This reduces the problem in a single step.
### Implementations (C++)

**Iterative (preferred for competitive programming)**

```cpp
long long gcd_iterative(long long a, long long b) {
    a = llabs(a);
    b = llabs(b);
    while (b != 0) {
        long long r = a % b;
        a = b;
        b = r;
    }
    return a;
}
```  

* **Time complexity:** $O(\log \min(a, b))$
* **Space complexity:** $O(1)$ (iterative)

**Recursive**  

```cpp
long long gcd_recursive(long long a, long long b) {
    a = llabs(a);
    b = llabs(b);
    return (b == 0) ? a : gcd_recursive(b, a % b);
}
```  
* **Time complexity:** $O(\log \min(a, b))$
* **Space complexity:** $O(\log \min(a, b))$  -- *due to call stack (recursive)*

---  

## Notes

* The Euclidean algorithm runs in logarithmic time; the worst case occurs for consecutive Fibonacci numbers.
* `llabs` is used to handle negative inputs; alternatively, you can take absolute values before calling.  

---  
<br/>

# LCM – Least Common Multiple

The **Least Common Multiple** of two integers $a$ and $b$ is the smallest positive integer that is divisible by both $a$ and $b$.

---

## Relation with GCD

$$\text{lcm}(a, b) = \frac{|a \times b|}{\gcd(a, b)}$$

This formula allows us to compute the LCM using the Euclidean algorithm (for GCD) in $O(\log \min(a, b))$ time.

---

## Implementation (Overflow-Safe)

A common pitfall is integer overflow when multiplying $a \times b$ before dividing by the GCD. To avoid this, perform the division first:  

```cpp
long long lcm(long long a, long long b) {
    if (a == 0 || b == 0) return 0;    // LCM is undefined for zero, often defined as 0
    a = llabs(a);
    b = llabs(b);
    return a / gcd(a, b) * b;          // safe: a/gcd is small enough
}
```  

> **Note:** The LCM is usually defined for positive integers. If you want to handle negative numbers, take absolute values.  
