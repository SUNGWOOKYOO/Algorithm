#pragma once
#include <iostream>
#include<list>
using namespace std;

typedef std::pair<int, int> edgeInfo; // {weight, vertex_id}

class Graph {
public:
	int NumOfvertices;
	list<edgeInfo>* adj;
	Graph(int NumV) {
		NumOfvertices = NumV;
		adj = new list<edgeInfo>[NumOfvertices];
	}
	~Graph() {
		delete[]adj;
	}
	void addEdge(int u, int v, int w) {
		adj[u].push_back({ w,v });	
		//adj[v].push_back({ w,u }); // undirected edge weight <=> bi-direction edge 
	}

	void showInfo() {
		// O(V+E)
		for (int i = 0; i < NumOfvertices; ++i) {
			for (auto it = adj[i].begin(); it != adj[i].end(); ++it) {
				cout << "(" << i << ", " << (*it).second << "," << (*it).first << ")" << endl;
			}
		}
	}
};
