#include <iostream>
#include "DirectedWeightGraph.h"
#include <iomanip>
#include <queue>
#include<vector>

using namespace std;

// O(VE)
vector<int> bellman(Graph& G, int src) {
	vector<int> d(G.NumOfvertices);
	int INF = 1e+8;

	// Initialization 
	for (int i = 0; i < G.NumOfvertices; ++i) {
		if (i == src)
			d[i] = 0;
		else
			d[i] = INF;
	}

	// O(V+E)
	vector<pair<int, edgeInfo>> edges;
	for (int i = 0; i < G.NumOfvertices; ++i) {
		for (auto it = G.adj[i].begin(); it != G.adj[i].end(); ++it) {
			edges.push_back({ i,*it });
		}
	}

	// O(VE)
	for (int i = 0; i < G.NumOfvertices; ++i) {
		for (auto edge : edges) {
			int u = edge.first;
			int v = edge.second.second;
			int weight = edge.second.first;
			if (d[v] > d[u] + weight) {
				d[v] = d[u] + weight;
			}
		}
	}

	for (auto edge : edges) {
		int u = edge.first;
		int v = edge.second.second;
		int weight = edge.second.first;
		if (d[v] > d[u] + weight) {
			d[v] = d[u] + weight;
			cout << "negative edge exists" << endl;
			exit(-1);
		}
	}
	/*
	for (int i = 0; i < G.NumOfvertices; ++i) {
	   cout << setw(8) << d[i];
	}
	*/
	return d;
}

// O((V+E)logV), if we implement by pseudocode, but in this code, O(V^2logV)
void Dijkstra(Graph& G, int src, vector<vector<int> >& D) {
	int* d = new int[G.NumOfvertices];
	int INF = 1e+8;
	// make priority queue using min heap
	std::priority_queue<edgeInfo, vector<edgeInfo>, greater<edgeInfo>> pq;
	vector<bool> InS(G.NumOfvertices, false);

	// O(V)
	for (int i = 0; i < G.NumOfvertices; ++i) {
		if (i == src)
			d[i] = 0;
		else
			d[i] = INF;
	}
	pq.push({ 0,src });

	while (!pq.empty()) {
		int u = pq.top().second; pq.pop();
		InS[u] = true;
		for (auto it = G.adj[u].begin(); it != G.adj[u].end(); ++it) {
			int v = (*it).second;
			int weight = (*it).first;
			
			// there were no change after decide tree        
			if (InS[v] == false && d[v] > d[u] + weight) {
				// update key[v]
				d[v] = d[u] + weight; 
				pq.push({ d[v], v }); 
			}
		}
	}
	/*
	cout << "shortest distance d[]:" << endl;
	for (int i = 0; i < G.NumOfvertices; ++i) {
	   cout << setw(8) << d[i];
	}
	*/
	for (int i = 0; i < G.NumOfvertices; ++i) {
		D[src][i] = d[i];
	}
	delete[]d;
}

// O(VE + V(V+E)logV)
void Johnson(Graph& G) {
	int src = G.NumOfvertices;
	// O(V+E)
	Graph modified_g(G.NumOfvertices + 1);
	vector<int> h(modified_g.NumOfvertices);
	for (int u = 0; u < G.NumOfvertices; ++u)
	{
		modified_g.addEdge(src, u, 0);
		for (auto it = G.adj[u].begin(); it != G.adj[u].end(); ++it) {
			int w = it->first;
			int v = it->second;
			modified_g.addEdge(u, v, w);
		}
	}
	//cout << "modified graph" << endl;
	//modified_g.showInfo();
	// O(VE)
	h = bellman(modified_g, src);

	// O(V + E)
	for (int u = 0; u < modified_g.NumOfvertices; ++u)
	{
		for (auto& edge : modified_g.adj[u]) {
			int v = edge.second;
			int w = edge.first + h[u] - h[v];
			edge = { w,v };
		}
	}
	//cout << "modified graph" << endl;
	//modified_g.showInfo();
	int INF = 1e+8;
	vector<int> init_rows(G.NumOfvertices, INF);
	vector<vector<int> > D(G.NumOfvertices, init_rows);
	modified_g.NumOfvertices -= 1;
	// O(V(V+E)logV), if V > E, O(V^2logV)
 	for (int u = 0; u < G.NumOfvertices; ++u) {
		Dijkstra(modified_g, u, D);
		for (int v = 0; v < G.NumOfvertices; ++v) {
			D[u][v] = D[u][v] + h[v] - h[u];
			cout << setw(12) << D[u][v];
		} cout << endl;
	}
}
int main() {
	int V = 5;
	Graph g(V);
	//  making above shown graph 
	g.addEdge(0, 1, 3);
	g.addEdge(0, 2, 8);
	g.addEdge(0, 4, -4);
	g.addEdge(1, 3, 1);
	g.addEdge(1, 4, 7);
	g.addEdge(2, 1, 4);
	g.addEdge(3, 0, 2);
	g.addEdge(3, 2, -5);
	g.addEdge(4, 3, 6);
	g.showInfo();

	Johnson(g);
/*
(0, 1, 3)
(0, 2, 8)
(0, 4, -4)
(1, 3, 1)
(1, 4, 7)
(2, 1, 4)
(3, 0, 2)
(3, 2, -5)
(4, 3, 6)
		   0           1          -3           2          -4
		   3           0          -4           1          -1
		   7           4           0           5           3
		   2          -1          -5           0          -2
		   8           5           1           6           0
*/
	return 0;
}