#include <cstdlib>

class Vertex{
    public:
        Edge addNeighbour(Vertex*);
        unsigned int getId();
        std::map <Vertex*, Edge> getNeighbours();
        Edge getNeighbour(Vertex*);
        Edge getSmallestNeighbouringEdge(std::map<Vertex*, int>);
        void printVertex();
        void printEdges();
        Vertex();
        Vertex(int);
        ~Vertex();
    private:
        unsigned int id;
        // std::vector <Edge> edges;
        // std::vector <Vertex*> neighbours;
        std::map <Vertex*, Edge> neighbours;
        Edge makeEdge(Vertex*);
};

struct Edge{
    Vertex* to;
    unsigned int weight;
};

unsigned int Vertex::getId(){ return id; }

Vertex::Vertex(){
    id = 0;
}

Vertex::Vertex(int vert_id){
    id = vert_id;
}

Vertex::~Vertex(){
    std::cout << "Vertex::" << id << "has been destroyed" << std::endl;
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
        std::cout << e.weight << " => " << e.to -> getId() << std::endl;
    }
}

std::map <Vertex*, Edge> Vertex::getNeighbours(){
    return neighbours;
}

Edge Vertex::getNeighbour(Vertex* v){
    Edge e;
    try{
        e = neighbours.at(v);
    }catch(std::out_of_range){
        std::cout << "Vertex::getNeighbour unable to get neighbour at position " << v << std::endl;
        throw std::out_of_range("no such vertex");
    }
    
    return e;
}

Edge Vertex::getSmallestNeighbouringEdge(std::map<Vertex*, int> visited){
    Edge lowEdge;
    lowEdge.weight = -1;
    int count = 0;
    for(auto const& i : getNeighbours()){
        //safeguard so new Edge with a `to` to random memory wouldn't return
        if(visited[i.first] && (++count < neighbours.size() || lowEdge.weight != -1)){
            continue;
        }
        Edge e = i.second;
        if(e.weight < lowEdge.weight || lowEdge.weight < 0){
            lowEdge = e;
        }
    }

    if(lowEdge.weight == -1){
        throw std::runtime_error("invalid edge structure generated");
    }

    return lowEdge;
}