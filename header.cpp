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
        Vertex();
        Vertex(int);
        ~Vertex();
    private:
        unsigned int id;
        bool isEnabled;
        // std::vector <Edge> edges;
        // std::vector <Vertex*> neighbours;
        std::map <Vertex*, Edge> neighbours;
        Edge makeEdge(Vertex*);
};

typedef std::vector<Vertex*> Tour;

struct Edge{
    Vertex* to = nullptr;
    unsigned int weight;
    bool isVirtual = false;
    bool isEnabled = true;
};

class Graph{
    public:
        int addVertex();
        bool vertexLink(int, int);
        Vertex* getVertex(int);
        Vertex* operator[](const int);
        Vertex* operator++(const int);
        Tour findVerticesWithEdgeTo(Vertex*);
        Tour GAStar(int, int);
        Graph();
        ~Graph();
        void printGraph();
        int size();
    private:
        unsigned int vertexCount;
        std::map <int, Vertex*> vertices;
};

Tour aStar(Vertex*, Vertex*, bool makeVirtualEdge = true);
int aStarHeuristicCost(Vertex*, Vertex*);
Vertex* getAStarSmallestVertex(std::map<Vertex*, int>, std::map<Vertex*, int>);
Tour aStarReconstructPath(std::map<Vertex*, Vertex*>, Vertex*);
int aStarGetTotalPathWeight(Tour);
Tour aStarGetPathToClosestOf(Vertex*, std::map<Vertex*, int>);
