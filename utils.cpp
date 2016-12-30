void printPath(Tour ll, string name = "", bool showSize = true){
    int w;
    cout << name;
    for(int i=0; i<ll.size(); i++){
        cout << ll[i] -> getId() << " ==";
        if(showSize && i < ll.size()-1){
            if(ll[i] -> hasEdgeTo(ll[i+1])){
                Edge e = ll[i] -> getNeighbour(ll[i+1]);
                w = e.weight;
                cout << "(" << w << ")";
            }
        }
        cout << ">> ";
    }
    cout << "total path weight: " << aStarGetTotalPathWeight(ll) << endl;
}

void printMap(std::map<Vertex*, auto> map, string name = ""){
    cout << "===" << name << "===" << endl;
    for(auto const& i : map){
        cout << "[id:" << i.first -> getId() << "] = " << i.second << endl; 
    }
    cout << endl;
}

void printVector(std::vector<auto> v){
    for(int i=0; i<v.size(); i++){
        std::cout << "[" << i << "]" << " => " << v[i] << std::endl;
    }
}

void timestamp(bool renew = false){
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

bool isAt(std::map<auto, auto> M, auto key){
    try{
        M.at(key);
        return true;
    }catch(...){
        return false;
    }
}

Graph* generateRandomGraph(int v_count = 0, int link_count = 10){
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
            gg -> vertexLink(i, rnd);
        }
    }

    return gg;
}

void exportGraphToCSV(Graph &gg, string name = ""){
    ofstream vert_file, edge_file;
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

std::ostream& recursiveMapPrint(std::ostream& os, const auto not_map, int recurse = 1){
    std::string tabulation;
    for(int i=0; i<recurse; i++){
        tabulation += "\t";
    }
    os << tabulation << not_map;
    return os;
}

std::ostream& recursiveMapPrint(std::ostream& os, const std::map<auto, auto> &M, int recurse = 0){
    std::string tabulation;
    for(int i=0; i<recurse; i++){
        tabulation += "\t";
    }
    for(auto const &i : M){
        os << tabulation << "[" << i.first << "] => \r\n";
        recursiveMapPrint(os, i.second, recurse+1);
        os << "\r\n";
    }
    return os;
}

std::ostream& operator<<(std::ostream& os, const std::map<auto, auto> &M){
    recursiveMapPrint(os, M);
    // for(auto const &i : M){
    //     os << "[" << i.first << "]" << " => \r\n\t" << i.second << "\r\n";
    // }
    return os;
}

std::ostream& operator<<(std::ostream& os, const std::vector<auto> &V){
    for(int i=0; i<V.size(); i++){
        os << "[" << i << "]" << " => \r\n\t" << V[i] << std::endl; 
    }
    return os;
}

std::ostream& operator<<(std::ostream& os, Vertex *V){
    os << "Vertex:" << V->getId() << " ";
    return os;
}