class Solution {
public:
    int sumCounts(vector<int>& nums) {
        const long long MOD = 1e9 + 7;
        int n = nums.size();

        vector<long long> sum(4 * n, 0);
        vector<long long> sq(4 * n, 0);
        vector<long long> lazy(4 * n, 0);

        auto apply = [&](int node, int l, int r, long long v) {
            long long len = r - l + 1;

            sq[node] = (sq[node] + 2 * v % MOD * sum[node] % MOD
                        + v * v % MOD * len % MOD) % MOD;

            sum[node] = (sum[node] + v * len) % MOD;
            lazy[node] = (lazy[node] + v) % MOD;
        };

        function<void(int,int,int)> push = [&](int node, int l, int r) {
            if (lazy[node] == 0 || l == r) return;

            int mid = (l + r) / 2;
            apply(node * 2, l, mid, lazy[node]);
            apply(node * 2 + 1, mid + 1, r, lazy[node]);
            lazy[node] = 0;
        };

        function<void(int,int,int,int,int,long long)> update =
            [&](int node, int l, int r, int ql, int qr, long long v) {
                if (ql > r || qr < l) return;

                if (ql <= l && r <= qr) {
                    apply(node, l, r, v);
                    return;
                }

                push(node, l, r);
                int mid = (l + r) / 2;

                update(node * 2, l, mid, ql, qr, v);
                update(node * 2 + 1, mid + 1, r, ql, qr, v);

                sum[node] = (sum[node * 2] + sum[node * 2 + 1]) % MOD;
                sq[node] = (sq[node * 2] + sq[node * 2 + 1]) % MOD;
            };

        vector<int> last(100001, -1);
        long long ans = 0;

        for (int i = 0; i < n; i++) {
            int prev = last[nums[i]];

           
            update(1, 0, n - 1, prev + 1, i, 1);

            ans = (ans + sq[1]) % MOD;
            last[nums[i]] = i;
        }

        return ans;
    }
};