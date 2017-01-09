#ifndef Branch_and_bound_H
#define Branch_and_bound_H

#include <string>

#include "vertex.hpp"
#include "graph.hpp"
#include "utils.hpp"

#include "my_globals.hpp"

class Node{
    public:
        std::string name;
        Node();
        Node(std::map<Vertex*, std::map<Vertex*, int>> c, Vertex*, std::string name);
        ~Node();
        std::map<Vertex*, std::map<Vertex*, int>> getConstraints();
        std::map<Vertex*, int> getConstraints(Vertex* V);
        void setLB(double);
        void addChildrenWithConstraintsBetween(Vertex*, Vertex*);
        void addChildrenWithConstraints(Vertex*);
        void addDisallowedEdges(Vertex*);
        void addRequiredEdges(Vertex*);
        void pruneLeft();
        void pruneRight();
        void calcLowerBound();
        bool isTour();
        int countNeighboursOut(Vertex*);
        int countNeighboursIn(Vertex*);
        bool goodNeighbourInOut(Vertex*, int a=1, int b=1);
        Tour getTour();
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

class branchAndBound{
    public:
        void aaa(Graph &gg, Node* n);
        branchAndBound();
        Tour getBestTour();
    private:
        long bestTour;
        Node* bestNode;
};

std::ostream& operator<<(std::ostream& os, Node *N);
Tour BnB(Graph &gg);

#endif