#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <stdexcept>
#include <random>

using namespace std;

#include "utils.hpp"
#include "vertex.hpp"
#include "astar.hpp"
#include "graph.hpp"

#include "nearest_neighbour.hpp"
#include "ant_colony.hpp"
#include "branch_and_bound.hpp"
#include "simulated_anealing.hpp"

void setGlobals(Graph* gg){
    gg -> setGlobals();
    ::start_vertex = gg -> getVertex(1);
    Node *root = new Node();
    root -> calcLowerBound();
    ::lower_bound = root -> getLB();
    delete root;
}

// #include <QGuiApplication>
// #include <QQmlApplicationEngine>

int main(int argc, char *argv[]){
    timestamp();
    Tour nn;
    Graph* gg;
    srand(time(NULL));


    current_count = 5;
    max_edges = 5;
    gg = generateRandomGraph(current_count, max_edges);
    cout << "to generate"; timestamp(true);
    setGlobals(gg);

    nn = BnB(*gg);
    printPath(nn, "BnB ");

    gg -> printGraph();
    delete gg;
    return 0;
    tinyxml2::XMLDocument doc;
    doc.LoadFile( "test.xml" );
    gg = new Graph(doc.RootElement());
    cout << "to generate"; timestamp(true);
    gg -> printGraph();
    cout << "to print"; timestamp(true);
    nn = AntColonyOptimization(*gg, 1, 20, 7);

    cout << "to colonise"; timestamp(true);
    printPath(nn, "ants ");

    delete gg;
    return 0;


    double minlat=54.6769, minlon=25.2823, maxlat=54.6797, maxlon=25.2898;
    int zoom = 16;
    int xfrom, xto, yfrom, yto;
    xfrom = long2tilex(minlon, zoom);
    xto = long2tilex(maxlon, zoom);
    yfrom = lat2tiley(minlat, zoom);
    yto = lat2tiley(maxlat, zoom);

    if(xfrom > xto) swap(xfrom, xto);
    if(yfrom > yto) swap(yfrom, yto);

    auto def = "http://a.tile.openstreetmap.org";

    cout << xfrom << " " << xto << " " << yfrom << " " << yto << std::endl;

    for(int i=xfrom; i<=xto; i++){
        for(int j=yfrom; j<=yto; j++){
            std::cout << def << "/" << zoom << "/" << i << "/" << j << ".png" << std::endl;
        }
    }

    return 0;




    int vertice_count = 10;
    int vertice_cap = 300;
    int vertice_increment = 25;
    if(argc >= 2){
        vertice_count = std::stoi(argv[1]);
        std::cout << "starting from: " << vertice_count << std::endl;
    }

    timestamp();
    for(int count = vertice_count; count < vertice_cap;){
        int max_count = count + vertice_increment;
        for(current_count = count; count < max_count; count++){
            srand(time(NULL));
            float ratio = (float)(count - current_count)/10;
            max_edges = current_count * (ratio + 0.1);
            std::string graph_name = "graph_" + std::to_string(current_count) + "_" + std::to_string(max_edges) + "_";

            std::cout << "current graph: " << graph_name << std::endl;

            Graph *gg = generateRandomGraph(current_count, max_edges);
            // gg.printGraph();
            cout << "to generate"; timestamp(true);

            exportGraphToCSV(*gg, graph_name);
            cout << "to export"; timestamp(true);

            Tour nn;

            nn = AntColonyOptimization(*gg, 1, 10, 5);
            cout << "to colonise"; timestamp(true);
            printPath(nn, "ants ");

            nn = nearestNeighbour(*gg, 1);
            cout << "to nn"; timestamp(true);
            printPath(nn, "nn ");

            nn = SimulatedAnealing(*gg, nn);
            cout << "to sa"; timestamp(true);
            printPath(nn, "sa ");

            nn = nearestNeighbour(*gg, 1, 1);
            cout << "to nnn"; timestamp(true);
            printPath(nn, "nnn ");

            delete gg;
        }
    }

    // gg++; 
    // gg++; 
    // gg++; 
    // gg++; 
    
    // gg.vertexLink(1, 2);
    // gg.vertexLink(2, 3);
    // gg.vertexLink(4, 1);
    // gg.vertexLink(4, 2);


    // BnB(gg, 1);

    // GeneticAlgorithm(gg, 1, nn);


    // nn = DFBranchAndBound(gg, gg[1], gg[4]);
    // printPath(nn, "BnB ");
    // gg.GAStar(1, 3);
    // printPath(nn, "a* ");
    
    // gg.printGraph();

    std::cout << std::endl;
    cout << "done" << endl;
    return 0;
}
