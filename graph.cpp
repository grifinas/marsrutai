Graph::Graph(){
    vertexCount = 0;
}

Graph::~Graph(){
    std::cout << "killed a graph" << std::endl;
    for(int i=0; i<vertices.size(); i++){
        delete vertices[i];
    }
}

int Graph::size(){
    return vertexCount;
}

Vertex* Graph::operator[](const int id){
    return getVertex(id);
}

Vertex* Graph::operator++(const int irrelevant){
    addVertex();
    return getVertex(vertexCount);
}

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