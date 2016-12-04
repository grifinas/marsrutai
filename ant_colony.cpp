/****RULES*****

    1. It must visit each city exactly once;
    2. A distant city has less chance of being chosen (the visibility);
    3. The more intense the pheromone trail laid out on an edge between two cities, the greater the probability that that edge will be chosen;
    4. Having completed its journey, the ant deposits more pheromones on all edges it traversed, if the journey is short;
    5. After each iteration, trails of pheromones evaporate.

*/

struct PheromonedEdge{
    int pheromones;
    int weight;
    Vertex* to;
    float eta;      //desirability
    inline void operator<<(Edge e){
        weight = e.weight;
        to = e.to;
        eta = 1/weight;
    }
};

std::vector<Vertex*> AntColonyOptimization(Vertex* start){
    std::map<Vertex*, std::map<Vertex*, PheromonedEdge>> trail;
    float alpha, beta;      //pheromone and desirability modifiers

    //TODO WHAT IS SUM z partof allowed(z) at https://en.wikipedia.org/wiki/Ant_colony_optimization_algorithms#Edge_selection

    
}