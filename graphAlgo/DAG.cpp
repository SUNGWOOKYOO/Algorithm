#include<iostream>
#include"DirectedWeightGraph.h"
#include<list>
using namespace std;
// https://www.geeksforgeeks.org/shortest-path-for-directed-acyclic-graphs/
void dag(Graph& g, int s){
	list<int> L = g.TopoSort();

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

	int s = 1;
	cout << "Following are shortest distances from source " << s << " n";
	

	return 0;
}