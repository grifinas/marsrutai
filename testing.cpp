#include <iostream>
#include <vector>
#include <string>
#include <fstream>

struct Edge;

#include "graph.cpp"

using namespace std;

int main(){
    Graph gg;


    int id = gg.addVertex(); 
    id = gg.addVertex(); 
    id = gg.addVertex(); 
    id = gg.addVertex(); 

    cout << "1 " << id << endl;
    
    Vertex v = gg.getVertex(id);
    
    gg.vertexLink(0, 1);
    gg.vertexLink(1, 2);


    v.sss();

    gg.printGraph();


    cout << "done" << endl;
    return 0;
}