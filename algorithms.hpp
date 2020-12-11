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

namespace ublas = boost::numeric::ublas;
using std::priority_queue;
using Edge = Graph::Edge;
using std::vector;
using std::cout;
using std::endl;
using std::pair;
using std::string;
using std::unordered_map;
typedef std::string Vertex;

/* If we don't want to have this templated that's fine too, we will likely just use vertices instead of ints like Geeks for Geeks did */ 
/* Might not be easily doable without explicity using Vertex and such anyways! */

namespace Alg {
    vector<Edge> shortest_path(const Graph& graph, Vertex start, Vertex end) {
        //https://www.geeksforgeeks.org/c-program-for-dijkstras-shortest-path-algorithm-greedy-algo-7/
        // set up priority queue
        auto comparison = [](pair<Vertex, double> lhs, pair<Vertex, double> rhs) { return lhs.second > rhs.second; };
        priority_queue<pair<Vertex, double>, vector<pair<Vertex, double>>, decltype(comparison) > pq(comparison);
        pq.push({start, 0});

        // set up distance map

        unordered_map<Vertex, double> dist;
        unordered_map<Vertex, Edge> prev;
        dist[start] = 0;
        vector<Vertex> vertexes = graph.vertexList;
        for (Vertex v : vertexes) {
            if (v != start) {
                dist[v] = INFINITY;
            }
        }

        // algorithm time

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
        // reconstruct path
        vector<Edge> path;
        Vertex current = end;
        while (prev.count(current) != 0) {
            path.push_back(prev[current]); // can't just insert at the beginning bc weird constructor error
            current = prev[current].source;
        }
        std::reverse(path.begin(), path.end()); // so i just reversed the list later
        
        return path;
        
    }

    // template <class G, class V>
    std::vector<Vertex> bfs(Graph graph, Vertex start) {
        //https://www.geeksforgeeks.org/breadth-first-search-or-bfs-for-a-graph/


        std::unordered_map<Vertex, int> vertexTracker;
        vertexTracker[start] = 1;


        std::vector<Vertex> toReturnEdges;
        toReturnEdges.push_back(start);
        //toReturnEdges.reserve(30);
        std::queue<Vertex> queue;

        queue.push(start);
        while(!queue.empty()) {
            Vertex current = queue.front();
            queue.pop();

            std::vector<Edge * > adjacentEdges = graph.incidentEdges(current);

            for (unsigned i = 0; i < adjacentEdges.size(); i++) {

                if (vertexTracker.find(adjacentEdges[i]->destination) == vertexTracker.end()) {
                    
                    toReturnEdges.push_back(adjacentEdges[i]->destination);
                    queue.push(adjacentEdges[i]->destination);
                    vertexTracker[adjacentEdges[i]->destination] = 1;
                }
            }

        }

        for (unsigned i =0; i < graph.vertexList.size(); i++) {
            if (vertexTracker.find(graph.vertexList[i]) == vertexTracker.end()) {
                queue.push(graph.vertexList[i]);
                vertexTracker[graph.vertexList[i]] = 1;
                toReturnEdges.push_back(graph.vertexList[i]);


                while(!queue.empty()) {
                Vertex current = queue.front();
                queue.pop();

                std::vector<Edge * > adjacentEdges = graph.incidentEdges(current);

                for (unsigned i = 0; i < adjacentEdges.size(); i++) {

                    if (vertexTracker.find(adjacentEdges[i]->destination) == vertexTracker.end()) {
                    
                        toReturnEdges.push_back(adjacentEdges[i]->destination);
                        queue.push(adjacentEdges[i]->destination);
                        vertexTracker[adjacentEdges[i]->destination] = 1;
                    }
                }

                }   

            }
        }

        return toReturnEdges;
    }

    // template <class G>
    std::list<std::pair<Vertex, double>> pagerank(const Graph& graph,  double alpha, int iterations, double tolerance) {
        //https://www.geeksforgeeks.org/page-rank-algorithm-implementation/
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