#include <cstdlib>

class Vertex{
    public:
        Edge addNeighbour(Vertex*);
        void sss();
        unsigned int getId();
        void printVertex();
        void printEdges();
        Vertex();
        Vertex(int);
        ~Vertex();
    private:
        unsigned int id;
        std::vector <Edge> edges;
        std::vector <Vertex*> neighbours;
    protected:
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

void Vertex::sss(){
    std::cout << "vertex things" << std::endl;
}

Edge Vertex::addNeighbour(Vertex *n){
    Edge e = makeEdge(n);
    edges.push_back(e);
    neighbours.push_back(n);
}

Edge Vertex::makeEdge(Vertex *p){
    Edge e;
    e.weight = rand() % 255;
    e.to = p;  
    return e;
}

void Vertex::printVertex(){
    std::cout << "Vertex::" << id << " has Edges" << std::endl;
    printEdges();
}

void Vertex::printEdges(){
    for(auto i : edges){
        std::cout << i.weight << " => " << i.to -> getId() << std::endl;
    }
}