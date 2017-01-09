#include "branch_and_bound.hpp"

branchAndBound::branchAndBound(){
    bestTour = 2147483647; //max long
    bestNode = nullptr;
}

Node::~Node(){
    delete leftChild;
    delete rightChild;
}

Node::Node(){
    name = "";
    leftChild = nullptr;
    rightChild = nullptr;
    Vertex* current = ::start_vertex;
    std::map<Vertex*, bool>seen;
    std::map<Vertex*, bool>been;
    while(current){
        been[current] = true;
        for(auto const &i : current -> getNeighbours()){
            constraints[current][i.first] = 0;
            seen[i.first] = true;
        }
        current = (*(seen - been).begin()).first;
    }
}

Node::Node(std::map<Vertex*, std::map<Vertex*, int>> c, Vertex* changed, std::string nm){
    name = nm;
    for(auto const &a : c){
        for(auto const &b : a.second){
            constraints[a.first][b.first] = b.second;
        }
    }
    addDisallowedEdges(changed);
    addRequiredEdges(changed);
    // addDisallowedEdges(changed);
    // addRequiredEdges(changed);
    leftChild = nullptr;
    rightChild = nullptr;
    // std::cout << "result of creation:\r\n" << constraints << std::endl;
}

void Node::addDisallowedEdges(Vertex* first){
    int count = 0;
    for(auto const &i : getConstraints(first)){
        if(i.second == 1){
            count++;
        }
    }
    if(count >= 1){
        for(auto const &i : first -> getNeighbours()){
            int c = constraints[first][i.first];
            if(constraints[first][i.first] == 0){
                constraints[first][i.first] = -1;
            }
        }
    }

    count = 0;
    Tour neigh = first -> getNeighbouredVertices();
    for(auto const &i : neigh){
        auto constr = getConstraints(i);
        if(constr.find(first) != constr.end() && constraints[i][first] == 1){
            count++;
        }
    }

    if(count >= 1){
        for(auto const &i : neigh){
            if(constraints[i][first] == 0){
                constraints[i][first] = -1;
            }
        }
    }
}

void Node::addRequiredEdges(Vertex* first){
    int count = 0;
    for(auto const &i : getConstraints(first)){
        if(i.second == -1){
            count++;
        }
    }
    if(count >= first -> getNeighbours().size() - 1){
        for(auto const &i : first -> getNeighbours()){
            if(constraints[first][i.first] == 0){
                constraints[first][i.first] = 1;
            }
        }
    }

    count = 0;
    Tour neigh = first -> getNeighbouredVertices();
    for(auto const &i : neigh){
        auto constr = getConstraints(i);
        if(constr.find(first) != constr.end() && constraints[i][first] == -1){
            count++;
        }
    }

    if(count >= neigh.size() - 1){
        for(auto const &i : neigh){
            if(constraints[i][first] == 0){
                constraints[i][first] = 1;
            }
        }
    }

}

bool Node::isTour(){
    if(!goodNeighbourInOut(::start_vertex, 1, 1)){
        return false;
    }

    Tour current = getTour();

    std::map<Vertex*, bool>seen;
    for(auto const &i : current){
        for(auto const &j : i -> getNeighbours()){
            seen[j.first] = true;
        }
    }
    for(auto const &i : current){
        seen.erase(i);
    }
    if(seen.size() > 0){
        return false;
    }else{
        return true;
    }
}

Tour Node::getTour(){
    Tour T, P;
    Vertex* current = ::start_vertex;
    while(true){
        T.push_back(current);
        for(auto const &i : getConstraints(current)){
            if(i.second != -1){
                current = i.first;
                break;
            }
            P.push_back(i.first);
        }
        if(*(P-T).begin() == 0){
            break;
        }
    }
    return T;
}

