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

    gg++; 
    gg++; 
    gg++; 
    gg++; 
    
    gg.vertexLink(1, 2);
    gg.vertexLink(2, 3);
    gg.vertexLink(4, 1);

    Vertex *v = gg[1];

    cout << v -> getId() << endl;

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