#include "astar.hpp"

Tour aStar(Vertex* begin, Vertex* goal, bool makeVirtualEdge){
    Tour result;

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
                Tour reconstructedPath = aStarReconstructPath(cameFrom, current);
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
            if(open.find(vertPtr) == open.end()){
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
    if(vert == goal){
        return 0;
    }
    int lowInt = -1;
    for(auto const& i : goal->getNeighbours()){
        if(i.first -> hasEdgeTo(goal)){
            Edge e = i.first -> getNeighbour(goal);
            if(e.weight < lowInt || lowInt < 0){
                lowInt = e.weight;
            }
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
        if(score < lowInt || lowInt < 0){
            lowest = i.first;
            lowInt = score;
        }
    }
    return lowest;
}

Tour aStarReconstructPath(std::map<Vertex*, Vertex*> cameFrom, Vertex* current){
    Tour totalPath;
    totalPath.push_back(current);
    while(cameFrom.find(current) != cameFrom.end()){
        current = cameFrom[current];
        totalPath.insert(totalPath.begin(), current);
    }
    return totalPath;
}

int aStarGetTotalPathWeight(Tour totalPath, bool force_eval){
    int pathWeight = 0;
    int ps = totalPath.size()-1;
    for(int i=0; i<ps; i++){ 
        bool hasEdgeTo = totalPath[i] -> hasEdgeTo(totalPath[i+1]);
        if(!hasEdgeTo && force_eval && totalPath[i] -> getId() != totalPath[i+1] -> getId()){
            Tour p = aStar(totalPath[i], totalPath[i+1], 1);
            hasEdgeTo = totalPath[i] -> hasEdgeTo(totalPath[i+1]);
        }
        if(hasEdgeTo){
            Edge e = totalPath[i] -> getNeighbour(totalPath[i+1]);
            pathWeight += e.weight;
        }
    }
    return pathWeight;
}

Tour aStarGetPathToClosestOf(Vertex* start, std::map<Vertex*, int> vertices){
    Tour finalPath, currentPath;
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

void aStarRoute(Tour &soFar, Vertex* start, Vertex* goal, bool skipFirst = true){
    Tour route = aStar(start, goal);
    std::cout << start -> getId() << " route to " << goal -> getId() << std::endl;
    //skip initial node of start

    for(int i=skipFirst?1:0; i<route.size(); i++){
        soFar.push_back(route[i]);
    }
}