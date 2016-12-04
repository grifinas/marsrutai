std::vector<Vertex*> aStar(Vertex*, Vertex*, bool makeVirtualEdge = true);
int aStarHeuristicCost(Vertex*, Vertex*);
Vertex* getAStarSmallestVertex(std::map<Vertex*, int>, std::map<Vertex*, int>);
std::vector<Vertex*> aStarReconstructPath(std::map<Vertex*, Vertex*>, Vertex*);
int aStarGetTotalPathWeight(std::vector<Vertex*>);
std::vector<Vertex*> aStarGetPathToClosestOf(Vertex*, std::map<Vertex*, int>);

std::vector<Vertex*> aStar(Vertex* begin, Vertex* goal, bool makeVirtualEdge){
    std::vector<Vertex*> result;

    // Vertex *begin = getVertex(start);
    // Vertex *goal = getVertex(end);

    std::map<Vertex*, int> closed;
    std::map<Vertex*, int> open;
    std::map<Vertex*, Vertex*> cameFrom;
    open[begin] = 1;

    Vertex *current;
    std::map<Vertex*, int> gScore;
    std::map<Vertex*, int> fScore;

    int tentative_gScore;

    gScore[begin] = 0;
    fScore[begin] = aStarHeuristicCost(begin, goal);

    while(open.size() > 0){
        current = getAStarSmallestVertex(open, fScore);
        if(current == goal){
            //solved
            if(makeVirtualEdge){
                std::vector<Vertex*> reconstructedPath = aStarReconstructPath(cameFrom, current);
                int w = aStarGetTotalPathWeight(reconstructedPath);
                begin -> makeVirtualEdge(goal, w);
                return reconstructedPath;
            }else{
                return aStarReconstructPath(cameFrom, current);
            }
        }

        open.erase(current);
        closed[current] = 1;
        for(auto const& neighbour : current -> getNeighbours()){
            Vertex *vertPtr = neighbour.first;
            Edge e = neighbour.second;
            if(closed[vertPtr]){
                continue;
            }

            tentative_gScore = gScore[current] + e.weight;
            if(!open[vertPtr]){
                open[vertPtr] = 1;
            }else if(tentative_gScore >= gScore[vertPtr]){
                continue;
            }
            
            cameFrom[vertPtr] = current;
            gScore[vertPtr] = tentative_gScore;
            fScore[vertPtr] = tentative_gScore + aStarHeuristicCost(vertPtr, goal);
        }

    }
    //empty vector
    return result;
}


/*
    TODO write an actuall heuristic aproach?
    currently the cost is the smallest weight of all edges to goal
*/
int aStarHeuristicCost(Vertex* vert, Vertex* goal){
    int lowInt = -1;
    for(auto const& i : goal->getNeighbours()){
        Edge e = i.first -> getNeighbour(goal);
        if(e.weight < lowInt || lowInt < 0){
            lowInt = e.weight;
        }
    }
    return lowInt;
}

Vertex* getAStarSmallestVertex(std::map<Vertex*, int> open, std::map<Vertex*, int> fScore){
    Vertex* lowest;
    int lowInt = -1;
    int score;
    for(auto const& i : open){
        score = fScore[i.first];
        if(score > lowInt || lowInt < 0){
            lowest = i.first;
            lowInt = score;
        }
    }
    return lowest;
}

std::vector<Vertex*> aStarReconstructPath(std::map<Vertex*, Vertex*> cameFrom, Vertex* current){
    std::vector<Vertex*> totalPath;
    totalPath.push_back(current);
    while(cameFrom[current]){
        current = cameFrom[current];
        totalPath.insert(totalPath.begin(), current);
    }
    return totalPath;
}

int aStarGetTotalPathWeight(std::vector<Vertex*> totalPath){
    int pathWeight = 0;
    for(int i=0; i<totalPath.size()-1; i++){ 
        try{
            Edge e = totalPath[i] -> getNeighbour(totalPath[i+1]);
            pathWeight += e.weight;
        }catch(...){
            continue;
        }
    }
    return pathWeight;
}

std::vector<Vertex*> aStarGetPathToClosestOf(Vertex* start, std::map<Vertex*, int> vertices){
    std::vector<Vertex*> finalPath, currentPath;
    int finalWeight = -1;
    int weight;
    for(auto const& i : vertices){
        currentPath = aStar(start, i.first);
        weight = aStarGetTotalPathWeight(currentPath);
        if(weight < finalWeight || finalWeight == -1){
            finalWeight = weight;
            finalPath = currentPath;
        }
    }

    return finalPath;
}