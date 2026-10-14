class Solution {
public:
    string maxSumOfSquares(int num, int sum) {
        if (sum > 9 * num)
            return "";

        string ans = "";

        while (sum >= 9) {
            ans += '9';
            sum -= 9;
            num--;
        }

        if (sum > 0) {
            ans += char('0' + sum);
            num--;
        }

        while (num > 0) {
            ans += '0';
            num--;
        }

        return ans;
    }
};