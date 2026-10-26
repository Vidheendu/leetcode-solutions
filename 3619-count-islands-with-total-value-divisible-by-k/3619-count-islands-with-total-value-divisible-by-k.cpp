class Solution {
public:
    int countIslands(vector<vector<int>>& grid, int k) {
        int m = grid.size();
        int n = grid[0].size();
        int count = 0;

        vector<pair<int, int>> dirs = {
            {1, 0}, {-1, 0}, {0, 1}, {0, -1}
        };

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] > 0) {
                    long long sum = 0;
                    stack<pair<int, int>> st;
                    st.push({i, j});
                    sum = grid[i][j];
                    grid[i][j] = 0;

                    while (!st.empty()) {
                        auto [r, c] = st.top();
                        st.pop();

                        for (auto [dr, dc] : dirs) {
                            int nr = r + dr;
                            int nc = c + dc;

                            if (nr >= 0 && nr < m &&
                                nc >= 0 && nc < n &&
                                grid[nr][nc] > 0) {
                                sum += grid[nr][nc];
                                st.push({nr, nc});
                                grid[nr][nc] = 0;
                            }
                        }
                    }

                    if (sum % k == 0) {
                        count++;
                    }
                }
            }
        }

        return count;
    }
};