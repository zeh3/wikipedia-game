#include <iostream>
#include "algorithms.hpp"

int main(int argc, char *argv[]) {
    // std::cout << "I compile!" << std::endl;
    // int graph[10][10];
    // int start = 0;
    // int end = 1;
    Graph graph;
    Graph::Vertex start;
    Graph::Vertex end;

    Alg::shortest_path(graph, start, end);
    Alg::bfs(graph, start);
    Alg::pagerank(graph, 0.5, 100, 0.000005);
    std::cout << "\n";

    return 0;
}