#include <iostream>
#include "algorithms.hpp"
#include "graph.h"

// using boost::numeric::ublas::matrix;

int main(int argc, char *argv[]) {
    std::ifstream file("decoded_links.tsv");
    Graph graph(file);
    // graph.printAdjMat();
    Vertex start;
    Vertex end;
    Alg::shortest_path(graph, start, end);
    Alg::bfs(graph, start);
    auto result = Alg::pagerank(graph, 0.85, 1000, 1e-5);
    int count = 0;
    for(auto entry : result) {
        count++;
        std::cout << entry.first + ": " << entry.second << std::endl;
        if(count > 10) break;
    }
    return 0;
}