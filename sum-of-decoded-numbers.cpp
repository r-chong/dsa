class Solution {
    const long long MOD = 1e9 + 7;
public:
    int sumDecoded(vector<long long>& nums) {
        // digit length can be 15 digits long, width about half (9) so int
        int width = 0;
        long long d = 0;
        long long ans = 0;
        
        for (int i = 0; i < nums.size(); i++) {
            width = nums[i] % 10;
            d = floor(nums[i] / 10);

            string str = to_string(d);
            string x_str = "";
            string y_str = "";

            for (int j = 0; j < width; j++) {
                x_str += str[j];
            }
            for (int j = width; j < str.size(); j++) {
                y_str += str[j];
            }

            long long x = stoll(x_str);
            long long y = stoll(y_str);

            long long decoded = 1;

            while (y > 0) {
                if (y & 1) {
                    decoded = (decoded * x) % MOD;
                }

                x = (x * x) % MOD;
                y >>= 1;
            }
            
            ans = (ans + decoded) % MOD;
        }

        return ans;
    }
};©leetcode