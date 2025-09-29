#include <bits/stdc++.h>
using namespace std;
#define int long long

class SegmentTree {
    int n;
    vector<int> tree, lazy;

public:
    SegmentTree(int size) {
        n = size;
        tree.resize(4 * n, 0);
        lazy.resize(4 * n, 0);
    }

    // Push lazy updates to children
    void push(int node, int start, int end) {
        if (lazy[node] != 0) {
            tree[node] += (end - start + 1) * lazy[node]; // apply lazy
            if (start != end) { // not a leaf
                lazy[2 * node + 1] += lazy[node];
                lazy[2 * node + 2] += lazy[node];
            }
            lazy[node] = 0;
        }
    }

    // Build tree from initial array
    void build(vector<int> &arr, int node, int start, int end) {
        if (start == end) {
            tree[node] = arr[start];
            return;
        }
        int mid = (start + end) / 2;
        build(arr, 2 * node + 1, start, mid);
        build(arr, 2 * node + 2, mid + 1, end);
        tree[node] = tree[2 * node + 1] + tree[2 * node + 2];
    }

    // Range update: add val to all elements in [l, r]
    void updateRange(int node, int start, int end, int l, int r, int val) {
        push(node, start, end); // apply pending updates

        if (r < start || end < l) return; // no overlap
        if (l <= start && end <= r) { // total overlap
            lazy[node] += val;
            push(node, start, end);
            return;
        }

        int mid = (start + end) / 2;
        updateRange(2 * node + 1, start, mid, l, r, val);
        updateRange(2 * node + 2, mid + 1, end, l, r, val);
        tree[node] = tree[2 * node + 1] + tree[2 * node + 2];
    }

    // Range query: sum of elements in [l, r]
    int queryRange(int node, int start, int end, int l, int r) {
        push(node, start, end); // apply pending updates

        if (r < start || end < l) return 0; // no overlap
        if (l <= start && end <= r) return tree[node]; // total overlap

        int mid = (start + end) / 2;
        int p1 = queryRange(2 * node + 1, start, mid, l, r);
        int p2 = queryRange(2 * node + 2, mid + 1, end, l, r);
        return p1 + p2;
    }
};
