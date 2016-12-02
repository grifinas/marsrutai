std::vector(Vertex*) nearestNeighbour(Vertex* start){
    std::map<Vertex*, int> visited;
    Vertex* current = start;

    while(!visited[current]){
        visited[current] = 1;
        Edge e = current -> getSmallestNeighbouringEdge();
        current = e.to; 
    }
}