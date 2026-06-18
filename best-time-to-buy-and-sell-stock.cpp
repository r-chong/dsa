class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int left = 0;
        int right = 1;
        int max_profit = 0;

        while (right < prices.size()) { 
            if (prices[right] > prices[left]) {
                max_profit = max(max_profit, prices[right] - prices[left]);
            } else {
                left = right;
            }
            right++;
        }

        return max_profit;
    }
};

// divergences:
// no need to keep track of indices
// also no need to keep track of past left,right as that has already been processed
// 2026-06-18
// took a bit of time thinking about how to update left, and which of {left, right} increments every step
