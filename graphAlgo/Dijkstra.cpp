#include<iostream>
#include"DirectedWeightGraph.h"
#include<queue>

using namespace std;
// https://www.geeksforgeeks.org/dijkstras-shortest-path-algorithm-using-priority_queue-stl/
void dijkstra(Graph& G, int src) {
	int INF = 1e+8;
	// Initialization 
	vector<int> d(G.NumOfvertices, INF);
	d[src] = 0;

	// make priority queue using min-heap 
	std::priority_queue<edgeInfo, vector<edgeInfo>, greater<edgeInfo>> pq;
	vector<bool> inS(G.NumOfvertices, false); // vertices list that shortest path is already decided 
	pq.push({ 0,src });

	while (!pq.empty()) {
		int u = pq.top().second; pq.pop();
		inS[u] = true; // vertices in inS set have already shortest path distance
		for (auto it = G.adj[u].begin(); it != G.adj[u].end(); ++it) {
			int v = (*it).second;
			int weight = (*it).first;
			if (inS[v] == false && d[v] > d[u] + weight) {
				// update d[v]
				d[v] = d[u] + weight;
				pq.push({ d[v], v });
			}
		}
	}

	cout << "shortest distance d[]:" << endl;
	for (int i = 0; i < G.NumOfvertices; ++i) {
		cout << d[i] << " ";
	}cout << endl;

}

int main() {
	// create the graph given in above fugure 
	int V = 5;
	Graph g(V);
	//  making above shown graph 
	g.addEdge(0, 1, 10);
	g.addEdge(0, 3, 5);
	g.addEdge(1, 2, 1);
	g.addEdge(1, 3, 2);
	g.addEdge(2, 4, 4);
	g.addEdge(3, 1, 3);
	g.addEdge(3, 2, 9);
	g.addEdge(3, 4, 2);
	g.addEdge(4, 0, 2);
	g.addEdge(4, 2, 6);
	g.showInfo();
	dijkstra(g, 0);
	return 0;
}