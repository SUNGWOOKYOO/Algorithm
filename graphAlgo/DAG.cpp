#include<iostream>
#include"DirectedWeightGraph.h"
#include<list>
#include<limits>
#include<iomanip>
using namespace std;
// https://www.geeksforgeeks.org/shortest-path-for-directed-acyclic-graphs/
void dag(Graph& G, int src){
	int* d = new int[G.NumOfvertices];
	int INF = 1e+8; // numerical max is not good option because it will lead to overflowing integer value 
	list<int> L = G.TopoSort();

	// Initialization 
	for (int i = 0; i < G.NumOfvertices; ++i) {
		if (i == src)
			d[i] = 0;
		else
			d[i] = INF;
	}

	// O(V + E)
	for (auto u: L) {
		//cout << "update " << u <<" ... "<< endl;
		for (auto vInfo : G.adj[u]) {
			int v = vInfo.second;
			int w = vInfo.first;
			if (d[v] > d[u] + w) {
				d[v] = d[u] + w;
				//cout << "weight "<< w << endl;
				//cout << "update d["<< v <<"] -> "<<d[v]<< endl;
			}
		}
	}

	cout << "shortest distance d[]:" << endl;
	for (int i = 0; i < G.NumOfvertices; ++i) {
		cout << setw(15) << d[i];
	}

	delete[]d;
}
int main() {

	// Create a graph given in the above diagram.  Here vertex numbers are 
   // 0, 1, 2, 3, 4, 5 with following mappings: 
   // 0=r, 1=s, 2=t, 3=x, 4=y, 5=z 
	Graph g(6);
	g.addEdge(0, 1, 5);
	g.addEdge(0, 2, 3);
	g.addEdge(1, 3, 6);
	g.addEdge(1, 2, 2);
	g.addEdge(2, 4, 4);
	g.addEdge(2, 5, 2);
	g.addEdge(2, 3, 7);
	g.addEdge(3, 4, -1);
	g.addEdge(4, 5, -2);
	g.showInfo();

	int s = 1;
	cout << "Following are shortest distances from source " << s << endl;
	dag(g, s);
	/*
(0, 1,5 )
(0, 2,3 )
(1, 3,6 )
(1, 2,2 )
(2, 4,4 )
(2, 5,2 )
(2, 3,7 )
(3, 4,-1 )
(4, 5,-2 )
Following are shortest distances from source 1
shortest distance d[]:
	  100000000              0              2              6              5              3
	*/
	return 0;
}