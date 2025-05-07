#include <iostream>
#include <vector>
#include <queue>
#include <omp.h>

using namespace std;

void parallelBFS(const vector<vector<int>>& adj, int start) {
    int n = adj.size();
    vector<bool> visited(n, false);
    queue<int> q;

    visited[start] = true;
    q.push(start);

    while (!q.empty()) {
        int level_size = q.size();
        vector<int> current_level;

        for (int i = 0; i < level_size; ++i) {
            int u = q.front();
            q.pop();
            current_level.push_back(u);
        }

        #pragma omp parallel for
        for (int i = 0; i < current_level.size(); ++i) {
            int u = current_level[i];
            cout << u << " "; 

            for (int v : adj[u]) {
                
                #pragma omp critical
                {
                    if (!visited[v]) {
                        visited[v] = true;
                        q.push(v);
                    }
                }
            }
        }
    }

    cout << endl;
}

int main() {
    int V = 6;
    vector<vector<int>> adj(V);

    adj[0] = {1, 2};
    adj[1] = {0, 3, 4};
    adj[2] = {0, 4};
    adj[3] = {1, 5};
    adj[4] = {1, 2, 5};
    adj[5] = {3, 4};

    cout << "BFS traversal starting from node 0:\n";
    parallelBFS(adj, 0);

    return 0;
}
