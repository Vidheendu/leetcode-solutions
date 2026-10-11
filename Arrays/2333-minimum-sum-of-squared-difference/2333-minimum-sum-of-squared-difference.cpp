
class Solution {
public:
    long long minSumSquareDiff(vector<int>& nums1, vector<int>& nums2, int k1, int k2) {
        long long k = (long long)k1 + k2;
        vector<int> diff(nums1.size());

        int mx = 0;
        long long total = 0;

        for (int i = 0; i < nums1.size(); i++) {
            diff[i] = abs(nums1[i] - nums2[i]);
            mx = max(mx, diff[i]);
            total += diff[i];
        }

        if (k >= total) return 0;

       
        int left = 0, right = mx;

        while (left < right) {
            int mid = left + (right - left) / 2;
            long long needed = 0;

            for (int d : diff) {
                if (d > mid)
                    needed += d - mid;
            }

            if (needed <= k)
                right = mid;
            else
                left = mid + 1;
        }

        int limit = left;
        long long ans = 0;
        long long remaining = k;

      
        for (int d : diff) {
            if (d > limit) {
                remaining -= d - limit;
                d = limit;
            }
            ans += 1LL * d * d;
        }

        
        if (limit > 0) {
            long long count = 0;

            for (int d : diff) {
                if (d == limit)
                    count++;
            }

            long long reduce = min(remaining, count);
            ans -= reduce * (2LL * limit - 1);
        }

        return ans;
    }
};