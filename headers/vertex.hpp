#ifndef vertex_H
#define vertex_H

#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <stdexcept>
#include <random>



struct Edge;

class Vertex{
    public:
        bool hasEdgeTo(Vertex*);
        unsigned int getId();
        int countDoubleEdges();
        std::map <Vertex*, Edge> getNeighbours();
        Edge addNeighbour(Vertex*);
        Edge getNeighbour(Vertex*);
        Edge getSmallestNeighbouringEdge(std::map<Vertex*, int>, std::map<Vertex*, int>&, int depth);
        // Edge getSmallestNeighbouringEdge(std::map<Vertex*, int>, std::map<Vertex*, int>&);
        Edge getSmallestNeighbouringEdge(std::map<Vertex*, int>);
        Edge getSmallestNeighbouringEdge();
        void printVertex();
        void printEdges();
        void makeVirtualEdge(Vertex*, int);
        void enable();
        void disable();
        void setLat(float a);
        void setLng(float a);
        void setId(unsigned int a);
        void setNodeId(const char* a);
        void newNeighboured(Vertex*);
        std::vector<Vertex*> getNeighbouredVertices();
        Vertex();
        Vertex(int);
        Vertex(int, const char*);
        ~Vertex();
    private:
        unsigned int id;
        const char* node_id;
        float lat, lng;
        bool isEnabled;
        // std::vector <Edge> edges;
        // std::vector <Vertex*> neighbours;
        std::map <Vertex*, Edge> neighbours;
        std::vector<Vertex*> isNeighbouredBy;
        Edge makeEdge(Vertex*);
};

typedef std::vector<Vertex*> Tour;

struct Edge{
    Vertex* to = nullptr;
    unsigned int weight;
    bool isVirtual = false;
    bool isEnabled = true;
};

std::ostream& operator<<(std::ostream& os, Vertex *V);
bool operator < (Edge e1, Edge e2);
std::ostream& operator<<(std::ostream& os, const Edge &E);
#endif