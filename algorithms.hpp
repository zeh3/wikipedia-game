#include <iostream>
#include <queue>
#include "graph.h"
#include <string>
// typedef std::string Vertex;

/* If we don't want to have this templated that's fine too, we will likely just use vertices instead of ints like Geeks for Geeks did */ 
/* Might not be easily doable without explicity using Vertex and such anyways! */

namespace Alg {
    void shortest_path(Graph path, Vertex start, Vertex end) {
        //https://www.geeksforgeeks.org/c-program-for-dijkstras-shortest-path-algorithm-greedy-algo-7/
        std::cout << "\nShortest_Path:\n";
    }

    // template <class G, class V>
    void bfs(Graph graph, Vertex start) {
        //https://www.geeksforgeeks.org/breadth-first-search-or-bfs-for-a-graph/
        std::cout << "\nBFS\n";
    }

    // template <class G>
    void pagerank(Graph graph,  double alpha, int iterations, double tolerance) {
        //https://www.geeksforgeeks.org/page-rank-algorithm-implementation/
        std::cout << "\nPage_rank\n";
    }
}