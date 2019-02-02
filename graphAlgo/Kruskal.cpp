#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

// https://www.geeksforgeeks.org/kruskals-minimum-spanning-tree-using-stl-in-c/
// Kruskal algorithm input: connected undirected weight graph
typedef std::pair<int, int> edge; // {vertex_id, vertex_id}

// use 2 heuristics
// 1. path compression 
// 2. union by rank 
class DisjointSet {
public:
	int* parent;
	int* rank;
	int num;
	DisjointSet(int n) {
		// {S0,S1, ..., Sn-1} are disjoint each other
		num = n;
		parent = new int[n];
		rank = new int[n];
		for (int i = 0; i < n; ++i) {
			rank[i] = 0;
			parent[i] = i;
		}
	}
	int find(int u) {
		if (u != parent[u])
			parent[u] = find(parent[u]); // path compression
		return parent[u];
	}
	void Union(int x, int y) {
		// find each representative for the set that includes x and y
		x = find(x);
		y = find(y);

		// union by rank
		if (rank[x] > rank[y])
			parent[y] = x;
		else
			parent[x] = y;

		if (rank[x] == rank[y])
			rank[y] = rank[y] + 1;
	}
};

class Graph {
public:
	int NumOfVertices;
	int NumOfEdges;
	vector<pair<int, edge>> edges; // {weight, edge} 
	Graph(int NumV, int NumE) {
		NumOfVertices = NumV;
		NumOfEdges = NumE;
	}
	void addEdge(int u, int v, int w) {
		edges.push_back({ w,{u,v} });
		//edges.push_back(make_pair(w,make_pair(u,v)));
	}
	int kruskal() {
		int result = 0;

		// https://www.geeksforgeeks.org/sorting-a-vector-in-c/
		// #include<algorithm>
		// sort by edges[*it].first(weight), auto it = edge.begin() ~ edge.end()
		std::sort(edges.begin(), edges.end());  

		DisjointSet Ds(NumOfVertices);
		for (auto it = edges.begin(); it != edges.end(); ++it) {
			int u = it->second.first;
			int v = it->second.second;
			if (Ds.find(u) != Ds.find(v)) {
				// print MST edge(greedy choice) 
				cout << u << "-" << v << endl;
				// update the sum of MST weight 
				result = result + it->first;

				Ds.Union(u, v);
			}
		}
		
		return result;
	}
};

int main() {
	/* Let us create above shown weighted
	   and unidrected graph */
	int V = 9, E = 14;
	Graph g(V, E);

	//  making above shown graph 
	g.addEdge(0, 1, 4);
	g.addEdge(0, 7, 8);
	g.addEdge(1, 2, 8);
	g.addEdge(1, 7, 11);
	g.addEdge(2, 3, 7);
	g.addEdge(2, 8, 2);
	g.addEdge(2, 5, 4);
	g.addEdge(3, 4, 9);
	g.addEdge(3, 5, 14);
	g.addEdge(4, 5, 10);
	g.addEdge(5, 6, 2);
	g.addEdge(6, 7, 1);
	g.addEdge(6, 8, 6);
	g.addEdge(7, 8, 7);

	cout << "Edges of MST are \n";
	int mst_wt = g.kruskal();
	cout << "\nWeight of MST is " << mst_wt;

	return 0;
}