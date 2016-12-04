/****RULES*****

    1. find V - closest unvisited vertex to current
    2. mark current as visited
    3. assign current to V
    4. if Exists unvisited V, goto 1

*/

std::vector<Vertex*> nearestNeighbour(Vertex* start){
    std::map<Vertex*, int> visited;
    std::map<Vertex*, int> unVisited;
    std::vector<Vertex*> result;
    Vertex* current = start;
    Edge e;

    while(!visited[current]){
        result.push_back(current);
        visited[current] = 1;
        unVisited.erase(current);
        try{
            e = current -> getSmallestNeighbouringEdge(visited, unVisited);
            current = e.to; 
        }catch(std::runtime_error){
            //ran into a corner
            if(unVisited.size() > 0){
                std::vector<Vertex*> pathToUnvisited = aStarGetPathToClosestOf(current, unVisited);
                //skip current
                for(int i=1; i< pathToUnvisited.size(); i++){
                    result.push_back(pathToUnvisited[i]);
                }
                current = pathToUnvisited[pathToUnvisited.size()-1];
            }
        }
    }
    return result;
}