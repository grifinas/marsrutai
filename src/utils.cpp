#include "utils.hpp"

void printPath(Tour ll, std::string name, bool showSize){
    int w;
    std::cout << name;
    for(int i=0; i<ll.size(); i++){
        std::cout << ll[i] -> getId() << " ==";
        if(showSize && i < ll.size()-1){
            if(ll[i] -> hasEdgeTo(ll[i+1])){
                Edge e = ll[i] -> getNeighbour(ll[i+1]);
                w = e.weight;
                std::cout << "(" << w << ")";
            }
        }
        std::cout << ">> ";
    }
    std::cout << "total path weight: " << aStarGetTotalPathWeight(ll, true) << std::endl;
}

void printMap(std::map<Vertex*, auto> map, std::string name){
    std::cout << "===" << name << "===" << std::endl;
    for(auto const& i : map){
        std::cout << "[id:" << i.first -> getId() << "] = " << i.second << std::endl; 
    }
    std::cout << std::endl;
}

void printVector(std::vector<auto> v){
    for(int i=0; i<v.size(); i++){
        std::cout << "[" << i << "]" << " => " << v[i] << std::endl;
    }
}

void timestamp(bool renew){
    static int timesTimeStamped = 0;
    auto now = std::chrono::high_resolution_clock::now(); 
    static auto t_start = now;
    if(timesTimeStamped > 0){ 
        std::cout << " " << std::chrono::duration<double, std::milli>(now-t_start).count() << " ms" << std::endl;
        if(renew){
            t_start = now;
        }
    }
    ++timesTimeStamped;
}

Graph* generateRandomGraph(int v_count, int link_count){
    Graph *gg = new Graph();
    if(v_count == 0){
        v_count = std::rand()%255;
    }
    //create vertices
    for(int i=0; i<v_count; i++){
        gg -> addVertex();
    }

    int rnd;
    for(int i=1; i<=v_count; i++){
        for(int j=0; j<std::rand()%link_count+1; j++){
            rnd = std::rand()%v_count+1;
            while(rnd == i){
                rnd = std::rand()%v_count+1;
            }
            gg -> vertexLinkBoth(i, rnd);
        }
    }

    return gg;
}

void exportGraphToCSV(Graph &gg, std::string name){
    std::ofstream vert_file, edge_file;
    int id;
    unsigned int edge_id = 0;

    vert_file.open (name + "_vertices.csv");
    edge_file.open (name + "_edges.csv");

    vert_file << "Id,Label\r\n";
    edge_file << "Source,Target,Type,Id,Weight\r\n";
    for(int i=1; i<=gg.size(); i++){
        id = gg[i] -> getId();
        vert_file << id << ", " << "v" << id << "\r\n";
        for(auto const& n : gg[i] -> getNeighbours()){
            edge_file << id << ", " << n.first -> getId() << ", Directed, " << ++edge_id << ", " << n.second.weight << "\r\n"; 
        }
    }
    vert_file.close();
    edge_file.close();
}

void swap(int &a, int &b){
    a += b;
    b = a - b;
    a -= b;
}

Tour twoOptSwap(Tour T, int from, int to){
    Vertex *tmp;
    if(from > to){
        swap(from, to);
    }
    for(from; from < to; from++, to--){
        tmp = T[from];
        T[from] = T[to];
        T[to] = tmp;
    }

    return T;
}