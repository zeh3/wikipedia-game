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

/**
 * Graph representation class. Contains an inner Edge struct to represent graph edge. Implemented using an adjacencyList of vertex to a list of Edge* for that vertex. Supplemental normalized adjacency matrix used for areAdjacent() and PageRank()
 */ 
class Graph {

    public:
    /**
     * Internal Edge struct to represent Graph edges
     * source: the source of this directed edge
     * destination: the destination of the directed edge
     * weight: the weight of the edge, used for Dijkstra's; defaulted to 1.0 and altered depending on .tsv 
     */
        struct Edge {
            Vertex source;
            Vertex destination;
            double weight = 1;
            Edge(){};
            Edge(Vertex setSrc, Vertex setDest) : source(setSrc), destination(setDest){};
            Edge(Vertex setSrc, Vertex setDest, double setWeight) : source(setSrc), destination(setDest), weight(setWeight) {};

            /**
             * Comparison operator overloaded for convenience
             */ 
            bool operator==(const Edge& other) const
            {
                return (source == other.source) && (destination == other.destination) && (weight == other.weight);
            }
        };
        
        /**
         * Rule of Three & helper functions used to implement them
         */ 
        Graph(){};
        Graph(std::ifstream& fileStream, bool weighted = false);
        ~Graph();        
        Graph(const Graph &other);
        Graph & operator=(const Graph & other);
        void _clear();
        bool operator==(const Graph & other) const;

        /**
         * Creates the adjacencyMatrix; must be called after any insert function calls and after graph construction.
         */ 
        void createAdjMat();

        /**
         * Helper function to print the adjaceny matrix
         */
        void printAdjMat();

        /** For insertion methods, createAdjMat() must be called after all insertions are complete; 
        * design choice was based on ultimately developing an immutable graph from a dataset and 
        * to save on time complexity. Insert functions included in design for testing purposes &
        * general graph implementations.
        */ 

        /**
         * Inserts a vertex into the graph 
         */
        void insertVertex(Vertex v);
        /**
         * Inserts a edge into the graph 
         */
        void insertEdge(Vertex v1, Vertex v2);

        /**
         * Returns the list of edges that are *leaving* a given vertex; this was our given implementation choice
         */ 
        std::vector<Edge*> incidentEdges(Vertex v) const;
        /**
         * Uses our adjacency matrix to determine if two vertices are adjacent
         */ 
        bool areAdjacent(Vertex v1, Vertex v2);

        /**
         * Member variables
         * adjacencyList: unordered_map storing the vertex as a key, and a list of outgoing edge pointers as the value
         * adjacencyMatrix: normalized boost::ublas matrix keeping track of outgoing edges; used for areAdjacent & pageRank algorithm
         * vertexList: a list of all vertices, in order they are added to the adjacencyList
         * vert_to_ind: unordered_map that stores a vertex as the key, and its associated index in vertexList as the value
         */
        std::unordered_map<Vertex, std::vector<Edge *>> adjacencyList;
        ublas::matrix<double> adjacencyMatrix;
        std::vector<Vertex> vertexList;
        std::unordered_map<Vertex, int> vert_to_ind;
};