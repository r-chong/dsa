#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

/*
 * Complete the 'journeyToMoon' function below.
 *
 * The function is expected to return an INTEGER. I HAD TO EDIT IT TO RETURN LONG TO PASS HACKERRANK'S OWN TESTCASES
 * The function accepts following parameters:
 *  1. INTEGER n
 *  2. 2D_INTEGER_ARRAY astronaut
 */

long journeyToMoon(int n, vector<vector<int>> astronaut) {
    // 1 & 2 are same country
    // 2 & 3 are same country
    // thus 1 & 2 & 3 are same country
    
    // not 1-indexed
    // graph represents:
    // 0 : []
    // 1 : [2, 3]
    // 2 : [1, 3] // however we already counted this country.
    // 3 : [1, 2]
    vector<vector<int>> graph(n);

    // adjacency list/graph out of pairs
    for(const vector<int> &pair : astronaut) {
        int first = pair[0];
        int second = pair[1];
        
        graph[first].push_back(second);
        graph[second].push_back(first);
    }
    
    // separate into countries. i think this is connected components; all astronauts in the same country have bidirectional links to each other
    vector<int>visited(n, false);
    vector<int>countrySizes;
    
    // outer loop over bfs
    // count country sizes
    for (int a = 0; a < n; a++) {
        if (visited[a]) {
            // skip counting size of this astronaut's country because we already counted
            continue;
        }
        
        // INIT BFS - NEW COUNTRY FOR THIS ASTRONAUT
        queue<int> q;
        q.push(a);
        visited[a] = true;
        
        int size = 0;
        
        // ALL ASTRONAUTS IN COUNTRY (IF NOT VISITED THEM ALREADY)
        while(!q.empty()) {
            // ALWAYS REMEMBER QUEUE FRONT!
            int curr = q.front();
            q.pop();
                
            for (int nei : graph[curr]) {
                if (!visited[nei]) {
                    q.push(nei);
                    visited[nei] = true;
                }
            }
            
            // size increases per astronaut
            // we already know they're valid
            // should process here not in the !visited
            size++;   
        }
        countrySizes.push_back(size);
    }
    
    long long res = 0;
    long long prev = 0;
    
    for (long long size : countrySizes) {
        // note that we are trying to find every country i * country j
        // but this is optimized O(k = n + p)
        // this is still abstract to me, how we get here 
        res += size * prev;
        prev += size;
    }
    
    return res;
}
    
int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string first_multiple_input_temp;
    getline(cin, first_multiple_input_temp);

    vector<string> first_multiple_input = split(rtrim(first_multiple_input_temp));

    int n = stoi(first_multiple_input[0]);

    int p = stoi(first_multiple_input[1]);

    vector<vector<int>> astronaut(p);

    for (int i = 0; i < p; i++) {
        astronaut[i].resize(2);

        string astronaut_row_temp_temp;
        getline(cin, astronaut_row_temp_temp);

        vector<string> astronaut_row_temp = split(rtrim(astronaut_row_temp_temp));

        for (int j = 0; j < 2; j++) {
            int astronaut_row_item = stoi(astronaut_row_temp[j]);

            astronaut[i][j] = astronaut_row_item;
        }
    }

    long result = journeyToMoon(n, astronaut);

    fout << result << "\n";

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
