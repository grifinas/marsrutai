#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <map>
#include <stdexcept>

struct Edge;

#include "graph.cpp"

using namespace std;

int main(){
    Graph gg;

    int id = gg.addVertex(); 
    id = gg.addVertex(); 
    id = gg.addVertex(); 
    id = gg.addVertex(); 
    
    gg.vertexLink(1, 2);
    gg.vertexLink(2, 3);
    gg.vertexLink(4, 1);

    Vertex *v = gg.getVertex(1);

    map<Vertex*, int> visited;

/*
    Vertex *vis = gg.getVertex(4);
    visited[vis] = 1;
    vis = gg.getVertex(2);
    visited[vis] = 1;


    Edge e = v -> getSmallestNeighbouringEdge(visited);

    cout << e.to << "  " << e.weight << endl; 
*/

    // Vertex *fake = new Vertex();

    // Edge e = v -> getNeighbour(fake);

    // cout << e.to << ":" << e.weight << endl;

    gg.printGraph();

    // std::vector<Vertex*> path = gg.aStar(0, 2);
    // cout << "path weight = " << aStarGetTotalPathWeight(path) << endl;

    cout << "done" << endl;

    return 0;
}