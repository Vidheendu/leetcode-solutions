class Solution {
public:
    vector<string> removeInvalidParentheses(string s) {
        vector<string> ans;
        unordered_set<string> seen;

        int leftRemove = 0;
        int rightRemove = 0;

        
        for (char c : s) {
            if (c == '(') {
                leftRemove++;
            }
            else if (c == ')') {
                if (leftRemove > 0) {
                    leftRemove--;
                }
                else {
                    rightRemove++;
                }
            }
        }

        
        function<void(int, int, int, int, string)> backtrack =
            [&](int index, int left, int right, int balance, string current) {

                
                if (balance < 0)
                    return;

                
                if (index == s.length()) {
                    if (left == 0 && right == 0 && balance == 0) {
                        if (!seen.count(current)) {
                            seen.insert(current);
                            ans.push_back(current);
                        }
                    }
                    return;
                }

                char c = s[index];

                
                if (c == '(' && left > 0) {
                    backtrack(index + 1, left - 1, right,
                              balance, current);
                }

                
                if (c == ')' && right > 0) {
                    backtrack(index + 1, left, right - 1,
                              balance, current);
                }

                
                if (c == '(') {
                    backtrack(index + 1, left, right,
                              balance + 1, current + c);
                }
                else if (c == ')') {
                    backtrack(index + 1, left, right,
                              balance - 1, current + c);
                }
                else {
                    
                    backtrack(index + 1, left, right,
                              balance, current + c);
                }
            };

        backtrack(0, leftRemove, rightRemove, 0, "");

        return ans;
    }
};