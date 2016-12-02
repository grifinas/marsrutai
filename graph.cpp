#include "vertex.cpp"

class Graph{
    public:
        static unsigned int vertexCount;

        int addVertex();
        bool vertexLink(int, int);
        Vertex* getVertex(int);
        void printGraph();
        std::vector<Vertex*> aStar(int, int);
    private:
        std::map <int, Vertex*> vertices;
        int aStarHeuristicCost(Vertex*, Vertex*);
        Vertex* getAStarSmallestVertex(std::map<Vertex*, int>);
        std::vector<Vertex*> aStarReconstructPath(std::map<Vertex*, Vertex*>, Vertex*);
};

#include "astar.cpp"

unsigned int Graph::vertexCount = 0;

int Graph::addVertex(){
     int vert_id = ++vertexCount;
     Vertex *v = new Vertex(vert_id);
     vertices[vert_id] = v;
     return vert_id;
}

Vertex* Graph::getVertex(int id){
    try{ 
        return vertices[id]; 
    }catch(std::out_of_range){
        return new Vertex();
    }
}

bool Graph::vertexLink(int v_id1, int v_id2){
    Vertex *v1ptr, *v2ptr;
    try{
        v1ptr = vertices.at(v_id1);
        v2ptr = vertices.at(v_id2);
    }catch(std::out_of_range){
        std::cout << "unable to link vertices, " << v_id1 << " & " << v_id2 << std::endl; 
        return false;
    }

    v1ptr -> addNeighbour(v2ptr);
    v2ptr -> addNeighbour(v1ptr);

    return true;
}

void Graph::printGraph(){
    for(auto const& v : vertices){
        // std::cout << "@:" << v.first << " ";
        v.second -> printVertex();
    }
}

