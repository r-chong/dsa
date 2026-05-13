#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

// we put dfs up here as you need to write in order of dependency
// we're trying to find the size of the subtree
// why is cuts a reference? because it was passed to us
int dfs(vector<vector<int>> &graph, int node, int parent, int &cuts) {
    // we include parent if the graph is undirected (so can be bidirectional connection)
    // or else we'd recurse forever/TLE
    int size = 1;
    // the reason for this is that we're caclulating size of subtree, so this node counts towards that
    
    for (int nei : graph[node]) {
        if (nei == parent) {
            // prevent loop like said above
            continue;
        }
        
        // we check if should be cut (subtree is even)
        // if we're doing postorder dfs we get the size of the child before the current. so we know if the size is even, then cut.
        
        int child_size = dfs(graph, nei, node, cuts);
        
        if (child_size % 2 == 0) {
            cuts++;
        } else {
            // propagates up
            size += child_size;
        }
    }
    return size;
}

// Complete the evenForest function below.
int evenForest(int t_nodes, int t_edges, vector<int> t_from, vector<int> t_to) {
    // make sure to specify size of graph!! note that subtree size includes self
    vector<vector<int>> graph(t_nodes + 1);
    
    // undirected graph built from tree to and from
    // main difference is it's 2 1d vectors not 1 2d vector
    for (int i = 0; i < t_edges; i++) {
        int u = t_from[i];
        int v = t_to[i];
        
        // bidirectional as undirected
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    
    int cuts = 0;
    // generalization: we dont always cut
    // we can: merge, choose best option, update a global value like a diameter, validate (is balanced)
    // What does each subtree need to report upward?
    // What does the parent do with each child's report?
    
    // parent is -1 from root
    // isnt that gonna get the end of the graph?
    dfs(graph, 1, -1, cuts);
    
    return cuts;
}


int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string t_nodes_edges_temp;
    getline(cin, t_nodes_edges_temp);

    vector<string> t_nodes_edges = split(rtrim(t_nodes_edges_temp));

    int t_nodes = stoi(t_nodes_edges[0]);
    int t_edges = stoi(t_nodes_edges[1]);

    vector<int> t_from(t_edges);
    vector<int> t_to(t_edges);

    for (int i = 0; i < t_edges; i++) {
        string t_from_to_temp;
        getline(cin, t_from_to_temp);

        vector<string> t_from_to = split(rtrim(t_from_to_temp));

        int t_from_temp = stoi(t_from_to[0]);
        int t_to_temp = stoi(t_from_to[1]);

        t_from[i] = t_from_temp;
        t_to[i] = t_to_temp;
    }

    int res = evenForest(t_nodes, t_edges, t_from, t_to);

    fout << res << "\n";

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
