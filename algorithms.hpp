#include <iostream>
#include <queue>
#include "graph.h"
#include <string>
#include <unordered_map>
#include <vector>
using Edge = Graph::Edge;


// typedef std::string Vertex;

/* If we don't want to have this templated that's fine too, we will likely just use vertices instead of ints like Geeks for Geeks did */ 
/* Might not be easily doable without explicity using Vertex and such anyways! */

namespace Alg {
    void shortest_path(Graph path, Vertex start, Vertex end) {
        //https://www.geeksforgeeks.org/c-program-for-dijkstras-shortest-path-algorithm-greedy-algo-7/
        std::cout << "\nShortest_Path:\n";
    }

    // template <class G, class V>
    std::vector<std::pair<Edge *, std::string>> bfs(Graph graph, Vertex start) {
        //https://www.geeksforgeeks.org/breadth-first-search-or-bfs-for-a-graph/
        std::unordered_map<Vertex, int> vertexTracker;
        vertexTracker[start] = 1;


        std::vector<std::pair<Edge *, std::string>> toReturnEdges;
        std::queue<Vertex> queue;

        queue.push(start);
        while(!queue.empty()) {
            Vertex current = queue.front();
            queue.pop();

            std::vector<Edge * > adjacentEdges = graph.incidentEdges(current);

            for (unsigned i = 0; i < adjacentEdges.size(); i++) {
                if (vertexTracker.find(adjacentEdges[i]->destination) == vertexTracker.end()) {
                    
                    toReturnEdges.push_back({new Edge(adjacentEdges[i]->source, adjacentEdges[i]->destination), "discovery"});
                    queue.push(adjacentEdges[i]->destination);
                    vertexTracker[adjacentEdges[i]->destination] = 1;
                } else {
          
                    toReturnEdges.push_back({new Edge(adjacentEdges[i]->source, adjacentEdges[i]->destination), "cross"});


                }
            }




        }

        std::cout << "\nBFS\n";

        return toReturnEdges;
    }

    // template <class G>
    void pagerank(Graph graph,  double alpha, int iterations, double tolerance) {
        //https://www.geeksforgeeks.org/page-rank-algorithm-implementation/
        std::cout << "\nPage_rank\n";
    }
}