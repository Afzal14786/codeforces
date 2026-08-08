<div align="center">
  <img src="../../assets/images/cf-logo.png" alt="Codeforces Logo" height="80">
  
  <h1><a href="https://codeforces.com/problemset/problem/1766/A" target="_blank">1766A - A. Extremely Round</a></h1>

  <p>time limit per test: 3.0 seconds<br>
  memory limit per test: 512 megabytes</p>
  <p><strong>tags:</strong> <code>brute force, implementation</code> | <strong>rating:</strong> <code>800</code></p>
</div>

<br>

Let's call a positive integer *extremely round* if it has only one non-zero digit. For example, $5000$, $4$, $1$, $10$, $200$ are extremely round integers; $42$, $13$, $666$, $77$, $101$ are not.

You are given an integer $n$. You have to calculate the number of extremely round integers $x$ such that $1 \le x \le n$.

### Input

The first line contains one integer $t$ ($1 \le t \le 10^4$) — the number of test cases.

Then, $t$ lines follow. The $i$-th of them contains one integer $n$ ($1 \le n \le 999999$) — the description of the $i$-th test case.

### Output

For each test case, print one integer — the number of extremely round integers $x$ such that $1 \le x \le n$.

### Examples

**Input**
```text
5
9
42
13
100
111
```

**Output**
```text
9
13
10
19
19
```