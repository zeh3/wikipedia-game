#include <iostream>
#include <queue>
#include "graph.h"
#include <string>
#include <boost/numeric/ublas/assignment.hpp>
#include <boost/numeric/ublas/vector.hpp>
#include <algorithm>
#include <numeric>
#include <unordered_map>
#include <vector>
#include <algorithm>

using std::priority_queue;
using Edge = Graph::Edge;
using std::vector;
using std::cout;
using std::endl;
using std::pair;
using std::string;
using std::unordered_map;

namespace ublas = boost::numeric::ublas;
typedef std::string Vertex;

/**
 * Namespace containing our three algorithms: Dijkstra's, BFS, & PageRank. Utilizes our graph implementation.
 */ 
namespace Alg {

    /**
     * DIJKSTRA'S SHORTEST PATH ALGORITHM
     **/
    vector<Edge> shortest_path(const Graph& graph, Vertex start, Vertex end) {
        auto comparison = [](pair<Vertex, double> lhs, pair<Vertex, double> rhs) { return lhs.second > rhs.second; };
        priority_queue<pair<Vertex, double>, vector<pair<Vertex, double>>, decltype(comparison) > pq(comparison);
        pq.push({start, 0});

        unordered_map<Vertex, double> dist;
        unordered_map<Vertex, Edge> prev;
        dist[start] = 0;
        vector<Vertex> vertexes = graph.vertexList;
        for (Vertex v : vertexes) {
            if (v != start) {
                dist[v] = INFINITY;
            }
        }

        while (!pq.empty()) {
            Vertex current = pq.top().first;
            if (current == end) {
                break;
            }
            pq.pop();
            vector<Edge*> adj = graph.incidentEdges(current);
            for (Edge* e : adj) {
                Vertex next = e->destination;
                if (dist[next] > dist[current] + e->weight) {
                    dist[next] = dist[current] + e->weight;
                    pq.push({next, dist[next]});
                    prev[next] = *e;
                }
            }
        }
        
        vector<Edge> path;
        Vertex current = end;
        while (prev.count(current) != 0) {
            path.push_back(prev[current]);
            current = prev[current].source;
        }
        std::reverse(path.begin(), path.end());
        
        return path;
        
    }
    
    /**
     * BREADTH-FIRST SEARCH ALGORITHM
     **/
    std::vector<Vertex> bfs(Graph graph, Vertex start) {
        std::unordered_map<Vertex, int> vertexTracker;
        std::vector<Vertex> toReturnVertices;
        std::queue<Vertex> queue;

        vertexTracker[start] = 1;
        toReturnVertices.push_back(start);
        queue.push(start);
        
        while(!queue.empty()) {
            Vertex current = queue.front();
            queue.pop();
            std::vector<Edge * > adjacentEdges = graph.incidentEdges(current);

            for (unsigned i = 0; i < adjacentEdges.size(); i++) {
                if (vertexTracker.find(adjacentEdges[i]->destination) == vertexTracker.end()) {
                    toReturnVertices.push_back(adjacentEdges[i]->destination);
                    queue.push(adjacentEdges[i]->destination);
                    vertexTracker[adjacentEdges[i]->destination] = 1;
                }
            }
        }

        for (unsigned i =0; i < graph.vertexList.size(); i++) {
            if (vertexTracker.find(graph.vertexList[i]) == vertexTracker.end()) {
                queue.push(graph.vertexList[i]);
                vertexTracker[graph.vertexList[i]] = 1;
                toReturnVertices.push_back(graph.vertexList[i]);

                while(!queue.empty()) {
                    Vertex current = queue.front();
                    queue.pop();
                    std::vector<Edge * > adjacentEdges = graph.incidentEdges(current);
                
                    for (unsigned i = 0; i < adjacentEdges.size(); i++) {
                        if (vertexTracker.find(adjacentEdges[i]->destination) == vertexTracker.end()) {
                            toReturnVertices.push_back(adjacentEdges[i]->destination);
                            queue.push(adjacentEdges[i]->destination);
                            vertexTracker[adjacentEdges[i]->destination] = 1;
                        }
                    }
                }  
            }
        }
        return toReturnVertices;
    }

    /**
     * PAGERANK ALGORITHM
     * Based on CS357 implementation (https://courses.grainger.illinois.edu/cs357/fa2020/assets/lectures/complete-slides/13-Markov-Chains.pdf) 
     */
    std::list<std::pair<Vertex, double>> pagerank(const Graph& graph,  double alpha=0.85, int iterations=1000, double tolerance=1e-7) {
        std::list<std::pair<Vertex, double>> result;
        size_t n = graph.adjacencyList.size();
        std::vector<Vertex> vert_list = graph.vertexList;
        
        ublas::vector<double> x(n);
        std::generate(x.begin(), x.end(), []() {return (rand() % 100) / 100.0;});
        x /= ublas::norm_1(x);
        ublas::matrix<double> M = graph.adjacencyMatrix;
        ublas::matrix<double> ones(n, n, 1.0);
        ublas::matrix<double> G = alpha * M + (1 - alpha) * (1.0/n * ones);
        ublas::vector<double> prevX(n);
        double diff = ublas::norm_2(x);

        while (diff >= tolerance && iterations--) {
            prevX = x;
            x = ublas::prod(G, x);
            diff = ublas::norm_2(x - prevX);
        }

        std::vector<size_t> idx(x.size());
        iota(idx.begin(), idx.end(), 0);
        std::stable_sort(idx.begin(), idx.end(), [&x](size_t ind_one, size_t ind_two) {return x(ind_one) > x(ind_two);});

        for(size_t i : idx) {
            result.emplace_back(std::make_pair(vert_list[i], x[i]));
        }
        return result;
    }
}