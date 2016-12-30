/****RULES*****

    1. It must visit each city exactly once;
    2. A distant city has less chance of being chosen (the visibility);
    3. The more intense the pheromone trail laid out on an edge between two cities, the greater the probability that that edge will be chosen;
    4. Having completed its journey, the ant deposits more pheromones on all edges it traversed, if the journey is short;
    5. After each iteration, trails of pheromones evaporate.

*/

struct PheromonedEdge{
    float pheromones = 0;
    float eta = 0;      //desirability
    int weight = 0;
    Vertex* to;
    void operator<<(Edge e){
        weight = e.weight;
        to = e.to;
        eta = (float)100/e.weight;
    }
};

struct Ant{
    int ant_id;
    int current_id = 0;
    Vertex *current;
    std::map<Vertex*, int> visited;
    Tour visitedVector;
    void operator<<(Vertex* v){
        if(current_id == 0){
            ant_id = v -> getId();
        }else{
            // std::cout << "ant " << ant_id << " went to " << v -> getId() << std::endl;
            // printMap(visited, "visited by ant " + std::to_string(ant_id));
        }
        current = v;
        visited[v] += 1;
        visitedVector.push_back(v);
        current_id = v -> getId();
    }  
};

bool isComplete(const int vertCount, const Tour &T);
void putPheromones(Graph &gg, std::vector<Ant> &Ants, std::map<Vertex*, std::map<Vertex*, PheromonedEdge>> &trail);


std::ostream& operator<<(std::ostream& os, const Ant &ant){
    os << ant.ant_id << " c:" << ant.current -> getId() << " p:";
    for(int i = 0; i<ant.visitedVector.size(); i++){
        os << ant.visitedVector[i] -> getId() << " -> ";
    }  
    return os;  
}

std::ostream& operator<<(std::ostream& os, const PheromonedEdge pe){
    os << "p::" << pe.pheromones << " @" << pe.eta << " w" << pe.weight << " to " << pe.to -> getId();
    return os;
}

Tour AntColonyOptimization(Graph &gg, int start, int traversalTimes = 1, int antCount = 0){
    std::map<Vertex*, std::map<Vertex*, PheromonedEdge>> trail;
    float alpha, beta, gamma;
    alpha = 1;      //how valuable the pheromones are
    beta = 1;       //how valuable the shorter path is
    gamma = 3;      //how many times returning costs
    double sum_score;

    std::vector<Ant> Ants;

    if(antCount == 0){
        antCount = gg.size();
    }

    Ant a;
    a << gg[start];
    Ants.push_back(a);
    antCount--;

    std::map<int, bool>antAt;
    int id;
    //make ants
    for(int i=0; i<antCount; i++){
        do{
            id = std::rand()%gg.size()+1;
        }while(isAt(antAt, id));
        antAt[id] = true;
        Ant a;
        a << gg[id];
        Ants.push_back(a);
    }

    for(int traversal_index = 0; traversal_index<traversalTimes; traversal_index++){
        int isAntDone = 0;
        putPheromones(gg, Ants, trail);
        for(int id=1; id <= gg.size()*100; id++){
            if(isAntDone >= Ants.size()){
                break;
            }
            isAntDone = 0;
            for(int i=0; i<Ants.size(); i++){
                if(isComplete(gg.size(), Ants[i].visitedVector)){
                    isAntDone++;
                    continue;
                }
                sum_score = 0;
                for(auto const& j : Ants[i].current -> getNeighbours()){
                    // j.first
                    PheromonedEdge pe;
                    try{
                        //has an edge
                        pe = trail.at(Ants[i].current).at(j.first); 
                    }catch(...){
                        //no edge, so make one
                        pe << j.second;
                        trail[Ants[i].current][j.first] = pe;
                    }
                    sum_score += pow(pe.pheromones, alpha) + pow(pe.eta, beta);
                }

                double value, high_value = -1;
                Vertex *high_v;

                // std::cout << "current " << Ants[i].current -> getId() << std::endl;
                for(auto const& option : trail[Ants[i].current]){
                    PheromonedEdge pe = option.second;
                    value = pow(pe.pheromones, alpha) + pow(pe.eta, beta);
                    // std::cout << "trail option " << option.first << "==" << option.first -> getId() << " value " << value << std::endl;
                    if(isAt(Ants[i].visited, option.first)){
                        //already visited, aka not allowed(won't work well)
                        // std::cout << "ForAnt " << i << " has visited vertex " << option.first -> getId() << " (" << Ants[i].visited.at(option.first) << " times), so unatractive " << std::endl;
                        value /= gamma * Ants[i].visited.at(option.first);
                    } 
                    value /= sum_score;
                    if(value > high_value || high_value == -1){
                        high_value = value;
                        high_v = option.first;
                    } 
                }
                Ants[i] << high_v;
            }
        }
    }
    return Ants[0].visitedVector;
}


void putPheromones(Graph &gg, std::vector<Ant> &Ants, std::map<Vertex*, std::map<Vertex*, PheromonedEdge>> &trail){
    float evaporation = 0.1;  //10% evaporates for every ant
    float pheromone = 1000; //how many pheromones to deposit
    for(int i=0; i<Ants.size(); i++){
        std::string name = "Ant ";
        name = name + std::to_string(Ants[i].visitedVector.front() -> getId());
        name += " | ";
        // printPath(Ants[i].visitedVector, name);
        for(int j=0; j<Ants[i].visitedVector.size()-1; j++){
            trail[Ants[i].visitedVector[j]][Ants[i].visitedVector[j+1]].pheromones *= 1 - evaporation;
            trail[Ants[i].visitedVector[j]][Ants[i].visitedVector[j+1]].pheromones += pheromone/aStarGetTotalPathWeight(Ants[i].visitedVector);  
        }
        Ants[i].visited.clear();
        Ants[i].visitedVector.clear();
        Ants[i] << gg[Ants[i].ant_id];
    }
}

//O(N^2)
bool isComplete(const int vertCount, const Tour &T){
    for(int i=1; i<vertCount; i++){
        bool isAccountedFor = false;
        for(int j=0; j<T.size(); j++){
            if(T[j] -> getId() == i){
                //id accounted for
                isAccountedFor = true;
                break;
            }
        }
        if(!isAccountedFor){
            return false;
        }
    }
    return true;
}