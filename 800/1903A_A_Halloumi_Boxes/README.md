<div align="center">
  <img src="../../assets/images/cf-logo.png" alt="Codeforces Logo" height="80">
  
  <h1><a href="https://codeforces.com/problemset/problem/1903/A" target="_blank">1903A - A. Halloumi Boxes</a></h1>

  <p>time limit per test: 1.0 seconds<br>
  memory limit per test: 256 megabytes</p>
  <p><strong>tags:</strong> <code>brute force, greedy, sortings</code> | <strong>rating:</strong> <code>800</code></p>
</div>

<br>

Theofanis is busy after his last contest, as now, he has to deliver many halloumis all over the world. He stored them inside $n$ boxes and each of which has some number $a_i$ written on it.

He wants to sort them in non-decreasing order based on their number, however, his machine works in a strange way. It can only reverse any subarray†$ of boxes with length **at most** $k$.

Find if it's possible to sort the boxes using **any number of reverses**.

†$ Reversing a subarray means choosing two indices $i$ and $j$ (where $1 \le i \le j \le n$) and changing the array $a_1, a_2, \ldots, a_n$ to $a_1, a_2, \ldots, a_{i-1}, \; a_j, a_{j-1}, \ldots, a_i, \; a_{j+1}, \ldots, a_{n-1}, a_n$. The length of the subarray is then $j - i + 1$.

### Input

The first line contains a single integer $t$ ($1 \le t \le 100$) — the number of test cases.

Each test case consists of two lines.

The first line of each test case contains two integers $n$ and $k$ ($1 \le k \le n \le 100$) — the number of boxes and the length of the maximum reverse that Theofanis can make.

The second line contains $n$ integers $a_1, a_2, \ldots, a_n$ ($1 \le a_i \le 10^{9}$) — the number written on each box.

### Output

For each test case, print YES (case-insensitive), if the array can be sorted in non-decreasing order, or NO (case-insensitive) otherwise.

### Examples

**Input**
```text
5
3 2
1 2 3
3 1
9 9 9
4 4
6 4 2 1
4 3
10 3 830 14
2 1
3 1
```

**Output**
```text
YES
YES
YES
YES
NO
```

### Note

In the first two test cases, the boxes are already sorted in non-decreasing order.

In the third test case, we can reverse the whole array.

In the fourth test case, we can reverse the first two boxes and the last two boxes.

In the fifth test case, it can be shown that it's impossible to sort the boxes.