#include <iostream>
#include "algorithms.hpp"
#include "graph.h"

int main(int argc, char *argv[]) {
    // std::cout << "I compile!" << std::endl;
    // int graph[10][10];
    Graph graph;
    
    Vertex start;
    Vertex end;

    Alg::shortest_path(graph, start, end);
    Alg::bfs(graph, start);
    Alg::pagerank(graph, 0.5, 100, 0.000005);
    std::cout << "\n";

    std::ifstream file("decoded_links.txt", std::ifstream::in);    
    Graph Graph(file);

    // Vertex V1;
    // Vertex V2;
    // std::unordered_map<Vertex, std::vector<Graph::Edge *>> adjacencyList;

    // while(!file.eof()) {
    //     std::getline (file, V1, '\t');
    //     std::getline (file, V2, '\n');
    //     adjacencyList[V1].push_back(new Graph::Edge(V1, V2));
    //     if (adjacencyList.find(V2) == adjacencyList.end()) adjacencyList[V2] = std::vector<Graph::Edge *>();
    // }

    // for (std::pair<Vertex, std::vector<Graph::Edge *>> child : Graph.adjacencyList) {
    //     std::cout << "\nSource: " << child.first << "\n\t\n";
    //     std::cout << "Destination: \n";
    //     for (int i = 0; i < (int) child.second.size(); i++)
    //         std::cout << "\t" << child.second[i]->destination << "\n";
    // }

    return 0;
}