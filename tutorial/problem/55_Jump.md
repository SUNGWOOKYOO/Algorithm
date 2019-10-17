# 55. Jump Game

[leetcode](https://leetcode.com/problems/jump-game/)

## Problem Definition

Given an size $n$ array $a$ 

Let $J_i$ be a possibility to jump from start index $0$ to last index $i$



### Naive
We start from the first position and jump to every index that is reachable. We repeat the process until last index is reached. It takes $O(2^n)$ 



### Dynamic Programming

*Recursion*
$$
J_i = 
\begin{cases} 
True & \text{if } i = 0 \\
\bigcup_{k=0}^{i-1} (J_k  \and (a_k \ge i-k)) & \text{if }i\ge0
\end{cases}
$$
Using above recursive equation, we can think it as a reculsive way.

We can find a solution by calling $J_{n-1}$.

>  <font color=red>Warning: </font> boolean values cannot notify memoization before it called.
>
> therefore, `memo` array can be used in order to check memoization was happend.

```c++
// O(n^2) 
bool lookup(vector<int>& a, bool* j, bool* memo, int i) {
    if (i == 0)
        return true;
    if (memo[i])
        return j[i];

    bool q = false;
    for (auto k = 0; k < i; ++k)
        q = q || (lookup(a, j, memo, k) && (a[k] >= i - k));
        
    memo[i] = true;
    j[i] = q;
    return j[i];
}

bool canJump(vector<int>& a) {
    int n = a.size();
    bool* j = new bool[n];
    bool* memo = new bool[n];
    // initialization
    for (int i = 1; i < n; ++i) {
        j[i] = false;
        memo[i] = false;
    }
    return lookup(a, j, memo, n - 1);
}
```

Of course, bottom up approach can be used

```c++
// O(n^2) bottom up approach
bool canJump_DP(vector<int>& a) {
    int n = a.size();
    bool* j = new bool[n];
    j[0] = true;
    for (int i = 1; i < n; ++i) {
        j[i] = false;
        for (int k = 0; k < i; ++k) {
            j[i] = j[i] || (j[k] && (a[k] >= i - k));
        }
    }
    return j[n - 1];
}
```



### Greedy 

More efficient way exist! 

If you think about this problem precisely, you can notice that there are many ways to get a solution.

In this example greedy choice property can be satisfied.

*2 greedy choce*

* backward: take the last element among being reachable!
* forward:  take the first element among being reachable! 

```c++
// backward
bool canJump_greedy(vector<int>& a) {
    int n = a.size();
    int last = n - 1;
    for (int i = n - 2; i >= 0; i--) {
        if (i + a[i] >= last)last = i;
    }
    return last <= 0;
}

// forward
bool canJump_greedy2(vector<int>& a) {
    int n = a.size();
    int maxj = a[0];
    for (int i = 0; i <= maxj; i++) {
        maxj = max(maxj, i + a[i]); // greedy choice 
        if (maxj >= n - 1) return true;
    }
    return false;
}
```



if you want to run this code, you can visit my [github](https://github.com/SUNGWOOKYOO/Algorithm/blob/master/src_Cplus/55_Jump.cpp). 

