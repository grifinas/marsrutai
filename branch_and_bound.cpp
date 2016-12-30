int BnBHeuristic(Vertex *goal);
void cbSearch(Tour T, Tour best_path, Vertex *goal, int &bound);

Tour DFBranchAndBound(Graph gg, Vertex *start, Vertex *goal, int bound = 9999999){
    Tour best_path;
    best_path.push_back(start);
    cbSearch(best_path, best_path, goal, bound);
    return best_path;
}

void cbSearch(Tour T, Tour best_path, Vertex *goal, int &bound){
    // int cost = aStarGetTotalPathWeight(T);
    int cost = 50;
    if(cost + BnBHeuristic(T.back()) < bound){
        if(T.back() == goal){
            best_path = T;
            bound = cost;
            return; 
        }else{
            for(auto const &neighbour : T.back() -> getNeighbours()){
                Tour tmp(T);
                tmp.push_back(neighbour.first);
                cbSearch(tmp, best_path, goal, bound);
            }
        }
    }
}

int BnBHeuristic(Vertex *goal){
    int lowInt = -1;
    for(auto const& i : goal->getNeighbours()){
        Edge e = i.first -> getNeighbour(goal);
        if(e.weight < lowInt || lowInt < 0){
            lowInt = e.weight;
        }
    }
    return lowInt;
}



class Node{
    public:
        Node();
        Node(std::map<Vertex*, std::map<Vertex*, int>> c);
        ~Node();
        std::map<Vertex*, std::map<Vertex*, int>> getConstraints();
        std::map<Vertex*, int> getConstraints(Vertex* V);
        void setLB(double);
        void addChildrenWithConstraintsBetween(Vertex*, Vertex*);
        double getLB();
        Node* left();
        Node* right();
        Node* getLowestBoundNode();
    private:
        std::map<Vertex*, std::map<Vertex*, int>>constraints;
        Node *leftChild;
        Node *rightChild;
        double lower_bound = 0;
};

Node::~Node(){
    delete leftChild;
    delete rightChild;
}

Node::Node(){
    leftChild = nullptr;
    rightChild = nullptr;
}

Node::Node(std::map<Vertex*, std::map<Vertex*, int>> c){
    for(auto const &a : c){
        for(auto const &b : a.second){
            constraints[a.first][b.first] = b.second;
        }
    }
    leftChild = nullptr;
    rightChild = nullptr;
}

std::map<Vertex*, std::map<Vertex*, int>> Node::getConstraints(){
    return constraints;
}

std::map<Vertex*, int> Node::getConstraints(Vertex* V){
    if(isAt(constraints, V)){
        return constraints[V];
    }
    std::map<Vertex*, int> empty;
    return empty;
}

void Node::setLB(double lb){
    lower_bound = lb;
}
double Node::getLB(){
    return lower_bound;
}

void Node::addChildrenWithConstraintsBetween(Vertex* first, Vertex* second){
    int original = 0;
    if(isAt(constraints, first) && isAt(constraints[first], second)){
        original = constraints[first][second];
    }

    constraints[first][second] = 1;
    leftChild = new Node(constraints);
    constraints[first][second] = -1;
    rightChild = new Node(constraints);
    constraints[first][second] = original;
}

Node* Node::left(){
    return leftChild;
}
Node* Node::right(){
    return rightChild;
}
Node* Node::getLowestBoundNode(){
    if(leftChild != nullptr && rightChild != nullptr){      //two children, pick lowerbound
        if(leftChild -> getLB() < rightChild -> getLB()){
            return leftChild -> getLowestBoundNode();
        }else{
            return rightChild -> getLowestBoundNode();
        }
    }else{
        if(leftChild != nullptr && rightChild == nullptr){      //only left child, pick it
            return leftChild -> getLowestBoundNode();
        }else if(leftChild == nullptr && rightChild != nullptr){        //only right child, pick it
            return rightChild -> getLowestBoundNode();
        }else{          //no children, return ourself
            return this;
        }
    }
}

