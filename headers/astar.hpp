#ifndef astar_H
#define astar_H

#include <iostream>
#include <vector>
#include <map>


#include "vertex.hpp"


Tour aStar(Vertex*, Vertex*, bool makeVirtualEdge = true);
int aStarHeuristicCost(Vertex*, Vertex*);
Vertex* getAStarSmallestVertex(std::map<Vertex*, int>, std::map<Vertex*, int>);
Tour aStarReconstructPath(std::map<Vertex*, Vertex*>, Vertex*);
int aStarGetTotalPathWeight(Tour, bool force_eval = false);
Tour aStarGetPathToClosestOf(Vertex*, std::map<Vertex*, int>);


#endif