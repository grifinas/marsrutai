#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <map>
#include <stdexcept>
#include <chrono>

struct Edge;
using namespace std;

#include "graph.cpp"
#include "utils.cpp"
#include "nearest_neighbour.cpp"
#include "ant_colony.cpp"

int main(){
    Graph gg;

    gg++; 
    gg++; 
    gg++; 
    gg++; 
    
    gg.vertexLink(1, 2);
    gg.vertexLink(2, 3);
    gg.vertexLink(4, 1);
    gg.vertexLink(4, 2);

    vector<Vertex*> nn = nearestNeighbour(gg[4]);
    printPath(nn, "nn ", false);
    gg.GAStar(1, 3);
    printPath(nn, "a* ");
    
    gg.printGraph();

    cout << "done" << endl;
    return 0;
}