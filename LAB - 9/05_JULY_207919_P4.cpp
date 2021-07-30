/* 
L9.4 Solve single source shortest path problem using Dijkstra’s algorithm and priority queue

For GRAPH : 
1. I am using nodes as 1(one) based indexing eg. if number of vertices = 3, vertices will be 1,1,2
2. I am using undirected graph
*/
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

class Graph {
    public:
        Graph(const int edges, const int vertices)
            : vertices{vertices}, graph{new vector<pair<int,int>>[vertices+1]}
        {}
        
        bool insert(const int, const int,const int);
        void Dijkstra(int,int*); 
    private:
        vector<pair<int,int>> *graph;
        int vertices;
};



bool Graph::insert(const int u, const int v,const int wt) {
    if (u < 1 || v < 1 || u > vertices || v > vertices) {
        cout << "[Warning] Edge out of bound";
        return false;
    }
    // Since undirected graph i will make an edge from u->v as well as
    // from v->u
    graph[u].push_back({v,wt});
    graph[v].push_back({u,wt});
    return true;
}

void Graph::Dijkstra(int src, int *dist) {
    priority_queue<pair<int,int>> pq;
    pq.push({0,src});
    dist[src] = 0;
    while(!pq.empty()) {
        int curr = pq.top().second;
        int wt = pq.top().first;
        pq.pop();
        for(auto it : graph[curr]) {
            if(dist[it.first] > wt + it.second) {
                dist[it.first] = wt + it.second;
                cout << it.first << dist[it.first] << endl;
                pq.push({dist[it.first],it.first});
            }
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
        if(!g.insert(u,v,wt))
            i--;
    }
    
    cout << "!!! Dijkstra’s ALGO !!!" << endl;
    int src;
    cout << "Enter source node: ";
    cin >> src;
    int *dist = new int[vertices+1];
    for(int i = 1; i <= vertices; i++)
        dist[i] = INT32_MAX;
    g.Dijkstra(src,dist);
    cout << "!! Shortest distance of all nodes from " << src << " !!" << endl;
    for(int i = 1;i <= vertices; i++) {
        cout << "[Node " << i << "] : " << dist[i] << endl;
    }
    return 0;
}