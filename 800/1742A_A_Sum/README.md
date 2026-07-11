<div align="center">
  <img src="../../assets/images/cf-logo.png" alt="Codeforces Logo" height="80">
  
  <h1><a href="https://codeforces.com/problemset/problem/1742/A" target="_blank">1742A - A. Sum</a></h1>

  <p>time limit per test: 1.0 seconds<br>
  memory limit per test: 256 megabytes</p>
  <p><strong>tags:</strong> <code>implementation</code> | <strong>rating:</strong> <code>800</code></p>
</div>

<br>

You are given three integers $a$, $b$, and $c$. Determine if one of them is the sum of the other two.

### Input

The first line contains a single integer $t$ ($1 \leq t \leq 9261$) — the number of test cases.

The description of each test case consists of three integers $a$, $b$, $c$ ($0 \leq a, b, c \leq 20$).

### Output

For each test case, output "YES" if one of the numbers is the sum of the other two, and "NO" otherwise.

You can output the answer in any case (for example, the strings "yEs", "yes", "Yes" and "YES" will be recognized as a positive answer).

### Examples

**Input**
```text
7
1 4 3
2 5 8
9 11 20
0 0 0
20 20 20
4 12 3
15 7 8
```

**Output**
```text
YES
NO
YES
YES
NO
NO
YES
```

### Note

In the first test case, $1 + 3 = 4$.

In the second test case, none of the numbers is the sum of the other two.

In the third test case, $9 + 11 = 20$.