Yes—**worst case**, this implementation can be described as:

[
O(n^2 2^n)
]

But it helps to separate where each factor comes from.

Your recursion creates `2^n` leaves because each element has two choices: exclude or include.

At every leaf:

```cpp
uniqueSubsets.insert(current);
```

Suppose the set currently contains (M) subsets.

* A `set` insertion performs `O(log M)` vector comparisons.
* (M) can approach (2^n), so:

[
\log M = \log(2^n) = n
]

* Comparing two `vector<int>` objects can take `O(n)` in the worst case.

Therefore, each insertion can cost:

[
O(n \cdot n) = O(n^2)
]

Across `2^n` leaves:

[
O(n^2 2^n)
]

There is also copying `current` into the set, which costs `O(n)`, but the `O(n^2)` set-comparison cost dominates it.

That is a conservative worst-case analysis. In practice, vector comparisons often terminate before examining all `n` elements, and duplicates may reduce the number of unique entries.

Why sorting is needed:

Without sorting, two index choices representing the same mathematical subset can produce vectors in different orders.

For example:

```cpp
nums = {2, 1, 2}
```

You could generate:

```cpp
{2, 1}  // choose indices 0 and 1
{1, 2}  // choose indices 1 and 2
```

Mathematically, both represent the subset containing `1` and `2`, but `set<vector<int>>` considers them different because vector order matters.

After sorting:

```cpp
nums = {1, 2, 2}
```

Every generated subset is in sorted order, so equivalent subsets have the same representation:

```cpp
{1, 2}
{1, 2}
```

The set can now remove the duplicate.

So your approach is correct, but the set is doing expensive cleanup after generating duplicate branches. The intended solution avoids generating those duplicate branches in the first place, bringing the usual bound down to approximately:

[
O(n2^n)
]
