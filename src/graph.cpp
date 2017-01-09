#include "graph.hpp"

Graph::Graph(){
    vertexCount = 0;
}

Graph::Graph(tinyxml2::XMLElement* root){
    vertexCount = 0;
    tinyxml2::XMLElement* Node = root -> FirstChildElement( "node" );
    while(Node){
        Vertex* v= new Vertex();
        v -> setNodeId(Node -> Attribute("id"));
        
        std::string float_string;
        const char* atr;
        if(atr = Node -> Attribute("lat")){
            float_string = atr;
            v -> setLat(std::stof(float_string));
        }else{
            std::cout << "Node without lat" << std::endl;
        }
        if(atr = Node -> Attribute("lon")){
            float_string = atr;
            v -> setLng(std::stof(float_string));
        }else{
            std::cout << "Node without lon" << std::endl;
        }
        long node_id = std::atol(Node -> Attribute("id"));
        addVertex(v, node_id);
        Node = Node -> NextSiblingElement("node");
    }
    Node = root -> FirstChildElement( "way" );
    while(Node){
        bool isOneWay = false;
        tinyxml2::XMLElement* nd = Node -> FirstChildElement( "nd" );
        int prievVertexId = 0;
        while(nd){
            long node_id = std::atol(nd -> Attribute("ref"));
            Vertex* v = getVertexByNode(node_id);
            if(v){
                if(prievVertexId > 0){
                    if(!isOneWay){
                        vertexLinkBoth(prievVertexId, v->getId());
                    }else{
                        std::cout << "one way road between " << prievVertexId << " n " << v << std::endl;
                        vertexLink(prievVertexId, v->getId());
                    }
                }
                prievVertexId = v->getId();
            }
            nd = nd -> NextSiblingElement("nd");
        }
        Node = Node -> NextSiblingElement("way");
    }
}

Graph::~Graph(){
    std::cout << "killed a graph" << std::endl;
    for(int i=0; i<vertices.size(); i++){
        delete vertices[i];
    }
}

void Graph::setGlobals(){
    for(int i=1; i<=vertexCount; i++){
        for( auto const &n : vertices[i] -> getNeighbours()){
            if(n.second.weight > ::longest_edge){
                ::longest_edge = n.second.weight;
            }
        }
    }
}

int Graph::size(){
    return vertexCount;
}

int Graph::addVertex(){
     int vert_id = ++vertexCount;
     Vertex *v = new Vertex(vert_id);
     vertices[vert_id] = v;
     return vert_id;
}

int Graph::addVertex(Vertex* v, long node){
    int vert_id = ++vertexCount;
    v -> setId(vert_id);
    if(node){
        NodeToVertex[node] = vert_id;
    }
    vertices[vert_id] = v;
    return vert_id;
}

Vertex* Graph::getVertex(int id){
    try{ 
        return vertices[id]; 
    }catch(std::out_of_range){
        return nullptr;
    }
}

Vertex* Graph::getVertexByNode(long c){
    if(NodeToVertex.find(c) != NodeToVertex.end()){
        int i = NodeToVertex[c];
        return getVertex(i);
    }
    return nullptr;
}

bool Graph::vertexLinkBoth(int v_id1, int v_id2){
    vertexLink(v_id1, v_id2);
    vertexLink(v_id2, v_id1);
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

    return true;
}

void Graph::printGraph(){
    if(vertices.size() == 0){
        return;
    }
    for(auto const& v : vertices){
        // std::cout << v.first << std::endl;
        // std::cout << "@:" << v.first << " ";
        v.second -> printVertex();
    }
}

Tour Graph::GAStar(int start, int end){
    Vertex *begin = getVertex(start);
    Vertex *goal = getVertex(end);
    return aStar(begin, goal);
}

Tour Graph::findVerticesWithEdgeTo(Vertex* needle){
    Tour result;
    for(auto const &i : vertices){
        if(i.second -> hasEdgeTo(needle)){
            result.push_back(i.second);
        }
    }
    return result;
}

Vertex* Graph::operator[](const int id){
    return getVertex(id);
}

Vertex* Graph::operator++(const int irrelevant){
    addVertex();
    return getVertex(vertexCount);
}