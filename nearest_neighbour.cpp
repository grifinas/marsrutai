/****RULES*****

    1. find V - closest unvisited vertex to current
    2. mark current as visited
    3. assign current to V
    4. if Exists unvisited V, goto 1

*/

Tour nearestNeighbour(Graph &gg, int start, int depth = 0){
    std::map<Vertex*, int> visited;
    std::map<Vertex*, int> unVisited;
    Tour result;
    Vertex* current = gg[start];
    Edge e;

    while(!visited[current] || unVisited.size() > 0){
        result.push_back(current);
        visited[current] = 1;
        unVisited.erase(current);
        e = current -> getSmallestNeighbouringEdge(visited, unVisited, depth);
        if(e.to != nullptr){
            current = e.to; 
        }else{
            //ran into a corner
            if(unVisited.size() > 0){
                Tour pathToUnvisited = aStarGetPathToClosestOf(current, unVisited);
                //skip current
                for(int i=1; i< pathToUnvisited.size(); i++){
                    result.push_back(pathToUnvisited[i]);
                    visited[pathToUnvisited[i]] = 1;
                    unVisited.erase(pathToUnvisited[i]);
                }
                current = pathToUnvisited[pathToUnvisited.size()-1];
            }
        }
    }
    return result;
}