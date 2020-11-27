#pragma once
#include <vector>
#include <map>
#include <string>
#include <list>
#include <unordered_map>


typedef std::string Vertex;


class Graph {

    public:
        /*
        struct Vertex {

            int degree;
            //Index in adjacecy Matrix for O(1) lookup;
            int position;

            std::string label;

            std::string print_info_to_prevent_make_error() {
                degree = 3;
                position = 3;
                label = "carrot";
                return label;
            }

            bool operator<(Vertex other) const {
                return false;
            }
        };
        */

        struct Edge {

            Vertex * a;
            Vertex * b;

            //0 if a to b 1 if b to a?
            int direction;

        };

    // public:
    //not default constructor. Here until we figure out what to pass in
        Graph() {};

        ~Graph() {};
        
        void insertVertex(Vertex v);

        void insertEdge(Vertex v1, Vertex v2, Edge theEdge);

        std::vector<Edge*> incidentEdges(Vertex v);

        bool areAdjacent(Vertex v1, Vertex v2);

        std::unordered_map<Vertex, std::vector<Edge *>()> adjacencyList();

        std::vector<std::vector<int>> adjacencyMatrix;

        std::vector<Vertex> vertexList;

};