std::ostream& operator<<(std::ostream& os, Node *N){
    os << "\r\nNode:" << N -> getLB() << ":\r\n" << N -> getConstraints();
    if(N -> left() != nullptr){
        os << "\r\nlchild " << N -> left();
    }
    if(N -> right() != nullptr){
        os << "\r\nrchild " << N -> right();
    }
    return os;
}

double calcLowerBound(Graph &gg, std::map<Vertex*, std::map<Vertex*, int>> constraints){
    Vertex *current;
    double twice_lower_bound = 0;
    for(int i=1; i<gg.size(); i++){
        current = gg[i];
        std::map<Vertex*, int>visited;
        std::vector<int>smallest;
        //check if constraints exist to current vertex
        if(isAt(constraints, current)){
            for(auto const &i : constraints[current]){
                if(i.second == -1){ //if cannot visit, preted that it's already visited'
                    visited[i.first] = 1;
                }else if(i.second == 1){
                    visited[i.first] = 1;
                    Edge tmp = current -> getNeighbour(i.first);
                    smallest.push_back(tmp.weight);
                }
            }
        }
        while(smallest.size() < 2){
            Edge tmp = current -> getSmallestNeighbouringEdge(visited);
            if(tmp.to != nullptr){
                visited[tmp.to] = 1;
                smallest.push_back(tmp.weight);
            }else{
                std::cout << "failed to get enough edges at line " << __LINE__ << " bad constraint or dead end" << std::endl;
                std::cout << "constraints:\r\n" << constraints << std::endl;
                std::cout << current << " neighbours: \r\n" << current ->getNeighbours() << std::endl;
                break;
            }
        }

        twice_lower_bound += smallest[0] + smallest[1];
        // std::cout << "smallest of " << current << " arr \r\n" << smallest << std::endl;
    }


    return twice_lower_bound/2;
}

int countNeighbours(Vertex* current, const std::map <Vertex*, Edge> &current_neighbours, Node *n){
    int total = current_neighbours.size();
    for(auto const &i : n -> getConstraints(current)){
        if(i.second == -1){
            total--;
        }
    }
    return total;
}

Tour BnB(Graph &gg, const int start){
    /*
        Constraints are as follows:
        1 => required, these vertices must connect one to another
        0 => allowed, vertices may connect, but they don't have to (this is implicit)
       -1 => disallowed, vertices may NOT connect
    */
    
    Node *current_node = new Node();
    Node *root = current_node;

    double lower_bound = calcLowerBound(gg, current_node -> getConstraints());
    std::cout << "lb " << lower_bound << std::endl;

    current_node -> setLB(lower_bound);

    for(int id=1; id<gg.size(); id++){
        Vertex* current = gg[id];
        std::map <Vertex*, Edge> current_neighbours = current -> getNeighbours();
        for(auto const &i : current_neighbours){
            if(countNeighbours(current, current_neighbours, current_node) <= 2){
                break;
            }
            if(i.first -> countDoubleEdges() < 2){
                Tour vert = gg.findVerticesWithEdgeTo(i.first);
                if(vert.size() < 2){
                    continue;
                }
            }
            std::cout << "branch for " << current << " cn:" << countNeighbours(current, current_neighbours, current_node) << " and " << i.first << std::endl;
            current_node -> addChildrenWithConstraintsBetween(current, i.first);
            Node *child = current_node -> left();
            lower_bound = calcLowerBound(gg, child -> getConstraints());
            child -> setLB(lower_bound);
            child = current_node -> right();
            lower_bound = calcLowerBound(gg, child -> getConstraints());
            child -> setLB(lower_bound);
            if(current_node -> left() -> getLB() < current_node -> right() -> getLB()){
                current_node = current_node -> left();
            }else{
                current_node = current_node -> right();
            }
        }
    }

    std::cout << "decision tree: " << root << std::endl;

    Node* Lowest = root -> getLowestBoundNode();

    std::cout << "lowest bound " << Lowest << std::endl;

    // Tour result = traverseWithConstraints()

    delete root;
}