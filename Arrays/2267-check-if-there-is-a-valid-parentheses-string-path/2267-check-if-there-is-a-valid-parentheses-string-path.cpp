class Solution {
public:
    bool hasValidPath(vector<vector<char>>& grid) {
        int m = grid.size();
        int n = grid[0].size();

        // A valid parentheses string must have even length
        if ((m + n - 1) % 2 != 0)
            return false;

        // dp[i][j] = set of possible balances at (i,j)
        vector<vector<unordered_set<int>>> dp(m, vector<unordered_set<int>>(n));

        // Starting cell
        if (grid[0][0] == ')')
            return false;

        dp[0][0].insert(1);

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {

                if (i == 0 && j == 0)
                    continue;

                int change = (grid[i][j] == '(') ? 1 : -1;

                // Come from top
                if (i > 0) {
                    for (int balance : dp[i - 1][j]) {
                        int newBalance = balance + change;

                        if (newBalance >= 0)
                            dp[i][j].insert(newBalance);
                    }
                }

                // Come from left
                if (j > 0) {
                    for (int balance : dp[i][j - 1]) {
                        int newBalance = balance + change;

                        if (newBalance >= 0)
                            dp[i][j].insert(newBalance);
                    }
                }
            }
        }

        // We need balance = 0 at the end
        return dp[m - 1][n - 1].count(0);
    }
};