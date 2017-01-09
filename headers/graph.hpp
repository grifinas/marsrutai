#ifndef graph_H
#define graph_H

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <stdexcept>
#include <random>


#include "tinyxml2.h"

#include "vertex.hpp"
#include "astar.hpp"

#include "my_globals.hpp"


class Graph{
    public:
        int addVertex();
        int addVertex(Vertex* v, long node = 0);
        bool vertexLink(int, int);
        bool vertexLinkBoth(int, int);
        Vertex* getVertex(int);
        Vertex* getVertexByNode(long);
        Vertex* operator[](const int);
        Vertex* operator++(const int);
        Tour findVerticesWithEdgeTo(Vertex*);
        Tour GAStar(int, int);
        Graph();
        Graph(tinyxml2::XMLElement*);
        ~Graph();
        void printGraph();
        void setGlobals();
        int size();
    private:
        unsigned int vertexCount;
        std::map <int, Vertex*> vertices;
        std::map <long, int> NodeToVertex;
};


#endif