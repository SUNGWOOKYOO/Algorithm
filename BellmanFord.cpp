#include<iostream>
#include"DirectedWeightGraph.h"
#include<limits>
#include<vector>
#include<iomanip>
using namespace std;

// https://www.geeksforgeeks.org/bellman-ford-algorithm-dp-23/
void bellman(Graph& G, int src) {
	int* d = new int[G.NumOfvertices];
	int INF = std::numeric_limits<int>::max();

	// Initialization 
	for (int i = 0; i < G.NumOfvertices; ++i) {
		if (i == src) 
			d[i] = 0;
		else 
			d[i] = INF;
	}

	// O(V+E)
	vector<pair<int,edgeInfo>> edges;
	for (int i = 0; i < G.NumOfvertices; ++i) {
		for (auto it = G.adj[i].begin(); it != G.adj[i].end(); ++it) {
			edges.push_back({ i,*it });
		}
	}

	// O(VE)
	for (int i = 0; i < G.NumOfvertices; ++i) {
		for (auto edge: edges) {
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

	for (int i = 0; i < G.NumOfvertices; ++i) {
		cout << setw(15) << d[i];
	}

	delete[]d;
}
int main() {
	int V = 5;
	Graph g(V);
	//  making above shown graph 
	g.addEdge(0, 1, -1);
	g.addEdge(0, 2, 4);
	g.addEdge(1, 2, 3);
	g.addEdge(1, 3, 2);
	g.addEdge(1, 4, 2);
	g.addEdge(3, 2, 5);
	g.addEdge(3, 1, 1);
	g.addEdge(4, 3, -3);
	g.showInfo();
	bellman(g, 0);
	return 0;
}