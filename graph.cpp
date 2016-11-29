#include "vertex.cpp"

class Graph{
    public:
        // Vertex vertices;
        static unsigned int vertexCount;

        int addVertex();
        bool vertexLink(int, int);
        int test();
        Vertex getVertex(int);
        void printGraph();
    private:
        std::vector <Vertex*> vertices;
};
unsigned int Graph::vertexCount = 0;

int Graph::addVertex(){
     int vert_id = ++vertexCount;
     Vertex *v = new Vertex(vert_id);
     vertices.push_back(v);
     return vert_id;
}

Vertex Graph::getVertex(int id){
    try{ 
        return *vertices.at(id); 
    }catch(std::out_of_range){
        return Vertex();
    }
}

int Graph::test(){
    return (int)vertexCount;
}

bool Graph::vertexLink(int v_id1, int v_id2){
    Vertex *v1ptr, *v2ptr;
    try{
        v1ptr = vertices.at(v_id1);
        v2ptr = vertices.at(v_id2);
    }catch(std::out_of_range){
        return false;
    }

    v1ptr -> addNeighbour(v2ptr);
    v2ptr -> addNeighbour(v1ptr);

    return true;
}

void Graph::printGraph(){
    for(auto const &i : vertices){
        i -> printVertex();
    }
}