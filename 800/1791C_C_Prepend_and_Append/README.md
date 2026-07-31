<div align="center">
  <img src="../../assets/images/cf-logo.png" alt="Codeforces Logo" height="80">
  
  <h1><a href="https://codeforces.com/problemset/problem/1791/C" target="_blank">1791C - C. Prepend and Append</a></h1>

  <p>time limit per test: 1.0 seconds<br>
  memory limit per test: 256 megabytes</p>
  <p><strong>tags:</strong> <code>implementation, two pointers</code> | <strong>rating:</strong> <code>800</code></p>
</div>

<br>

Meenal initially had a binary string† $s$ (possibly of length $0$). He performed the following operation several (possibly zero) times:

- Add $\texttt{0}$ to one end of the string and $\texttt{1}$ to the other end of the string. For example, starting from the string $\texttt{1011}$, you can obtain either $\color{red}{\texttt{0}}\texttt{1011}\color{red}{\texttt{1}}$ or $\color{red}{\texttt{1}}\texttt{1011}\color{red}{\texttt{0}}$.

You are given Meenal's final string. What is the length of the **shortest** possible string he could have started with?

† A binary string is a string (possibly the empty string) whose characters are either $\texttt{0}$ or $\texttt{1}$.

### Input

The first line of the input contains an integer $t$ ($1 \leq t \leq 100$) — the number of testcases.

The first line of each test case contains an integer $n$ ($1 \leq n \leq 2000$) — the length of Meenal's final string.

The second line of each test case contains a string $s$ of length $n$ consisting of characters $\texttt{0}$ or $\texttt{1}$, denoting the final string.

### Output

For each test case, output a single nonnegative integer — the shortest possible length of Meenal's original string. Note that Meenal's original string could have been empty, in which case you should output $0$.

### Examples

**Input**
```text
9
3
100
4
0111
5
10101
6
101010
7
1010110
1
1
2
10
2
11
10
1011011010
```

**Output**
```text
1
2
5
0
3
1
0
2
4
```

### Note

In the first test case, the shortest possible string Meenal started with is $\texttt{0}$, and he performed the following operation: $\texttt{0} \to \color{red}{\texttt{1}}\texttt{0}\color{red}{\texttt{0}}$.

In the second test case, the shortest possible string Meenal started with is $\texttt{11}$, and he performed the following operation: $\texttt{11} \to \color{red}{\texttt{0}}\texttt{11}\color{red}{\texttt{1}}$.

In the third test case, the shortest possible string Meenal started with is $\texttt{10101}$, and he didn't perform any operations.

In the fourth test case, the shortest possible string Meenal started with is the empty string (which we denote by $\varepsilon$), and he performed the following operations: $\varepsilon \to \color{red}{\texttt{1}}\texttt{}\color{red}{\texttt{0}} \to \color{red}{\texttt{0}}\texttt{10}\color{red}{\texttt{1}} \to \color{red}{\texttt{1}}\texttt{0101}\color{red}{\texttt{0}}$.

In the fifth test case, the shortest possible string Meenal started with is $\texttt{101}$, and he performed the following operations: $\texttt{101} \to \color{red}{\texttt{0}}\texttt{101}\color{red}{\texttt{1}} \to \color{red}{\texttt{1}}\texttt{01011}\color{red}{\texttt{0}}$.