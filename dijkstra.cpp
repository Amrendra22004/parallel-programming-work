#include <iostream>
#include <vector>
#include <climits>
#include <omp.h>

using namespace std;

const int INF = INT_MAX;
const int V = 6;  

void dijkstra(const vector<vector<int>>& graph, int src) {
    vector<int> dist(V, INF);
    vector<bool> visited(V, false);
    dist[src] = 0;

    for (int count = 0; count < V - 1; ++count) {
        int u = -1;
        int min_dist = INF;

        for (int i = 0; i < V; ++i) {
            if (!visited[i] && dist[i] < min_dist) {
                min_dist = dist[i];
                u = i;
            }
        }

        if (u == -1) break;  
        visited[u] = true;

        #pragma omp parallel for
        for (int v = 0; v < V; ++v) {
            if (!visited[v] && graph[u][v] != 0 && dist[u] != INF) {
                int new_dist = dist[u] + graph[u][v];
                #pragma omp critical
                {
                    if (new_dist < dist[v]) {
                        dist[v] = new_dist;
                    }
                }
            }
        }
    }


    cout << "Vertex\tDistance from Source " << src << endl;
    for (int i = 0; i < V; ++i) {
        cout << i << "\t" << dist[i] << endl;
    }
}

int main() {
    vector<vector<int>> graph = {
        {0,  2,  0,  1,  0,  0},
        {2,  0,  3,  2,  0,  0},
        {0,  3,  0,  0,  0,  1},
        {1,  2,  0,  0,  1,  0},
        {0,  0,  0,  1,  0,  2},
        {0,  0,  1,  0,  2,  0}
    };

    cout << "\n";
    dijkstra(graph, 0);

    return 0;
}
