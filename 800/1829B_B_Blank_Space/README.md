<div align="center">
  <img src="../../assets/images/cf-logo.png" alt="Codeforces Logo" height="80">
  
  <h1><a href="https://codeforces.com/problemset/problem/1829/B" target="_blank">1829B - B. Blank Space</a></h1>

  <p>time limit per test: 1.0 seconds<br>
  memory limit per test: 256 megabytes</p>
  <p><strong>tags:</strong> <code>implementation</code> | <strong>rating:</strong> <code>800</code></p>
</div>

<br>

You are given a binary array $a$ of $n$ elements, a binary array is an array consisting only of $0$s and $1$s.

A blank space is a segment of **consecutive** elements consisting of only $0$s.

Your task is to find the length of the longest blank space.

### Input

The first line contains a single integer $t$ ($1 \leq t \leq 1000$) — the number of test cases.

The first line of each test case contains a single integer $n$ ($1 \leq n \leq 100$) — the length of the array.

The second line of each test case contains $n$ space-separated integers $a_i$ ($0 \leq a_i \leq 1$) — the elements of the array.

### Output

For each test case, output a single integer — the length of the longest blank space.

### Examples

**Input**
```text
5
5
1 0 0 1 0
4
0 1 1 1
1
0
3
1 1 1
9
1 0 0 0 1 0 0 0 1
```

**Output**
```text
2
1
1
0
3
```