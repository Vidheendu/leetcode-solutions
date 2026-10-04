class Solution {
public:
    bool checkValidString(string s) {
        int low = 0;
        int high = 0;

        for (char c : s) {
            if (c == '(') {
                low++;
                high++;
            }
            else if (c == ')') {
                low--;
                high--;
            }
            else { // '*'
                low--;   // '*' acts as ')'
                high++;  // '*' acts as '('
            }

            // Even the maximum possible balance is negative
            if (high < 0)
                return false;

            // Balance cannot actually be negative
            low = max(low, 0);
        }

        // We need some possibility where balance is exactly 0
        return low == 0;
    }
};