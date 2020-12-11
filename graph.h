#pragma once
#include <vector>
#include <map>
#include <string>
#include <list>
#include <unordered_map>
#include <fstream>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>


typedef std::string Vertex;
namespace ublas = boost::numeric::ublas;


class Graph {

    public:
        struct Edge {
            Vertex source;
            Vertex destination;
            double weight = 1;
            Edge(){};
            Edge(Vertex setSrc, Vertex setDest) : source(setSrc), destination(setDest){};
            Edge(Vertex setSrc, Vertex setDest, double setWeight) : source(setSrc), destination(setDest), weight(setWeight) {};
            bool operator==(const Edge& other) const
            {
                return (source == other.source) && (destination == other.destination) && (weight == other.weight);
            }
        };
        
        Graph(){};
        Graph(std::ifstream& fileStream, bool weighted = false);        
        Graph(const Graph &other);
        ~Graph();
        void _clear();

        Graph & operator=(const Graph & other);
        bool operator==(const Graph & other) const;
        void createAdjMat();
        void printAdjMat();

        // For insertion methods, createAdjMat() must be called after all insertions are complete; 
        // design choice was based on ultimately developing an immutable graph from a dataset and 
        // to save on time complexity. Insert functions included in design for testing purposes &
        // general graph implementations.
        void insertVertex(Vertex v);
        void insertEdge(Vertex v1, Vertex v2);

        std::vector<Edge*> incidentEdges(Vertex v) const;
        bool areAdjacent(Vertex v1, Vertex v2);

        std::unordered_map<Vertex, std::vector<Edge *>> adjacencyList;
        ublas::matrix<double> adjacencyMatrix;
        std::vector<Vertex> vertexList;
        std::unordered_map<Vertex, int> vert_to_ind;
};