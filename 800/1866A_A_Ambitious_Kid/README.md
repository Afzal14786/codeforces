<div align="center">
  <img src="../../assets/images/cf-logo.png" alt="Codeforces Logo" height="80">
  
  <h1><a href="https://codeforces.com/problemset/problem/1866/A" target="_blank">1866A - A. Ambitious Kid</a></h1>

  <p>time limit per test: 1.0 seconds<br>
  memory limit per test: 256 megabytes</p>
  <p><strong>tags:</strong> <code>math</code> | <strong>rating:</strong> <code>800</code></p>
</div>

<br>

Chaneka, Pak Chanek's child, is an ambitious kid, so Pak Chanek gives her the following problem to test her ambition.

Given an array of integers $[A_1, A_2, A_3, \ldots, A_N]$. In one operation, Chaneka can choose one element, then increase or decrease the element's value by $1$. Chaneka can do that operation multiple times, even for different elements.

What is the minimum number of operations that must be done to make it such that $A_1 \times A_2 \times A_3 \times \ldots \times A_N = 0$?

### Input

The first line contains a single integer $N$ ($1 \leq N \leq 10^5$).

The second line contains $N$ integers $A_1, A_2, A_3, \ldots, A_N$ ($-10^5 \leq A_i \leq 10^5$).

### Output

An integer representing the minimum number of operations that must be done to make it such that $A_1 \times A_2 \times A_3 \times \ldots \times A_N = 0$.

### Examples

**Input**
```text
3
2 -6 5
```

**Output**
```text
2
```

**Input**
```text
1
-3
```

**Output**
```text
3
```

**Input**
```text
5
0 -1 0 1 0
```

**Output**
```text
0
```

### Note

In the first example, initially, $A_1\times A_2\times A_3=2\times(-6)\times5=-60$. Chaneka can do the following sequence of operations:
- Decrease the value of $A_1$ by $1$. Then, $A_1\times A_2\times A_3=1\times(-6)\times5=-30$
- Decrease the value of $A_1$ by $1$. Then, $A_1\times A_2\times A_3=0\times(-6)\times5=0$

In the third example, Chaneka does not have to do any operations, because from the start, it already holds that $A_1\times A_2\times A_3\times A_4\times A_5=0\times(-1)\times0\times1\times0=0$