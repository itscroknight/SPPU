#include <iostream>
#include <vector>
#include <queue>
#include <omp.h>
using namespace std;

void parallelBFS(vector<vector<int>>& graph, int start) {
    int n = graph.size();
    vector<bool> visited(n, false);
    queue<int> q;

    visited[start] = true;
    q.push(start);

    while (!q.empty()) {
        int size = q.size();

        #pragma omp parallel for
        for (int i = 0; i < size; i++) {
            int current;

            #pragma omp critical
            {
                if (!q.empty()) {
                    current = q.front();
                    q.pop();
                    cout << current << " ";
                }
            }

            for (int neighbor : graph[current]) {
                #pragma omp critical
                {
                    if (!visited[neighbor]) {
                        visited[neighbor] = true;
                        q.push(neighbor);
                    }
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

    cout << "Parallel BFS traversal: ";
    parallelBFS(graph, 0);

    return 0;
}
