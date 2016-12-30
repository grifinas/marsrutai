#include <cstdlib>

bool operator < (Edge e1, Edge e2){
    if(e1.weight < e2.weight){
        return true;
    }
    return false;
}

std::ostream& operator<<(std::ostream& os, const Edge &E){
    os << E.weight;
    if(E.isVirtual){
        os << "(v)"; 
    }
    os << " => " << E.to -> getId();
    return os;
}

unsigned int Vertex::getId(){ return id; }

Vertex::Vertex(){
    id = 0;
    isEnabled = true;
}

Vertex::Vertex(int vert_id){
    id = vert_id;
    isEnabled = true;
}

Vertex::~Vertex(){
    std::cout << "Vertex::" << id << " has been destroyed" << std::endl;
}

void Vertex::enable(){
    isEnabled = true;
}

void Vertex::disable(){
    isEnabled = false;
}


Edge Vertex::addNeighbour(Vertex *n){
    neighbours[n] = makeEdge(n); 
    return neighbours[n];
}

Edge Vertex::makeEdge(Vertex *p){
    Edge e;
    e.weight = (rand() % 255) + 1;
    e.to = p;  
    return e;
}

void Vertex::makeVirtualEdge(Vertex* to, int weight){
    Edge e;
    e.to = to;
    e.weight = weight;
    e.isVirtual = true;

    try{
        Edge oldEdge = neighbours.at(to);
        if(oldEdge.weight > e.weight){
            neighbours[to] = e;
        } 
    }catch(std::out_of_range){
        neighbours[to] = e;
    }
}

void Vertex::printVertex(){
    std::cout << "Vertex::" << id;
    std::string text;
    if(neighbours.size() < 1){
        text = "is unconnected";
    }else{
        text = "has Edges";
    }
    std::cout << " " << text << std::endl;
    printEdges();
}

void Vertex::printEdges(){
    for(auto const& neighbour : neighbours){
        Edge e = neighbour.second;
        std::cout << "\t" << e << std::endl;;
    }
}

std::map <Vertex*, Edge> Vertex::getNeighbours(){
    return neighbours;
}

bool Vertex::hasEdgeTo(Vertex* v){
    bool isNeigbour = false;
    try{
        Edge e = neighbours.at(v);
        isNeigbour = e.isEnabled;
    }catch(...){}
    return isNeigbour;
}

Edge Vertex::getNeighbour(Vertex* v){
    Edge e;
    try{
        e = neighbours.at(v);
    }catch(std::out_of_range){
        std::cout << "Vertex::getNeighbour vertex id: " << id << " is unable to get neighbour at position " << v << std::endl;
        try{
            std::cout << "Vertex id: " << v -> getId() << std::endl;
        }catch(...){}
        throw std::out_of_range("no such vertex");
    }
    
    return e;
}

Edge Vertex::getSmallestNeighbouringEdge(std::map<Vertex*, int> visited, std::map<Vertex*, int> &unVisited, int depth = 0){
    Edge lowEdge;
    int lowest_accumulated_weight = 0;
    for(auto const& i : getNeighbours()){
        int current_accumulated_weight = 0;
        if(visited[i.first] == 1 || i.second.isEnabled == false/* && (++count < neighbours.size() || lowEdge.weight != -1)*/){
            continue;
        }else{
            unVisited[i.first] = 1;
        }

        Vertex* current = i.first;
        current_accumulated_weight += i.second.weight;
        for(int deep=0; deep<depth; deep++){
            Edge e = current -> getSmallestNeighbouringEdge(visited, unVisited);
            if(e.to != nullptr){
                current = e.to;
                current_accumulated_weight += e.weight;
            }/*else if(deep == 0){    //if dead end try to backtrack
                if(current -> hasEdgeTo(i.first)){
                    e = current -> getNeighbour(i.first);
                    current = e.to;
                    current_accumulated_weight += e.weight;
                }
            }*/
        }

        if(current_accumulated_weight < lowest_accumulated_weight || lowest_accumulated_weight == 0){
            lowest_accumulated_weight = current_accumulated_weight;
            lowEdge = i.second;
        }
    }
    return lowEdge;
}

// Edge Vertex::getSmallestNeighbouringEdge(std::map<Vertex*, int> visited, std::map<Vertex*, int> &unVisited){
//     Edge lowEdge;
//     // int count = 0;
//     for(auto const& i : getNeighbours()){
//         //safeguard so new Edge with a `to` to random memory wouldn't return
//         if(visited[i.first] == 1 || i.second.isEnabled == false/* && (++count < neighbours.size() || lowEdge.weight != -1)*/){
//             continue;
//         }else{
//             unVisited[i.first] = 1;
//         }
//         Edge e = i.second;
//         if(e.weight < lowEdge.weight || lowEdge.weight == 0){
//             lowEdge = e;
//         }
//     }

//     return lowEdge;
// }

Edge Vertex::getSmallestNeighbouringEdge(std::map<Vertex*, int> visited){
    std::map<Vertex*, int> unVisited;
    return getSmallestNeighbouringEdge(visited, unVisited);
}

Edge Vertex::getSmallestNeighbouringEdge(){
    std::map<Vertex*, int> visited;
    return getSmallestNeighbouringEdge(visited);
}

int Vertex::countDoubleEdges(){
    int total = 0;
    for(auto const& i : getNeighbours()){
        if(i.first -> hasEdgeTo(this)){
            total++;
        }
    }
    return total;
}