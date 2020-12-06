#include <iostream>
#include "algorithms.hpp"
#include "graph.h"
#include <set>

// using boost::numeric::ublas::matrix;

int main(int argc, char *argv[]) {
    Graph graph;
    Vertex start;
    Vertex end;
    Alg::shortest_path(graph, start, end);
    Alg::bfs(graph, start);
    Alg::pagerank(graph, 0.5, 100, 0.000005);
    return 0;
}