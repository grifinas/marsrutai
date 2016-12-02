std::vector<Vertex*> Graph::aStar(int start, int end){
    std::vector<Vertex*> result;

    Vertex *begin = getVertex(start);
    Vertex *goal = getVertex(end);

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
        current = getAStarSmallestVertex(fScore);
        if(current == goal){
            //solved
            return aStarReconstructPath(cameFrom, current);
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
int Graph::aStarHeuristicCost(Vertex* vert, Vertex* goal){
    int lowInt = -1;
    for(auto const& i : goal->getNeighbours()){
        Edge e = i.first -> getNeighbour(goal);
        if(e.weight < lowInt || lowInt < 0){
            lowInt = e.weight;
        }
    }
    return lowInt;
}

Vertex* Graph::getAStarSmallestVertex(std::map<Vertex*, int> fScore){
    Vertex* lowest;
    int lowInt = -1;
    for(auto const& i : fScore){
        if(i.second > lowInt || lowInt < 0){
            lowest = i.first;
            lowInt = i.second;
        }
    }
    return lowest;
}

std::vector<Vertex*> Graph::aStarReconstructPath(std::map<Vertex*, Vertex*> cameFrom, Vertex* current){
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
        std::cout << totalPath[i] -> getId() << " -> " << totalPath[i+1] -> getId(); 
        Edge e = totalPath[i] -> getNeighbour(totalPath[i+1]);
        std::cout << " = " << e.weight << std::endl;
        pathWeight += e.weight;
    }
    return pathWeight;
}