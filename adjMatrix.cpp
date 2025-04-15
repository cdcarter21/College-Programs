#include <iostream>
#include <vector>

using namespace std;

void dfs(int vertex, bool* edges, int vertices, vector<bool>& visited) {
    visited[vertex] = true;

    for (int i = 0; i < vertices; i++) {
        if (edges[vertex * vertices + i] && !visited[i]) {
            dfs(i, edges, vertices, visited);
        }
    }
}

int count_cc(bool *edge, int vertices) {
    //check if graph is directed
    for (int i = 0; i < vertices; i++) {
        for (int j=0; j<vertices; j++) {
            if (edge[i * vertices + j] != edge[j * vertices + i])
                return 0; 
        }
    }
    
    vector<bool> visited(vertices, false);
    int count = 0;

    for (int i = 0; i < vertices; i++) {
        if (!visited[i]) {
            dfs(i, edge, vertices, visited);
            count++;
        }
    }
    
    return count;
}
