/* 
L9.1 Implement the Depth First Search (DFS) graph traversal algorithm.
1. I am using nodes as 1 based indexing eg. if number of vertices = 3, vertices will be 1,2,3
2. I am using undirected graph
3. Also graph can have more than one connected components, still algorithm will work 
*/

#include <iostream>
#include <vector>
using namespace std;

class Graph {
    public:
        Graph(const int n)
            : vertices{n}, graph{new vector<int>[n + 1]}
        {}
        
        bool insert(const int, const int);
        void dfs(int,bool*);
    private:
        vector<int> *graph;
        int vertices;
};

bool Graph::insert(const int u, const int v) {
    if (u < 1 || v < 1 || u > vertices || v > vertices) {
        cout << "[Warning] Edge out of bound";
        return false;
    }
    // Since undirected graph i will make an edge from u->v as well as
    // from v->u
    graph[u].push_back(v);
    graph[v].push_back(u);
    return true;
}

void Graph::dfs(int node, bool* visited) {
    visited[node] = true;
    cout << node << " ";
    for(auto it : graph[node]) {
        if(!visited[it]) {
            dfs(it,visited);
        }
    }
}

int main() {
    int vertices, edges;
    cout << "Enter number of nodes in graph : ";
    cin >> vertices;
    cout << "Enter number of edges : ";
    cin >> edges;

    Graph g(vertices);
    cout << "!! Enter edges (u,v) !! " << endl;
    for(int i = 0; i < edges; i++) {
        int u, v;
        cout << "[Edge: " << i+1 << "] : ";
        cin >> u >> v;
        if(!g.insert(u,v))
            i--;
    }
    
    cout << "!!! DFS !!!" << endl; 
    bool *visited = new bool[vertices+1];
    for(int i = 1; i <= vertices; i++)
        visited[i] = false;

    int componentNumber{1};
    for(int i = 1; i <= vertices; i++) {
        if(!visited[i]) {
            cout << "Component : #" << componentNumber++ << " : ";
            g.dfs(i,visited);
            cout << endl;
        }
    }
    return 0;
}