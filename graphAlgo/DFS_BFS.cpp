#include <iostream>
#include <list>
#include <stack>
#include <vector>
#include <queue>
using namespace std;

// DFS can be implemented by recursive call without stack 
// because recursive call means using a stack in our main memory(stack field)
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
	Graph getTranspose() {
		Graph g(NumofVertices);
		for (int v = 0; v < NumofVertices; v++){
			for (auto it = adj[v].begin(); it != adj[v].end(); ++it){
				g.adj[*it].push_back(v);
			}
		}
		return g;
	}

	void DFS_recursive(int);
	void DFSUtil(int, vector<bool>&);
	void DFS(int);
	void DFSAll();
	void BFS(int);

	// Intuition: when we use DFS, we can notice that the more we search deeply, the more late the finish time of the node is. 
	list<int> TopoSort();
	void topoDFS(stack<int>&, vector<bool>&, int v);
	void SCC();
};

void Graph::DFSUtil(int v, vector<bool>& visited) {
	// S.pop 
	// update v.d timing 
	cout << v << " ";
	visited[v] = true;

	for (auto it = adj[v].begin(); it != adj[v].end(); ++it) {
		if (visited[*it] == false) {
			//S.push(*it);
			DFSUtil(*it, visited);
		}
	}

	// update v.f set timing 
	return;
}
void Graph::DFS_recursive(int s) {
	vector<bool> visited(NumofVertices, false);

	// S.push(s)
	DFSUtil(s, visited);
	cout << endl;
}
// iterative version
void Graph::DFS(int s) {
	//TODO
	vector<bool> visited(NumofVertices, false); //Initialization of visited list 
	stack<int> S; 
	S.push(s);
	while (!S.empty()) {
		int v = S.top(); S.pop();

		// update v.d timing
		cout << v << " ";
		visited[v] = true;
		
		for (auto it = adj[v].begin(); it != adj[v].end(); ++it) {
			if (visited[*it] == false) {
				S.push(*it);
			}
		}
	}
	cout << endl;
}

void Graph::DFSAll() {
	// DFS all vertices 
	//TODO
	vector<bool> visited(NumofVertices, false);

	// recursive way
	for (int i = 0; i < NumofVertices; ++i) {
		if (visited[i] == false) {
			cout << "Depth search ... "; 
			DFSUtil(i, visited);
			cout << endl;
		}
	}
	// iterative way 
	/*
	for (int i = 0; i < NumofVertices; ++i) {
		if (visited[i] == false) {
			stack<int> S;
			S.push(i);
			while (!S.empty()) {
				int v = S.top(); S.pop();

				// finish timing 
				cout << v << " ";
				visited[v] = true;

				for (auto it = adj[v].begin(); it != adj[v].end(); ++it) {
					if (visited[*it] == false) {
						S.push(*it);
					}
				}
			}
			cout << endl;
		}
	}
	*/
}

void Graph::BFS(int v) {
	// TODO
	vector<bool> visited(NumofVertices, false);
	queue<int> Q;
	Q.push(v); 
	visited[v] = true;

	while (!Q.empty()) {
		int v = Q.front();  Q.pop();

		// update  v.d timing
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

	// finish timing, that is, once a vertex with finish time has been determined, it can be put on the stack.
	// by doing so,
	// later on, if we pop the stack until being empty,
	// we can obtain a list of nodes with the ending time in descending order.
	cout << "push " << v <<" node"<< endl;
	S.push(v);
}
list<int> Graph::TopoSort() {
	stack<int> S;
	list<int> L;
	vector<bool> visited(NumofVertices, false);
	
	// Let assume that the node with small number has a higher priority when DFS search  
	for (int i = 0; i < NumofVertices; ++i) {
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
void Graph::SCC() {

	cout << "Topological sort ... " << endl;
	list<int> L = TopoSort();

	cout << "transpose ..." << endl;
	Graph gt = getTranspose();
	vector<bool> visited(NumofVertices, false);

	cout << "DFS for gt ... " << endl;
	int p = 0;
	for (auto it = L.begin(); it != L.end(); ++it) {
		if (visited[*it] == false) {
			cout << "SCC["<<p++<<"] ... ";
			gt.DFSUtil(*it, visited);
			cout << endl;
		}
	}
}

int main() {
	Graph g(5); // Total 5 vertices in graph 
	g.addEdge(1, 0);
	g.addEdge(0, 2);
	g.addEdge(2, 1);
	g.addEdge(0, 3);
	g.addEdge(1, 4);
	cout << "Following is Depth First Traversal iterative version \n";
	g.DFS(0);

	cout << "Following is Depth First Traversal recursive version \n";
	g.DFS_recursive(0);

	Graph gall(8); // Total 5 vertices in graph 
	gall.addEdge(0, 1);
	gall.addEdge(1, 3);
	gall.addEdge(1, 2);
	gall.addEdge(1, 6);
	gall.addEdge(3, 5);
	gall.addEdge(3, 2);
	gall.addEdge(4, 0);
	gall.addEdge(7, 0);
	gall.addEdge(4, 7);
	cout << "Following is Depth First Traversal All version \n";
	gall.DFSAll();

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

	cout << "Result of SCC \n";
	Graph g3(5);
	g3.addEdge(1, 0);
	g3.addEdge(0, 2);
	g3.addEdge(2, 1);
	g3.addEdge(0, 3);
	g3.addEdge(3, 4);
	g3.SCC();
	/*
Following is Depth First Traversal iterative version
0 3 2 1 4
Following is Depth First Traversal recursive version
0 2 1 4 3
Following is Depth First Traversal All version
Depth search ... 0 1 3 5 2 6
Depth search ... 4 7
Following is Bread First Traversal
0 2 3 1 4
Result of Topological sort
DFS search starts at 0...
push 0 node
DFS search starts at 1...
push 1 node
DFS search starts at 2...
push 3 node
push 2 node
DFS search starts at 4...
push 4 node
DFS search starts at 5...
push 5 node
5 4 2 3 1 0
Result of SCC
transpose ...
Topological sort ...
DFS search starts at 0...
push 1 node
push 2 node
push 4 node
push 3 node
push 0 node
DFS for gt ...
SCC[0] ... 0 1 2
SCC[1] ... 3
SCC[2] ... 4
	*/
	return 0;
}