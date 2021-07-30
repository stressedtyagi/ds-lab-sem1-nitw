/* 
L9.3 Find minimum spanning tree of a simple connected undirected graph using Kruskal’s algorithm
For GRAPH : 
1. I am using nodes as 1(one) based indexing eg. if number of vertices = 3, vertices will be 1,1,2
2. I am using undirected graph
4. Graph will be stored as : an array that will store the information about all the edges as (u,v,wt), where u - souce, v - destination, wt - weight of edge. Where each edge is object is about of Structure Edge.

Also i have included Algorithm header file just to use sort() function since if i try to implement sort using any sorting techniques 
the time complexity of the algorithm may be voilated and could cause algorithm to run in more time than the one it actually has to.
*/
#include <iostream>
#include <algorithm>
using namespace std;

class DisjointSet {
    public:
        DisjointSet(int n) : parent{new int[n+1]}, rank{new int[n+1]} {
            for(int i = 1; i <= n; i++) 
                parent[i] = i, rank[i] = 0;
        } 
        int find(int i) {
            return parent[i] == i ? i : parent[i] = find(parent[i]);
        }
        void Union(int u, int v) {
            u = find(u);
            v = find(v);
            if(rank[u] < rank[v]) {
                parent[u] = u; 
            }else if (rank[u] > rank[v]) {
                parent[v] = u;
            }else {
                parent[v] = u;
                rank[u]++;
            }
        }
    private:
        int *parent, *rank;
};

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
        void Kruskal(const int);
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

void Graph::Kruskal(const int edges) {
    // sorting graph edges wrt edge weight
    // using inbuilt sort function to sort these
    // reason to use this function is given above
    // also i use Lambda instead of defining separtate compare function
    sort(graph,graph+vertices,[](const Edge& i, const Edge& j) {
        return i.wt < j.wt;
    });

    DisjointSet dset(vertices);
    int cost{0};
    int **a = new int*[edges];
    int index{0};
    for(int i = 1; i <= vertices; i++) {
        Edge curr = graph[i];
        if(dset.find(curr.u) != dset.find(curr.v)) {
            cost += curr.wt;
            a[index] = new int[3];
            a[index][0] = curr.u;
            a[index][1] = curr.v;
            a[index][2] = curr.wt;
            index++;
            dset.Union(curr.u,curr.v);
        }
    }
    for(int i = 0; i < index; i++) {
        cout << "[Edge : " << i+1 << "]: " << a[i][0] << " -> " << a[i][1] << " : " << a[i][2] << endl;
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
    
    cout << "!!! MST : Kruskal ALGO !!!" << endl;
    int src;
    g.Kruskal(edges);

    return 0;
}