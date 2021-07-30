/* 
L9.2 Find minimum spanning tree of a simple connected undirected graph using Prim’s algorithm
For GRAPH : 
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
            : vertices{n}, graph{new vector<pair<int,int>>[n + 1]}
        {}
        
        bool insert(const int, const int,const int);
        void prims(const int,bool*,int*,int*);
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

void Graph::prims(const int src, bool *mst, int *key, int *parent) {
    // setting weight to reach source node equal to 0
    key[src] = 0;
    for(int i = 1; i < vertices; i++) {
        int u{1}, minWeight{INT32_MAX};
        for(int j = 1; j <= vertices; j++) {
            if(minWeight > key[i] && !mst[i])
                minWeight = key[i], u = i;
        }
        if(minWeight == INT32_MAX)
            break;
        mst[u] = true;
        for(auto it : graph[u]) {
            int v = it.first;
            int wt = it.second;
            if(!mst[v] && key[v] > wt) {
                parent[v] = u;
                key[v] = wt;
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

    Graph g(vertices);
    cout << "~~~~ HERE u-source, v-dest, wt-weight of edge ~~~~~" << endl;
    cout << "!! Enter edges (u,v,wt) !! " << endl;
    for(int i = 0; i < edges; i++) {
        int u, v, wt;
        cout << "[Edge: " << i+1 << "] : ";
        cin >> u >> v >> wt;
        if(!g.insert(u,v,wt))
            i--;
    }
    
    cout << "!!! MST : PRIMS ALGO !!!" << endl;
    int src;
    cout << "Enter src node : ";
    cin >> src;
    bool *mst = new bool[vertices+1];
    int *key = new int[vertices+1];
    int *parent = new int[vertices+1];
    for(int i = 1; i <= vertices; i++)
        mst[i] = false, key[i] = INT32_MAX, parent[i] = -1;
    g.prims(src,mst,key,parent);
    for (int i = 1; i <= vertices; i++) 
        cout << "[Node]: " << i << " - [Parent]: " << parent[i] << " - [Weight]: " << key[i] << endl;
    return 0;
}