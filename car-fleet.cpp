class Solution {
public:
    // highway method: no stack or pairs or sorting
    int carFleet(int target, vector<int>& position, vector<int>& speed) {
        vector<double> road(target, -1);
        // we create a fixed array the size of the target. then we put an ETA at each of the original positions
        // road[position[i]] is going to either have an empty value or an ETA.
        // then we walk the road backwards

        int n = position.size();
        for (int i = 0; i < n; i++) {
            double eta = (double)(target - position[i]) / speed[i];
            road[position[i]] = eta;
        }

        // a car can only go <= the slowest speed of the cars in front of it (slowest_ahead)
        // if a car is faster than slowest_ahead, then its speed is overwritten by slowest_ahead
        // if a car is slower than slowest_ahead, then it's creating its own bottleneck separately aka new fleet
        int fleets = 0;
        double slowest_ahead = -1.0;
        for (int t = target - 1; t >= 0; t--) {
            if (road[t] != -1) {
                if (road[t] > slowest_ahead) {
                    slowest_ahead = road[t];
                    fleets++;
                } else {
                    road[t] = slowest_ahead;
                }
            }
        }

        return fleets;
    }
};
// divergences:
// - edge case - even though the frontmost card would bottleneck the one behind it, it actually hits the target first
// - integer division vs double math. see line 11