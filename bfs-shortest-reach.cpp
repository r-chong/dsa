#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

/*
 * Complete the 'bfs' function below.
 *
 * The function is expected to return an INTEGER_ARRAY.
 * The function accepts following parameters:
 *  1. INTEGER n
 *  2. INTEGER m
 *  3. 2D_INTEGER_ARRAY edges
 *  4. INTEGER s
 */

vector<int> bfs(int n, int m, vector<vector<int>> edges, int s) {
    // turn edges into a graph. so adjacency list (unordered_map)
    // only finding from 1 node
    // array of distances from START to a,b,c etc
    
    vector<vector<int>> graph(n + 1);
    
    // populate the graph
    for (const vector<int>& edge : edges) {
        // for one of the edges
        
        int u = edge[0];
        int v = edge[1];
        
        // depending if undirected or directed, you add as a neighbour to just one or both respectively
        graph[u].push_back(v);
        // this is undirected, so
        graph[v].push_back(u);
    }
    
    // given graph[s]
    // have to find array of distances from s to each other.
    // for that key, it's the start of bfs
    // so then run bfs on that node. for each node added to neighbours at a level of depth
    // append to array (queue is sorted as well - how to do that?)
    // and take depth * 6
    // then at the end, loop through all nodes, if its not having a connection then assign -1
    
    // since bfs is done iteratively here
    // we can put all in this function
    vector<int> dist(n + 1, -1);
    queue<int> q;
    
    dist[s] = 0;
    q.push(s);
    
    while(!q.empty()) {
        int u = q.front();
        q.pop();
        
        // for all neighbours
        for (int v : graph[u]) {
            if (dist[v] == -1) {
                // if this is -1 we just visited for the first time. SO THIS IS THE SHORTEST PATH TO V
                dist[v] = dist[u] + 6;
                // dist[u] is the parent neighbour and the parent neighbour starts at dist 0
                q.push(v);
            }
        }
    }
    
    vector<int> ans;
    // this part serves as the answer generator
    // so all pairs
    // i = 1 because HackerRank says nodes are numbered from 1 to n, not 0 to n - 1
    for (int i = 1; i <= n; i++) {
        if (i != s) {
            ans.push_back(dist[i]);
        }
    }
    
    return ans;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string q_temp;
    getline(cin, q_temp);

    int q = stoi(ltrim(rtrim(q_temp)));

    for (int q_itr = 0; q_itr < q; q_itr++) {
        string first_multiple_input_temp;
        getline(cin, first_multiple_input_temp);

        vector<string> first_multiple_input = split(rtrim(first_multiple_input_temp));

        int n = stoi(first_multiple_input[0]);

        int m = stoi(first_multiple_input[1]);

        vector<vector<int>> edges(m);

        for (int i = 0; i < m; i++) {
            edges[i].resize(2);

            string edges_row_temp_temp;
            getline(cin, edges_row_temp_temp);

            vector<string> edges_row_temp = split(rtrim(edges_row_temp_temp));

            for (int j = 0; j < 2; j++) {
                int edges_row_item = stoi(edges_row_temp[j]);

                edges[i][j] = edges_row_item;
            }
        }

        string s_temp;
        getline(cin, s_temp);

        int s = stoi(ltrim(rtrim(s_temp)));

        vector<int> result = bfs(n, m, edges, s);

        for (size_t i = 0; i < result.size(); i++) {
            fout << result[i];

            if (i != result.size() - 1) {
                fout << " ";
            }
        }

        fout << "\n";
    }

    fout.close();

    return 0;
}

string ltrim(const string &str) {
    string s(str);

    s.erase(
        s.begin(),
        find_if(s.begin(), s.end(), not1(ptr_fun<int, int>(isspace)))
    );

    return s;
}

string rtrim(const string &str) {
    string s(str);

    s.erase(
        find_if(s.rbegin(), s.rend(), not1(ptr_fun<int, int>(isspace))).base(),
        s.end()
    );

    return s;
}

vector<string> split(const string &str) {
    vector<string> tokens;

    string::size_type start = 0;
    string::size_type end = 0;

    while ((end = str.find(" ", start)) != string::npos) {
        tokens.push_back(str.substr(start, end - start));

        start = end + 1;
    }

    tokens.push_back(str.substr(start));

    return tokens;
}
