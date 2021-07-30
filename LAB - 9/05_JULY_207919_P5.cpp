/* 
L9.5 Solve single source shortest problem using Bellman–Ford algorithm

For GRAPH : 
1. I am using nodes as 1(one) based indexing eg. if number of vertices = 3, vertices will be 1,1,2
2. I am using undirected graph
*/
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

struct Edge {
    int u;
    int v;
    int wt;
};

class Graph {
    public:
        Graph(const int edges, const int vertices)
            : vertices{vertices}, graph{new Edge[edges+1]}
        {}
        
        bool insert(const int,const int, const int,const int);
        void BellmanFord(const int&,int*,const int&); 
    private:
        Edge *graph;
        int vertices;
};

bool Graph::insert(const int index, const int u, const int v,const int wt) {
    if (u < 1 || v < 1 || u > vertices || v > vertices) {
        cout << "[Warning] Edge out of bound";
        return false;
    }
    // Since undirected graph i will make an edge from u->v as well as
    // from v->u
    graph[index] = {u,v,wt};
    return true;
}

void Graph::BellmanFord(const int& src, int *dist,const int& edges) {
    dist[src] = 0;
    // Relaxing all edges V-1 (V:number of vertices) time
    for(int n = 1; n <= vertices-1; n++) {
        for(int i = 1; i <= edges; i++) {
            Edge curr = graph[i];
            if(dist[curr.u] + curr.wt < dist[curr.v])
                dist[curr.v] = dist[curr.u] + curr.wt;
        }
    }
}

int main() {
    int vertices, edges;
    cout << "Enter number of nodes in graph : ";
    cin >> vertices;
    cout << "Enter number of edges : ";
    cin >> edges;

    Graph g(edges,vertices);
    cout << "~~~~~ HERE u-source, v-dest, wt-weight of edge ~~~~~" << endl;
    cout << "!! Enter edges (u,v,wt) !! " << endl;
    for(int i = 0; i < edges; i++) {
        int u, v, wt;
        cout << "[Edge: " << i+1 << "] : ";
        cin >> u >> v >> wt;
        if(!g.insert(i+1,u,v,wt))
            i--;
    }
    
    cout << "!!! Bellman Ford ALGO !!!" << endl;
    int src;
    cout << "Enter source node: ";
    cin >> src;
    int *dist = new int[vertices+1];
    for(int i = 1; i <= vertices; i++)
        dist[i] = INT32_MAX;
    g.BellmanFord(src,dist,edges);
    cout << "!! Shortest distance of all nodes from " << src << " !!" << endl;
    for(int i = 1;i <= vertices; i++) {
        cout << "[Node " << i << "] : " << dist[i] << endl;
    }
    return 0;
}