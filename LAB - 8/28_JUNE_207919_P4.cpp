/* 
L8.4 Implement the Breadth First Search (BFS) graph traversal algorithm.
1. I am using nodes as 1 based indexing eg. if number of vertices = 3, vertices will be 1,2,3
2. I am using directed graph
*/
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

class Graph {
    public:
        Graph(const int n) 
            :
            vertices{n}, graph{new vector<int>[n+1]}
            {}
        bool insert(const int,const int);
        void bfs(const int&) const;
    private:
        vector<int> *graph;
        int vertices;
};

bool Graph::insert(const int u, const int v) {
    if(u < 1 || v < 1 || u > vertices || v > vertices) {
        cout << "[Warning] Edge out of bound";
        return false;
    }

    graph[u].push_back(v);
    return true;
}

void Graph::bfs(const int& src) const{
    if(src < 1 || src > vertices) {
        cout << "[Warning] Source out of bound. Aborting bfs";
        return;
    }
    vector<bool> visited(vertices+1,false);
    queue<int> q;
    q.push(src);
    visited[src] = true;
    cout << "BFS : ";
    while(!q.empty()) {
        int curr = q.front();
        q.pop();
        cout << curr << " ";
        for(auto it : graph[curr]) {
            if(!visited[it]) {
                visited[it] = true;
                q.push(it);
            }
        }
    }
    cout << endl;
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
    
    int src;
    cout << "Enter source node for bfs : ";
    cin >> src;
    g.bfs(src);
    return 0;
}