// snippet of logic when I got confused on permutations
// maybe worth analyzing later

i is index
for (int i = 0; i < nums.size(); i++) {
    if (current[i] != -11) continue;

    // j is actual value
    for (int j = 0; j < nums.size(); j++) {
        if (used.contains(nums[j])) continue;

        current[i] = nums[j];
        used.insert(nums[j]);

        for (int x : current) {
            if (x == -11) {
                cout << "[ ]" << ", ";
            }   

            cout << "[" << x << "]" << ", ";
        }
        cout << endl;

        backtrack(choicesRemaining - 1, current, used, nums, res);
        used.erase(nums[j]);
        current[i] = -11;
    }
}