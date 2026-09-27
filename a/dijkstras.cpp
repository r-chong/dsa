// leetcode: 1334. Find the City With the Smallest Number of Neighbors at a Threshold Distance

class Solution {
public:
    int findTheCity(int n, vector<vector<int>>& edges, int distanceThreshold) {
        vector<vector<pair<int,int>>> graph(n);

        for (auto& e : edges) {
            int u = e[0];
            int v = e[1];
            int w = e[2];

            graph[u].push_back({v, w});
            graph[v].push_back({u, w}); // undirected
        }

        // min heap
        priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;

        int answer = -1;
        int minCount = INT_MAX;
        
        // no start so run dijkstras from each city
        // dist contains the shortest distance from that start(assumed) to every city (index) which is why we reset for each start
        for (int start = 0; start < n; start++) {
            vector<int> dist(n, INT_MAX);

            pq.push({0, start});
            dist[start] = 0;

            while (!pq.empty()) {
                auto [currDist, curr] = pq.top();
                pq.pop();

                if (currDist > dist[curr]) continue;

                for (auto [next, weight] : graph[curr]) {
                    // we can't mark as visited-never-come-here-again as nodes have weighting now and it may not be exhausted yet
                    if (currDist + weight < dist[next]) {
                        dist[next] = currDist + weight;
                        pq.push({dist[next], next});
                    }
                }
            }

            int count = 0;
        
            // process our findings
            for (int city = 0; city < n; city++) {
                if (city != start && dist[city] <= distanceThreshold) {
                    count++;
                }
            }

            if (count <= minCount) {
                minCount = count;
                answer = start;
            }
        }
        
        return answer;
    }
};
// learning dijkstra's:
// - no visited set needed