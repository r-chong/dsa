class Solution {
    int dp(int l, int r, vector<int>& nums) {
        if (l > r) return 0;

        // my optimal move is the minuend. My opponent's optimal move is the subtrahend. Return/memoize the difference.
        return max(nums[l] - dp(l + 1, r, nums), nums[r] - dp(l, r - 1, nums));
    }
public:
    bool predictTheWinner(vector<int>& nums) {
        return dp(0, nums.size() - 1, nums) >= 0;
    }
};
// divergences:
// - thought minmax was more complicated than it was
// - forgot the >= for entrypoint return val