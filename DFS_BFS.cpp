#include <iostream>
#include <list>
#include <stack>
#include <vector>
#include <queue>
using namespace std;

class Graph{
private:
	int NumofVertices = 0;
	// std:: list
	list<int>* adj; 
public:
	Graph(int _NumofVertices) {
		this->NumofVertices = _NumofVertices;
		adj = new list<int>[NumofVertices];
	}
	void addEdge(int v, int w) {
		adj[v].push_back(w);
	}
	void DFS(int);
	void BFS(int);
	list<int> TopoSort();
	void topoDFS(stack<int>&, vector<bool>&, int v);
};

void Graph::DFS(int s) {
	//TODO
	vector<bool> visited(NumofVertices, false); //Initialization of visited list 
	stack<int> S; 
	S.push(s);
	while (!S.empty()) {
		int v = S.top(); S.pop();
		if (visited[v] == false) {
			cout << v << " ";
			visited[v] = true;
		}
		for (auto it = adj[v].begin(); it != adj[v].end(); ++it) {
			if (visited[*it] == false) {
				S.push(*it);
			}
		}
	}
	cout << endl;
}
void Graph::BFS(int v) {
	// TODO
	vector<bool> visited(NumofVertices, false);
	queue<int> Q;
	Q.push(v); 
	visited[v] = true;

	while (!Q.empty()) {
		int v = Q.front();  Q.pop();
		cout << v << " ";

		for (auto it = adj[v].begin(); it != adj[v].end(); ++it) {
			if (visited[*it] == false) {
				Q.push(*it);
				visited[*it] = true;
			}
		}
	}
	cout << endl;

}

void Graph::topoDFS(stack<int>& S, vector<bool>& visited, int v) {
	visited[v] = true;
	for (auto it = adj[v].begin(); it != adj[v].end(); ++it ) {
		if (visited[*it] == false) {
			topoDFS(S, visited, *it);
		}
	}
	cout << "push " << v <<" node"<< endl;
	S.push(v);
}
list<int> Graph::TopoSort() {
	stack<int> S;
	list<int> L;
	vector<bool> visited(NumofVertices, false);
	
	// Let assume that the node with small number has a higher priority when DFS search  
	for (int i = 0; i < NumofVertices; ++i) {
		if (visited[i] == false)
			cout << "DFS search starts at "<< i <<"... " << endl;
			topoDFS(S, visited, i);
	}
	while (!S.empty()) {
		L.push_back(S.top());
		S.pop();
	}
	return L;
}

int main() {
	Graph g(5); // Total 5 vertices in graph 
	g.addEdge(1, 0);
	g.addEdge(0, 2);
	g.addEdge(2, 1);
	g.addEdge(0, 3);
	g.addEdge(1, 4);
	cout << "Following is Depth First Traversal\n";
	g.DFS(0);
	cout << "Following is Bread First Traversal\n";
	g.BFS(0);


	// Create a graph given in the above diagram 
	Graph g2(6);
	g2.addEdge(5, 2);
	g2.addEdge(5, 0);
	g2.addEdge(4, 0);
	g2.addEdge(4, 1);
	g2.addEdge(2, 3);
	g2.addEdge(3, 1);

	cout << "Result of Topological sort\n"; // the graph should be DAG 
	list<int> TopoList = g2.TopoSort();
	for (auto it = TopoList.begin(); it != TopoList.end(); ++it) {
		cout << *it;
		if (it != TopoList.end()) cout << " ";
	}
	cout << endl;
	return 0;
}