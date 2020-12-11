#include <iostream>
#include "algorithms.hpp"
#include "graph.h"
#include <vector>

// using boost::numeric::ublas::matrix;
using std::vector;
using std::cout;
using std::endl;

int main(int argc, char *argv[]) {
    std::ifstream file("tests/disconnected_graph.tsv");
    Graph graph(file);
    graph.printAdjMat();

    vector<Vertex> vertexes = graph.vertexList;
    srand(time(NULL));
    Vertex start = vertexes[rand() % vertexes.size()];
    Vertex end = vertexes[rand() % vertexes.size()];
    vector<Edge> path = Alg::shortest_path(graph, start, end);
    cout << "The shortest path from " << start << " to " << end << ":" << endl;
    for (Edge e : path) {
        cout << e.source << " -> ";
    }
    cout << end << endl;

    Alg::bfs(graph, start);
    auto result = Alg::pagerank(graph, 0.85, 1000, 1e-7);
    int count = 0;
    for(auto entry : result) {
        count++;
        cout << entry.first + ": " << entry.second << endl;
        if(count > 10) break;
    }
    return 0;
}