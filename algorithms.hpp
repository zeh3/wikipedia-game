#include <iostream>
#include <queue>
#include "graph.h"
#include <string>
#include <boost/numeric/ublas/assignment.hpp>
#include <boost/numeric/ublas/vector.hpp>
#include <algorithm>
#include <numeric>

namespace ublas = boost::numeric::ublas;
using std::priority_queue;
using Edge = Graph::Edge;
using std::vector;
using std::cout;
using std::endl;

/* If we don't want to have this templated that's fine too, we will likely just use vertices instead of ints like Geeks for Geeks did */ 
/* Might not be easily doable without explicity using Vertex and such anyways! */

namespace Alg {
    vector<Edge> shortest_path(const Graph& graph, Vertex start, Vertex end) {
        //https://www.geeksforgeeks.org/c-program-for-dijkstras-shortest-path-algorithm-greedy-algo-7/

        auto comparison = [](Edge lhs, Edge rhs) { return lhs.weight > rhs.weight; };
        priority_queue<Edge, vector<Edge>, decltype(comparison) > pq(comparison);
        
        vector<Edge> path;


        return path;
        
    }

    // template <class G, class V>
    void bfs(const Graph& graph, Vertex start) {
        //https://www.geeksforgeeks.org/breadth-first-search-or-bfs-for-a-graph/
        std::cout << "\nBFS\n";
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