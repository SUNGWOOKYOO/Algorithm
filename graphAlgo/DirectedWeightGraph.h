#pragma once
#include<iostream>
#include<list>
#include<vector>
#include<stack>
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

	void topoDFS(stack<int>& S, vector<bool>& visited, int v) {
		visited[v] = true;
		for (auto it = adj[v].begin(); it != adj[v].end(); ++it) {
			if (visited[(*it).second] == false) {
				topoDFS(S, visited, (*it).second);
			}
		}

		// finish timing, that is, once a vertex with finish time has been determined, it can be put on the stack.
		// by doing so,
		// later on, if we pop the stack until being empty,
		// we can obtain a list of nodes with the ending time in descending order.
		cout << "push " << v << " node" << endl;
		S.push(v);
	}
	list<int> TopoSort() {
		stack<int> S;
		list<int> L;
		vector<bool> visited(NumOfvertices, false);

		// Let assume that the node with small number has a higher priority when DFS search  
		for (int i = 0; i < NumOfvertices; ++i) {
			if (visited[i] == false) {
				cout << "DFS search starts at " << i << "... " << endl;
				topoDFS(S, visited, i);
			}
		}
		while (!S.empty()) {
			L.push_back(S.top());		S.pop();
		}
		return L;
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
