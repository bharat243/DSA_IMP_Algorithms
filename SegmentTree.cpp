#include <bits/stdc++.h>
using namespace std;
#define int long long

struct SegmentTree {
    int n;
    vector<int> tree;

    // Initialize with size
    SegmentTree(int size) {
        n = size;
        tree.assign(4 * n, 0); // segment tree size ~ 4*n
    }

    // Build tree from initial array
    void build(vector<int> &arr, int node, int start, int end) {
        if (start == end) {
            tree[node] = arr[start];
        } else {
            int mid = (start + end) / 2;
            build(arr, 2 * node, start, mid);
            build(arr, 2 * node + 1, mid + 1, end);
            tree[node] = tree[2 * node] + tree[2 * node + 1];
        }
    }

    // Point update: set arr[idx] = val
    void update(int node, int start, int end, int idx, int val) {
        if (start == end) {
            tree[node] = val;
        } else {
            int mid = (start + end) / 2;
            if (idx <= mid)
                update(2 * node, start, mid, idx, val);
            else
                update(2 * node + 1, mid + 1, end, idx, val);
            tree[node] = tree[2 * node] + tree[2 * node + 1];
        }
    }

    // Range sum query [l, r]
    int query(int node, int start, int end, int l, int r) {
        if (r < start || end < l) return 0;      // no overlap
        if (l <= start && end <= r) return tree[node]; // total overlap
        int mid = (start + end) / 2;
        int p1 = query(2 * node, start, mid, l, r);
        int p2 = query(2 * node + 1, mid + 1, end, l, r);
        return p1 + p2;
    }
};
