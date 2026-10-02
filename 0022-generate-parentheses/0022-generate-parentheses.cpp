class Solution {
public:
    vector<string> generateParenthesis(int n) {
        vector<string> ans;

        function<void(string, int, int)> backtrack =
            [&](string current, int open, int close) {

                // We have used all brackets
                if (current.length() == 2 * n) {
                    ans.push_back(current);
                    return;
                }

                // Add '(' if available
                if (open < n) {
                    backtrack(current + '(', open + 1, close);
                }

                // Add ')' only when there is an unmatched '('
                if (close < open) {
                    backtrack(current + ')', open, close + 1);
                }
            };

        backtrack("", 0, 0);

        return ans;
    }
};