// Naive sorted container: array iterative
int binarySearch(int target, vector<int> &arr) {
    int lo = 0;
    int hi = arr.size() - 1;

    // note <= or else we miss last element
    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;

        if (arr[mid] == target) {
            return mid;
        } else if (arr[mid] < target ) {
            lo = mid + 1;
        } else {
            hi = mid - 1;
        }
    }
    
    return -1;
}

// Naive sorted container: array recursive
int binarySearch(int lo, int hi, int target, vector<int> &arr) {
    // note this base case or else we infinitely loop if cannot find
    if (lo > hi) return -1;

    int mid = lo + (hi - lo) / 2;

    if (arr[mid] == target) {
        return mid;
    } else if (arr[mid] < target ) {
        return binarySearch(mid + 1, hi, target, arr);
    } else {
        return binarySearch(lo, mid - 1, target, arr);
    }
}

// Naive sorted container: binary search tree recursive
TreeNode *n binarySearch(int target, TreeNode *n) {
    if (!n) {
        return nullptr;
    } else if (n->val == target) {
        return n;
    } else if (n->val < target) {
        return binarySearch(target, n->right);
    } else {
        return binarySearch(target, n->left);
    }
}

// Naive sorted container: binary search tree iterative
TreeNode *n binarySearch(int target, TreeNode *n) {
    while (n) {
        if (n->val == target) {
            return n;
        } else if (n->val < target) {
            n = n->right;
        } else {
            n = n->left;
        }
    }

    return nullptr;
}

// Accessor
template <typename Get, typename T>
int binarySearch(int lo, int hi, Get get, const T& target) {
    int ans = hi + 1;

    // I don't fully understand the stop condition here
    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        if (get(mid) >= target) {
            ans = mid;
            hi = mid - 1;
        } else {
            lo = mid + 1;
        }
    }
    return ans;
}

// Predicate invariant
template <typename Pred> int binarySearch(int lo, int hi, Pred ok) {
    // search range: [lo, hi)
    // returns first x where ok(x) is true
    // assumes ok is monotonic; once you have the first true, it's all true after that

    while (lo < hi) {
        // prevent overflow: if |hi| is less than |lo|, this will give a negative. so we add lo such that we're always between hi, lo
        int mid = lo + (hi - lo) / 2;

        if (ok(mid)) {
            hi = mid;
        } else {
            lo = mid + 1;
        }
    }

    return lo;
}

// Iterator (STL)
template <typename It, typename T, typename Comp = std::less<>>
It lower_bound(It first, It last, const T& value, Comp comp = {}) {
    while (first < last) {
        It mid = first + (last - first) / 2;
        if (comp(*mid, value)) {
            first = mid + 1;
        } else {
            last = mid;
        }
    }
    return first;
}
