#include <iostream>
#include "algorithms.hpp"
#include "graph.h"
#include <set>

void checkForR(Vertex x) {
    for (char m : x) { if (m == '\r') std::cout << "HEY";}
}

int main(int argc, char *argv[]) {
// Test that it Compiles
    // std::cout << "I compile!" << std::endl;
    // Graph graph;
    // Vertex start;
    // Vertex end;
    // Alg::shortest_path(graph, start, end);
    // Alg::bfs(graph, start);
    // Alg::pagerank(graph, 0.5, 100, 0.000005);
    // std::cout << "\n";

// Test Graph Constructor and Adjacency List / Vertex List is Built Properly
    std::ifstream fileStream("decoded_links.tsv", std::ifstream::in);    
    Graph Graph(fileStream);
    // std::cout << Graph.vert_to_ind.size() << " " << Graph.vertexList.size();
    for (int i = 0; i < (int) Graph.vert_to_ind.size(); i++) {
        std::cout << Graph.vertexList[i] << " " << Graph.vert_to_ind[Graph.vertexList[i]] << " " << Graph.vertexList[Graph.vert_to_ind[Graph.vertexList[i]]] << "\n";
        if (Graph.vert_to_ind[Graph.vertexList[i]] != i) std::cout << "Failure at: " << i << "\n";
    }

    // std::set<Vertex> uniques;
    // for (auto child : Graph.vertexList) {
    //     std::cout << "Entry " << child.second << ": " << child.first << "\n";
    //     uniques.insert(child.first);
    //     // if (lastCount < child.second) lastCount = child.second;
    // }
    // std::cout << "There are the correct number of Unique Entries: " << uniques.size() << " == " << Graph.vertexList.size() << " -> " << (uniques.size() == Graph.vertexList.size() ? "True" : "False");
    
// Check Unique Values in Our Adjacency and Vertix Lists
    // Vertex V1, V2;
    // std::set<Vertex> uniques;
    // while(!fileStream.eof()) {

    //     std::getline (fileStream, V1, '\t');
    //     std::getline (fileStream, V2, '\n');     
    //     uniques.insert(V1);
    //     uniques.insert(V2);
    //     if (Graph.vertexList.find(V1) == Graph.vertexList.end()) Graph.vertexList.insert(std::make_pair(V1, Graph.vertexList.size()));
    //     if (Graph.vertexList.find(V2) == Graph.vertexList.end()) Graph.vertexList.insert(std::make_pair(V2, Graph.vertexList.size()));
    //     Graph.adjacencyList[V1].push_back(new Graph::Edge(V1, V2));
    //     if (Graph.adjacencyList.find(V2) == Graph.adjacencyList.end()) Graph.adjacencyList[V2] = std::vector<Graph::Edge *>();
    // }

    // std::cout << "\n\nSize: " << uniques.size() << "\n";
    // std::cout << "There are a Proper Number of "

// Create Custom Adjacency List Outside the Graph File
    // Vertex V1;
    // Vertex V2;
    // std::unordered_map<Vertex, std::vector<Graph::Edge *>> adjacencyList;
    // std::map<Vertex, int> map_reduce;
    // int lines = 0;

    // while(!fileStream.eof()) {
    //     std::getline (fileStream, V1, '\t');
    //     std::getline (fileStream, V2, '\n');
        // checkForR(V1);
        // checkForR(V2);
        // map_reduce[V1]++;
        // map_reduce[V2]++;
        // std::cout << "Node 1: " << V1 << "\n";
        // std::cout << "Node 2: " << V2 << "\n";
    //     uniques.insert(V1);
    //     uniques.insert(V2);
    //     adjacencyList[V1].push_back(new Graph::Edge(V1, V2));
    //     if (adjacencyList.find(V2) == adjacencyList.end()) adjacencyList[V2] = std::vector<Graph::Edge *>();
    // }
    // std::cout << uniques.size();
    // for (auto child : map_reduce) std::cout /*<< "Article: "*/ << child.first << "\t" /*<< "\tCount: "*/ << child.second << "\n";
    

    // for (std::pair<Vertex, std::vector<Graph::Edge *>> child : Graph.adjacencyList) {
    //     std::cout << "\nSource: " << child.first << "\n\t\n";
    //     std::cout << "Destination: \n";
    //     for (int i = 0; i < (int) child.second.size(); i++)
    //         std::cout << "\t" << child.second[i]->destination << "\n";
    // }

    return 0;
}