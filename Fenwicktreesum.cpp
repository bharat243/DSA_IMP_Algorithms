#include <bits/stdc++.h>
using namespace std;

struct Fenwick {
    int n;
    vector<long long> bit; 

    Fenwick(int n) {
        this->n = n;
        bit.assign(n + 1, 0);
    }

    // Add 'val' at index idx (0-based index)
    void update(int idx, long long val) {
        idx++; // convert to 1-based
        while (idx <= n) {
            bit[idx] += val;
            idx += idx & -idx; // move to parent
        }
    }

    // Prefix sum from 0 to idx (0-based)
    long long query(int idx) {
        idx++; // convert to 1-based
        long long sum = 0;
        while (idx > 0) {
            sum += bit[idx];
            idx -= idx & -idx; // move to parent
        }
        return sum;
    }

    // Range sum [l, r] inclusive
    long long rangeQuery(int l, int r) {
        return query(r) - query(l - 1);
    }
};
