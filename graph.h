#pragma once
#include <vector>
#include <string>

class Graph {

    public:
    //not default constructor. Here until we figure out what to pass in
    Graph();
    
    void insertVertex(Vertex v);

    void insertEdge(Vertex v1, Vertex v2, Edge theEdge);

    vector<Edge*> incidentEdges(Vertex v);

    bool areAdjacent(Vertex v1, Vertex v2);

    std::map<Vertex, std::list<Edge *>> adjacencyList;


    std::vector<std::vector<int>> adjacencyMatrix;


    private:

    class Edge{

        public:
        Vertex * a;
        Vertex * b;

        //0 if a to b 1 if b to a?
        int direction;

    };

    class Vertex {

        int degree;
        //Index in adjacecy Matrix for O(1) lookup;
        int position;

        string label;

    };



};