struct SparseTable {
    int n, K;
    vector<vector<int>> st;
    vector<int> logTable;

    SparseTable(const vector<int>& arr) {
        n = arr.size();
        K = log2(n) + 1;

        // Precompute logs for queries
        logTable.resize(n + 1);
        logTable[1] = 0;
        for (int i = 2; i <= n; i++)
            logTable[i] = logTable[i / 2] + 1;

        // Initialize Sparse Table
        st.assign(n, vector<int>(K));
        for (int i = 0; i < n; i++)
            st[i][0] = arr[i];

        // Build Sparse Table
        for (int j = 1; j < K; j++) {
            for (int i = 0; i + (1 << j) <= n; i++) {
                st[i][j] = min(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
            }
        }
    }

    // Query minimum on range [L, R]
    int query(int L, int R) {
        int j = logTable[R - L + 1];
        return min(st[L][j], st[R - (1 << j) + 1][j]);
    }
};
// sparse table use for Idempodent functions like min,max,__gcd,lcm, bitwise and , bitwiae or
// no point update 
// preprocessing O(nlogn)
// query timr o(1)
