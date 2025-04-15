#include <iostream>
#include <vector>
#include <set>

using namespace std;

struct Edge {
    int vertex;
    Edge * next;
};

void dfs(int vertex, vector<Edge*> const &edges, vector<bool>& visited) {
    visited[vertex] = true;

    Edge* current = edges[vertex];
    while (current != nullptr) {
        if (!visited[current->vertex]) {
            dfs(current->vertex, edges, visited);
        }
        current = current->next;
    }
}

int count_cc(Edge **edges, int vertices) {
    vector<bool> visited(vertices, false);
    int count = 0;
    
    set<int> adjVertices;
    //this is to check if the graph is directed
    for (int i = 0; i < vertices; i++) {
        Edge* current = edges[i];
        while (current != nullptr) {
            adjVertices.insert(current->vertex);
            current = current->next;
        }
    }
    //this is to check if the graph is directed
    for (int i = 0; i < vertices; i++) {
        Edge* current = edges[i];
        while (current != nullptr) {
            // if it doesn't find i in the set, it will return the end of the set.
            // this means if .find() is equal to .end(), i is not in the set.
            if (adjVertices.find(i) == adjVertices.end())
                return 0;
            current = current->next;
        }
    }

    for (int i = 0; i < vertices; i++) {
        if (!visited[i]) {
            dfs(i, vector<Edge*>(edges, edges + vertices), visited);
            count++;
        }
    }

    return count;
}

// int main() {
//     Edge e[] = {
//         {1,nullptr},
//     };

//     Edge * g[] = {
//         e+0,
//         nullptr
//     };

//     int num = count_cc(g, 2);
//     cout << "Number of connected components: " << num << endl;

//     assert(count_cc(g,2) == 0);
// }