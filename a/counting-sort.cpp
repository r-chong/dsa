vector<int> countingSort(vector<int>& nums) {
    if (nums.empty()) return {};

    int minVal = nums[0];
    int maxVal = nums[0];

    // find extrema
    for (int x : nums) {
        minVal = min(minVal, x);
        maxVal = max(maxVal, x);
    }

    int range = maxVal - minVal + 1;
    vector<int> count(range, 0);

    // count frequency of each number
    for (int x : nums) {
        count[x - minVal]++;
    }

    // make a new array from min to max value
    vector<int> sorted;
    sorted.reserve(nums.size());

    // push value to array as many times as it appeared
    for (int i = 0; i < range; i++) {
        int value = i + minVal;
        while (count[i] > 0) {
            sorted.push_back(value);
            count[i]--;
        }
    }

    return sorted;
}