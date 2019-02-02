#include<iostream>
#include<vector>
#include<algorithm>
#include<list>
#include<queue>
using namespace std;

// https://www.geeksforgeeks.org/prims-algorithm-using-priority_queue-stl/
// Prim algorithm input: connected undirected weight graph
/*
 In Prim¡¯s algorithm, we need a priority queue and below operations on priority queue :

ExtractMin : 
	from all those vertices which have not yet been included in MST, we need to get vertex with minimum key value.
DecreaseKey : 
	After extracting vertex we need to update keys of its adjacent vertices, and if new key is smaller, then update that in data structure.

 The algorithm discussed here can be modified so that decrease key is never required. The idea is, not to insert all vertices in priority queue, 
but only those which are not MST and have been visited through a vertex that has included in MST. 
We keep track of vertices included in MST in a separate boolean array inMST[].
*/

typedef std::pair<int, int> edgeInfo; // {weight, vertex_id}

class Graph {
public:
	int NumOfvertices;
	list<edgeInfo>* adj;
	Graph(int NumV) {
		NumOfvertices = NumV;
		adj = new list<edgeInfo>[NumOfvertices];
	}
	void addEdge(int u, int v, int w) {
		// undirected edge weight <=> bi-direction edge 
		adj[u].push_back({ w,v });
		adj[v].push_back({ w,u });
	}
	void prim() {
		// https://www.geeksforgeeks.org/implement-min-heap-using-stl/
		// make priority queue using min-heap 
		std::priority_queue<edgeInfo, vector<edgeInfo>, greater<edgeInfo>> pq;

		int src = 0; // taking vertex 0 as a src (other vertices can be used.)

		int INF = 100000; // large value
		vector<int> key(NumOfvertices, INF);
		vector<int> parent(NumOfvertices, -1);
		vector<bool> inMST(NumOfvertices, false);

		pq.push({ 0,src });
		key[src] = 0;
		while (!pq.empty()) {
			int u = pq.top().second; pq.pop();
			inMST[u] = true;
			for (auto it = adj[u].begin(); it != adj[u].end(); ++it) {
				int v = (*it).second;   
				int weight = (*it).first; 
				if (inMST[v] == false && key[v] > weight) {
					// update key[v]
					key[v] = weight;
					pq.push({ key[v], v });
					parent[v] = u;
				}
			}
		}

		int result = 0;
		cout << "Edges of MST are \n";
		for (int i = 1; i < NumOfvertices; ++i) {
			cout << parent[i] << "-" << i << endl;
			result = result + key[i];
		}

		cout << "\nWeight of MST is " << result << endl;
	}
};

int main() {
	int V = 9;
	Graph g(V);
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

	g.prim();
	return 0;
}