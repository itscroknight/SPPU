#include <iostream>
#include <vector>
#include <omp.h>
using namespace std;

void parallelDFS(vector<vector<int>>& graph, int node, vector<bool>& visited) {
    visited[node] = true;
    cout << node << " ";

    #pragma omp parallel for
    for (int i = 0; i < graph[node].size(); i++) {
        int neighbor = graph[node][i];
        if (!visited[neighbor]) {
            #pragma omp critical
            {
                if (!visited[neighbor]) {
                    parallelDFS(graph, neighbor, visited);
                }
            }
        }
    }
}

int main() {
    int n = 7; // Number of nodes
    vector<vector<int>> graph(n);

    graph[0] = {1, 2};
    graph[1] = {3, 4};
    graph[2] = {5, 6};

    vector<bool> visited(n, false);

    cout << "Parallel DFS traversal: ";
    parallelDFS(graph, 0, visited);

    return 0;
}
