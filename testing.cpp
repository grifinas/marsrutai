#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <map>
#include <stdexcept>
#include <chrono>
#include <random>
#include <math.h>

struct Edge;
using namespace std;

#include "header.cpp"
#include "utils.cpp"

#include "vertex.cpp"
#include "astar.cpp"
#include "graph.cpp"

#include "nearest_neighbour.cpp"
#include "ant_colony.cpp"
// #include "match_twice_and_stich.cpp"
#include "2-opt.cpp"
#include "branch_and_bound.cpp"
// #include "genetic.cpp"
#include "simulated_anealing.cpp"

int main(int argc, char *argv[]){
    int vertice_count = 10;
    int vertice_cap = 300;
    if(argc >= 2){
        vertice_count = std::stoi(argv[1]);
        std::cout << "starting from: " << vertice_count << std::endl;
    }

    timestamp();
    for(int count = vertice_count; count < vertice_cap;){
        int max_count = count+10;
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

            nn = SimulatedAnealing(*gg, 1, nn);
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