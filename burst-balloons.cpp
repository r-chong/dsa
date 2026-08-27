class Solution {
    vector<vector<int>> memo;

    int coinsAt(int sum, vector<int>& balloons) {
        if (balloons.empty()) return sum;

        vector<int> temp = balloons;

        int maxB = 0;
        for (int i = 0; i < balloons.size(); i++) {
            int left = (i > 0) ? balloons[i - 1] : 1;
            int right = (i < balloons.size() - 1) ? balloons[i + 1] : 1;

            int calc = left * balloons[i] * right;
            temp.erase(temp.begin() + i);

            maxB = max(maxB, coinsAt(sum + calc, temp));

            // backtrack
            temp = balloons;
        }

        return maxB;
    }
public:
    int maxCoins(vector<int>& nums) {
        vector<int> balloons = nums;

        return coinsAt(0, balloons);
    }
};
// divergences:
// - erase syntax -specifically use of iterators
// - emplace syntax - there is no emplace front
// - was adding 1 to ends but that means its actually a new balloon. can just use variables
// - was double counting by adding sum when in reality the final coin amount should just be returned plainly (we already do sum + calc on recursion call)

// memoized topdown
class Solution {
    vector<vector<int>> memo;

    int fix(int left, int right, vector<int>& nums) {
        // fix either 1, 5 as last
        // within the interval still, find optimal for left and right interval (left to k, k to right)
        // then add score for the current
        if (left > right) return 0;
        if (memo[left][right] != -1) return memo[left][right];

        int score = 0;
        for (int k = left; k <= right; k++) {
            int l = fix(left, k - 1, nums);
            int r = fix(k + 1, right, nums);

            int lv = (left > 0) ? nums[left - 1] : 1;
            int rv = (right < nums.size() - 1) ? nums[right + 1] : 1;

            int popK = lv * nums[k] * rv;

            score = max(score, l + r + popK);
        }
        return memo[left][right] = score;
    }
public:
    int maxCoins(vector<int>& nums) {
        // each can be the last node
        memo = vector<vector<int>>(nums.size(), vector<int>(nums.size(), -1));

        return fix(0, nums.size() - 1, nums);
    }
};