std::map<Vertex*, std::map<Vertex*, int>> Node::getConstraints(){
    return constraints;
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

std::map<Vertex*, int> Node::getConstraints(Vertex* V){
    if(constraints.find(V) != constraints.end()){
        return constraints[V];
    }
    std::map<Vertex*, int> empty;
    return empty;
}

void Node::setLB(double lb){
    lower_bound = lb;
}
double Node::getLB(){
    if(lower_bound){
        return lower_bound;
    }
    calcLowerBound();       //sets lower_bound
    return lower_bound;
}

/*
    Constraints are as follows:
    1 => required, these vertices must connect one to another
    0 => allowed, vertices may connect, but they don't have to (this is implicit)
    -1 => disallowed, vertices may NOT connect
*/
void Node::addChildrenWithConstraints(Vertex* first){
    Vertex* second = nullptr;
    for(auto const &i : getConstraints(first)){
        if(i.second == 0){
            second = i.first;
            break;
        }
    }

    if(second == nullptr){
        return;
    }

    int original;
    if(constraints.find(first) != constraints.end() && constraints[first].find(second) != constraints[first].end()){
        original = constraints[first][second];
    }
    constraints[first][second] = 1;
    std::string newName = name + " " + std::to_string(first -> getId()) + "-" + std::to_string(second -> getId()) + " ";
    leftChild = new Node(constraints, first, newName);

    newName = name + " " + std::to_string(first -> getId()) + "-" + std::to_string(second -> getId()) + "* ";
    constraints[first][second] = -1;
    rightChild = new Node(constraints, first, newName);
    constraints[first][second] = original;
}

void Node::addChildrenWithConstraintsBetween(Vertex* first, Vertex* second){
    int original = 0;
    if(constraints.find(first) != constraints.end() && constraints.find(second) != constraints.end()){
        original = constraints[first][second];
    }

    constraints[first][second] = 1;
    // leftChild = new Node(constraints);
    constraints[first][second] = -1;
    // rightChild = new Node(constraints);
    constraints[first][second] = original;
}

Node* Node::left(){
    return leftChild;
}
Node* Node::right(){
    return rightChild;
}

void Node::pruneLeft(){
    leftChild = nullptr;
}
void Node::pruneRight(){
    rightChild = nullptr;
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

void Node::calcLowerBound(){
    Vertex *current = ::start_vertex;
    double twice_lower_bound = 0;
    
    std::map<Vertex*, bool>seen;
    std::map<Vertex*, bool>been;

    while(current){
        double smallest = -1;
        been[current] = true;

        auto constr = getConstraints(current);
        //smallest from current to another
        for(auto const &i : current -> getNeighbours()){
            if(constr.find(i.first) != constr.end() && constr[i.first] != -1 && (i.second.weight < smallest || smallest == -1)){
                smallest = i.second.weight;
            }
            seen[i.first] = true;
        }
        twice_lower_bound += smallest;
        smallest = -1;
        //smallest from another to vertex
        for(auto const &i : current -> getNeighbouredVertices()){
            constr = getConstraints(i);
            if(constr.find(current) != constr.end() && constr[current] != -1){
                Edge e = i -> getNeighbour(current);
                if(e.weight < smallest || smallest == -1){
                    smallest = e.weight;
                }
            }
        }
        twice_lower_bound += smallest;
        current = (*(seen - been).begin()).first;
    }
    lower_bound = twice_lower_bound/2;
    


}

int Node::countNeighboursOut(Vertex* current){
    int total_out = current -> getNeighbours().size();
    for(auto const &i : getConstraints(current)){
        if(i.second == -1){
            total_out--;
        }
    }
    return total_out;
}
int Node::countNeighboursIn(Vertex* current){
    Tour neighboured = current -> getNeighbouredVertices();
    int total_in = neighboured.size();
    for(auto const &i : neighboured){
        std::map<Vertex*, int> constr = getConstraints(i);
        if(constr.find(current) != constr.end() && constr[current] == -1){
            total_in--;
        }
    }

    return total_in;
}

bool Node::goodNeighbourInOut(Vertex* current, int in, int out){
    if(countNeighboursOut(current) == out && countNeighboursIn(current) == in){
        return true;
    }
    return false;
}

Tour BnB(Graph &gg){
    branchAndBound* BnB = new branchAndBound();
    Node* root = new Node();
    root -> calcLowerBound();
    BnB -> aaa(gg, root);

    Tour result = BnB -> getBestTour();
    delete root;
    delete BnB;
    return result;
}

Tour branchAndBound::getBestTour(){
    if(bestNode != nullptr){
        return bestNode -> getTour();
    }else{
        Tour T;
        return T;
    }
}

void branchAndBound::aaa(Graph &gg, Node* n){
    if(n != nullptr){
        std::cout << "result of constraint dissallowment on" << (*n).name << "\r\n" << n -> getConstraints() << std::endl;
        if(n -> isTour()){
            long node_weight = aStarGetTotalPathWeight(n -> getTour(), true);
            if(node_weight < bestTour){
                bestTour = node_weight;
                bestNode = n;
            }
        }
        if(n -> getLB() < 2 * bestTour){
            /*edge index???*/
            //pick some point that's maybe not quite well
            Vertex* current = nullptr;
            for(int id=1; id<gg.size(); id++){
                current = gg[id];
                if(n -> countNeighboursOut(current) != 1){
                    break;
                }
            }
            //make children
            n -> addChildrenWithConstraints(current);

            Node *child = n -> left();
            if(child != nullptr){
                child -> calcLowerBound();
                if(child -> getLB() > 2* bestTour){
                    n -> pruneLeft();
                }
            }

            child = n -> right();
            if(child != nullptr){
                child -> calcLowerBound();
                if(child -> getLB() > 2* bestTour){
                    n -> pruneRight();
                }
            }

            Node *left, *right;
            left = n -> left();
            right = n -> right();
            if(left != nullptr && right != nullptr){
                if(n -> left() -> getLB() <= n -> right() -> getLB()){
                    aaa(gg, n -> left());
                    aaa(gg, n -> right());
                }else{
                    aaa(gg, n -> right());
                    aaa(gg, n -> left());
                }
            }else{
                aaa(gg, n -> left());
                aaa(gg, n -> right());
            }
        }
    }
}