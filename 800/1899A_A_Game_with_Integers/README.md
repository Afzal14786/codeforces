<div align="center">
  <img src="../../assets/images/cf-logo.png" alt="Codeforces Logo" height="80">
  
  <h1><a href="https://codeforces.com/problemset/problem/1899/A" target="_blank">1899A - A. Game with Integers</a></h1>

  <p>time limit per test: 1.0 seconds<br>
  memory limit per test: 256 megabytes</p>
  <p><strong>tags:</strong> <code>games, math, number theory</code> | <strong>rating:</strong> <code>800</code></p>
</div>

<br>

Vanya and Vova are playing a game. Players are given an integer $n$. On their turn, the player can add $1$ to the current integer or subtract $1$. The players take turns; Vanya starts. If **after** Vanya's move the integer is divisible by $3$, then he wins. If $10$ moves have passed and Vanya has not won, then Vova wins.

Write a program that, based on the integer $n$, determines who will win if both players play optimally.

### Input

The first line contains the integer $t$ ($1 \leq t \leq 100$) — the number of test cases.

The single line of each test case contains the integer $n$ ($1 \leq n \leq 1000$).

### Output

For each test case, print "First" without quotes if Vanya wins, and "Second" without quotes if Vova wins.

### Examples

**Input**
```text
6
1
3
5
100
999
1000
```

**Output**
```text
First
Second
First
First
Second
First
```