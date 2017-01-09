#include "vertex.hpp"

unsigned int Vertex::getId(){ return id; }

Vertex::Vertex(){
    id = 0;
    node_id = "";
    isEnabled = true;
}

Vertex::Vertex(int vert_id){
    id = vert_id;
    node_id = "";
    isEnabled = true;
}

Vertex::Vertex(int vert_id, const char* nid){
    node_id = nid;
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


void Vertex::setLat(float a){lat = a;}
void Vertex::setLng(float a){lng = a;}
void Vertex::setId(unsigned int a){id = a;}
void Vertex::setNodeId(const char* a){node_id = a;}

Edge Vertex::addNeighbour(Vertex *n){
    n -> newNeighboured(this);
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
    std::cout << "Vertex::" << id << " " << node_id << " ";
    if(neighbours.size() < 1){
        std::cout << "is unconnected";
    }else{
        std::cout << "has Edges";
    }
    std::cout << std::endl;
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
    }catch(...){
        std::cout << "Vertex::getNeighbour vertex id: " << id << " is unable to get neighbour at position " << v << std::endl;
        try{
            std::cout << "Vertex id: " << v -> getId() << std::endl;
        }catch(...){}
    }
    return e;
}

void Vertex::newNeighboured(Vertex* v){ isNeighbouredBy.push_back(v);    }
Tour Vertex::getNeighbouredVertices(){  return isNeighbouredBy; }

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

std::ostream& operator<<(std::ostream& os, Vertex *V){
    os << "Vertex:" << V->getId() << " ";
    return os;
}

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