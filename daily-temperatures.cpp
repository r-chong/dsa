class Solution {
public:
    // TC: O(n), SC: O(n)
    vector<int> dailyTemperatures(vector<int>& temperatures) {
        int n = temperatures.size();
        vector<int> answer(n, 0);

        // PAST UNRESOLVED DAYS
        vector<int> stck;

        for (int i = 0; i < n; i++) {
            // Resolve past unresolved days whose next warmer day is today
            while (!stck.empty() && temperatures[i] > temperatures[stck.back()]) {
                answer[stck.back()] = i - stck.back();
                stck.pop_back();
            }
            stck.push_back(i);
        }
        return answer;
    }

    // TC: O(n^2), SC: O(1) auxilary, O(n) including output
    // since answer is required, it's technically not extra
    vector<int> dailyTemperaturesBruteForce(vector<int>& temperatures) {
        int n = temperatures.size();
        vector<int> answer(n, 0);

        for (int i = 0; i < n; i++) {	
	     int j = i;
            while (j < n) {
                if (temperatures[j] > temperatures[i]) {
                    answer[i] = j - i;
                    break;
                }
                j++;
            }
        }

        return answer;
    }
};
// divergences:
// - thought that the inside loop was caching forward (which was unintuitive). Instead, we were caching previously-seen items which is intuitive.
// - was unsure to use vector or stack. For leetcode, vector is better. Syntax is push_back, pop_back, back()
// - thought that the condition (!stck.empty() && temperatures[i] > temperatures[stck.back()]) was an `if` not a `while`
// - put a continue inside the conditional
// - originally pushed the first value and indexed from 1 as I thought the condition would never start