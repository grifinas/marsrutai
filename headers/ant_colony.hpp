#ifndef ant_colony_H
#define ant_colony_H

#include "vertex.hpp"
#include "graph.hpp"

#include "my_globals.hpp"


struct PheromonedEdge;
struct Ant;
bool isComplete(Ant a);
void putPheromones(Graph &gg, std::vector<Ant> &Ants, std::map<Vertex*, std::map<Vertex*, PheromonedEdge>> &trail);
Tour AntColonyOptimization(Graph &gg, int start, int traversalTimes = 1, int antCount = 0);
void putPheromones(Graph &gg, std::vector<Ant> &Ants, std::map<Vertex*, std::map<Vertex*, PheromonedEdge>> &trail);
bool isComplete(Ant a);
std::ostream& operator<<(std::ostream& os, const Ant &ant);
std::ostream& operator<<(std::ostream& os, const PheromonedEdge pe);
#endif