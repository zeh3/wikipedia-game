#define CATCH_CONFIG_MAIN
#include "./catch/catch.hpp"
#include "../graph.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include "../algorithms.hpp"

using std::string;
using std::vector;
using std::ifstream; 
using std::cout; 
using std::endl;
using boost::numeric::ublas::matrix;
using Edge = Graph::Edge;

typedef std::string Vertex;

/*
* the graph for the following test cases looks like this:
* A --> B --> C
*/

Graph createSimpleGraph() {
    Graph graph;
    graph.insertVertex("A");
    graph.insertVertex("B");
    graph.insertVertex("C");

    graph.insertEdge("A", "B");
    graph.insertEdge("B", "C");

    graph.createAdjMat();

    return graph;
}

Graph createBasicDisconnectedGraph() {
    Graph graph;

    graph.insertVertex("A");
    graph.insertVertex("B");
    graph.insertVertex("C");
    graph.insertVertex("D");
    graph.insertVertex("E");
    graph.insertVertex("F");
    graph.insertVertex("G");
    graph.insertVertex("H");
    graph.insertVertex("I");

    graph.insertEdge("A","B");
    graph.insertEdge("A","C");
    graph.insertEdge("B","C");
    graph.insertEdge("B","D");
    graph.insertEdge("E","F");
    graph.insertEdge("F","G");
    graph.insertEdge("G","H");

    graph.createAdjMat();

    return graph;
}

Graph createMediumCircleGraph() {
    Graph graph;
    graph.insertVertex("A");
    graph.insertVertex("B");
    graph.insertVertex("C");
    graph.insertVertex("D");
    graph.insertVertex("E");
    graph.insertVertex("F");
    graph.insertVertex("G");
    graph.insertVertex("H");

    graph.insertEdge("A", "B");
    graph.insertEdge("B", "C");
    graph.insertEdge("C", "D");
    graph.insertEdge("D", "E");
    graph.insertEdge("E", "F");
    graph.insertEdge("F", "G");
    graph.insertEdge("G", "H");

    graph.createAdjMat();

    return graph;
}


// for checking adjacency matrix things
int transformCoordinates(int x, int y, int size) {
    return size * y + x;
}

bool tolerable(double expected, double actual) {
    return std::fabs(expected - actual) < FLT_EPSILON;
}

bool pr_comparison(vector<double> expected, vector<double> actual) {
    if(expected.size() != actual.size()) return false;
    for(auto it1 = expected.begin(), it2 = actual.begin(); it1 != expected.end() && it2 != actual.end(); it1++, it2++) {
        if(!tolerable(*it1, *it2)) return false;
    }
    return true;
}

TEST_CASE("Equals operator", "[ruleof3]") {
    Graph g1 = createBasicDisconnectedGraph();
    Graph g2 = createBasicDisconnectedGraph();
    Graph g3 = createMediumCircleGraph();

    REQUIRE(g1 == g2);
    REQUIRE(!(g2 == g3));
}

TEST_CASE("Copy constructor", "[ruleof3]") {
    Graph g1 = createSimpleGraph();
    Graph g2(g1);

    REQUIRE(g1 == g2);
}

TEST_CASE("Assignment operator", "[ruleof3]") {
    Graph g1 = createSimpleGraph();
    Graph g2 = g1;
    REQUIRE(g2 == createSimpleGraph());
}

TEST_CASE("simple graph insert vertices", "[defaultConstructor][insertVertex][vertexList][simpleGraph]") {
    Graph graph = createSimpleGraph();
    vector<Vertex> vertexList = graph.vertexList;
    REQUIRE(vertexList.size() == 3);
    REQUIRE(std::count(vertexList.begin(), vertexList.end(), "A") == 1);
    REQUIRE(std::count(vertexList.begin(), vertexList.end(), "B") == 1);
    REQUIRE(std::count(vertexList.begin(), vertexList.end(), "C") == 1);
}

TEST_CASE("simple graph adjacencies correct", "[defaultConstructor][insertVertex][insertEdge][incidentEdges][areAdjacent][simpleGraph]") {
    Graph graph = createSimpleGraph();
    // check incident edges size
    REQUIRE(graph.incidentEdges("A").size() == 1);
    REQUIRE(graph.incidentEdges("B").size() == 1);
    REQUIRE(graph.incidentEdges("C").size() == 0);

    //check incident edges contents
    REQUIRE(graph.incidentEdges("A")[0]->source == "A");
    REQUIRE(graph.incidentEdges("A")[0]->destination == "B");

    REQUIRE(graph.incidentEdges("B")[0]->source == "B");
    REQUIRE(graph.incidentEdges("B")[0]->destination == "C");

    // check areAdjacent
    REQUIRE(graph.areAdjacent("A", "B"));
    REQUIRE(graph.areAdjacent("B", "C"));
    REQUIRE(!graph.areAdjacent("A", "C"));
}
    
TEST_CASE("simple graph adjacency matrix", "[defaultConstructor][insertVertex][insertEdge][simpleGraph][adjacencyMatrix][vertexList]") {
     Graph graph = createSimpleGraph();

     matrix<double> mat = graph.adjacencyMatrix;
     //size
     REQUIRE(mat.size1() == 3);
     REQUIRE(mat.size2() == 3);

     auto v = graph.vertexList;

     size_t AIndex = std::find(v.begin(), v.end(), "A") - v.begin();
     auto BIndex = std::find(v.begin(), v.end(), "B") - v.begin();
     auto CIndex = std::find(v.begin(), v.end(), "C") - v.begin();
     //nonzero values
     REQUIRE(mat(BIndex, AIndex) == 1);
     REQUIRE(mat(CIndex, BIndex) == 1);
     //diaganols
     REQUIRE(mat(AIndex, AIndex) == 0);
     REQUIRE(mat(BIndex, BIndex) == 0);
     REQUIRE(mat(CIndex, CIndex) == 1.0 / 3.0);
     //reversed edges
     REQUIRE(mat(AIndex, BIndex) == 0);
     REQUIRE(mat(BIndex, CIndex) == 1.0 / 3.0);
     //everything else lol
     REQUIRE(mat(AIndex, CIndex) == 1.0 / 3.0);
     REQUIRE(mat(CIndex, AIndex) == 0);
}

/*
* The graph for these test cases can be found in connected_graph.JPG
*/

TEST_CASE("vertexList for connected graph is correct", "[ifstreamConstructor][vertexList][connectedGraph]") {
    ifstream file("tests/connected_graph.tsv");
    Graph graph(file);
    auto v = graph.vertexList;
    vector<string> actualLabels = {"A", "B", "C", "D", "E", "F", "G"};

    REQUIRE(v.size() == actualLabels.size());
    
    for (Vertex label : actualLabels) {
        REQUIRE(std::count(v.begin(), v.end(), label) == 1);
    }
}

TEST_CASE("connected graph adjacencies correct", "[incidentEdges][areAdjacent][ifstreamConstructor][connectedGraph]") {
    ifstream file("tests/connected_graph.tsv");
    Graph graph(file);

    // verify that everything is adjacent to center vertex
    vector<string> others = {"A", "B", "C", "D", "F", "G"};
    for (auto label : others) {
        REQUIRE(graph.areAdjacent("E", label));
    }

    auto i = graph.incidentEdges("E");
    vector<string> destinations;
    for (Edge* e : i) {
        REQUIRE((e->source) == "E");
        destinations.push_back((e->destination));
    }

    for (auto label: others) {
        REQUIRE(std::count(destinations.begin(), destinations.end(), label) == 1);
    }

    // check (some of) the outer vertexes
    REQUIRE(graph.areAdjacent("F", "A"));
    REQUIRE(graph.areAdjacent("G", "C"));
    REQUIRE(!graph.areAdjacent("A", "C")); 
    REQUIRE(!graph.areAdjacent("D", "C"));

    REQUIRE(graph.incidentEdges("C").size() == 1);
    REQUIRE(graph.incidentEdges("B").size() == 1);
}

TEST_CASE("connected graph adjacency matrix", "[ifstreamConstructor][connectedGraph][adjacencyMatrix]") {
    ifstream file("tests/connected_graph.tsv");
    Graph graph(file);
    auto actual = graph.adjacencyMatrix;
    int size = 7;

    REQUIRE(actual.size1() == size);
    REQUIRE(actual.size2() == size);

    /*vector<vector<double>> expected = { {0, 0, 0, 0.5, 0, 0, 0}, {0, 0, 0, 0, 0, .5, 0}, 
    {0, 0.5, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0.5}, {0.5, 0.5, 0.5, 0.5, 0, 0.5, 0.5},
    {0.5, 0, 0, 0, 0, 0, 0}, {0, 0, 0.5, 0, 0, 0, 0}};*/

    vector<Vertex> vertexList = graph.vertexList;
    auto C = std::find(vertexList.begin(), vertexList.end(), "C") - vertexList.begin();
    auto B = std::find(vertexList.begin(), vertexList.end(), "B") - vertexList.begin();
    auto F = std::find(vertexList.begin(), vertexList.end(), "F") - vertexList.begin();
    auto E = std::find(vertexList.begin(), vertexList.end(), "E") - vertexList.begin();

    // check a few diaganols
    REQUIRE(actual(C, C) == 0);
    REQUIRE(actual(B, B) == 0);
    REQUIRE(actual(F, F) == 0);
    REQUIRE(actual(E, E) == 0);

    // a few expected 1.0s
    REQUIRE(actual(B, C) == 1.0);
    REQUIRE(actual(F, B) == 1.0);

    // a few expected 1 / 6
    REQUIRE(actual(C, E) == 1.0 / 6.0);
    REQUIRE(actual(B, E) == 1.0 / 6.0);
    REQUIRE(actual(F, E) == 1.0 / 6.0);

    // a few reverse edges
    REQUIRE(actual(C, B) == 0);
    REQUIRE(actual(B, F) == 0);

    //just some random thing that should be 0
    REQUIRE(actual(C, F) == 0);
    REQUIRE(actual(F, C) == 0);
    REQUIRE(actual(E, C) == 0);
    REQUIRE(actual(E, B) == 0);
    REQUIRE(actual(E, F) == 0);
}

// dijkstra's

TEST_CASE("unweighted graph constructor defaults to 1", "[ifstreamConstructor][adjacencyList][edge]") {
    ifstream file("tests/disconnected_graph.tsv");
    Graph graph(file);
    auto adjList = graph.adjacencyList;

    for (auto pairs : adjList) {
        auto edges = pairs.second;
        for (Edge* e : edges) {
            REQUIRE(e->weight == 1);
        }
    }
}

TEST_CASE("weighted graph constructor works", "[ifstreamConstructor][adjacencyList][edge]") {
    ifstream file("tests/connected_graph_weights.tsv");
    Graph graph(file, true);

    auto adjList = graph.adjacencyList;
    // test a few weights
    REQUIRE(adjList["C"][0]->weight == 0);
    REQUIRE(adjList["D"][0]->weight == 1);
    REQUIRE(adjList["A"][0]->weight == 1);
    REQUIRE(adjList["B"][0]->weight == 0);
}

TEST_CASE("shortest path of 0s", "[shortestPath]") {
    ifstream file("tests/connected_graph_weights.tsv");
    Graph graph(file, true);

    vector<Edge> path = Alg::shortest_path(graph, "E", "F");
    double total_weight = 0;

    for (Edge e : path) {
        total_weight += e.weight;
    }

    vector<Edge> expectedPath = {Edge("E", "C", 0), Edge("C", "B", 0), Edge("B", "F", 0)};

    REQUIRE(total_weight == 0);
    REQUIRE(path == expectedPath);
}

TEST_CASE("shortest path of length 1", "[shortestPath]") {
    ifstream file("tests/connected_graph_weights.tsv");
    Graph graph(file, true);

    vector<Edge> expectedPath = {Edge("E", "G", 1)};
    REQUIRE(Alg::shortest_path(graph, "E", "G") == expectedPath);
}

TEST_CASE("invalid paths", "[shortestPath]") {
    ifstream file("tests/disconnected_graph.tsv");
    Graph graph(file);

    vector<Edge> disconnected_path = Alg::shortest_path(graph, "A", "F");
    REQUIRE(disconnected_path.size() == 0);

    vector<Edge> same_start_end = Alg::shortest_path(graph, "H", "H");
    REQUIRE(same_start_end.size() == 0);

    vector<Edge> no_path = Alg::shortest_path(graph, "C", "B");
    REQUIRE(no_path.size() == 0);
}

TEST_CASE("non-zero weighted path in complex graph", "[shortestPath]") {
    ifstream file("tests/complex_graph_weights.tsv");
    Graph graph(file, true);

    vector<Edge> expected = {Edge("A", "E", 1), Edge("E", "I", 0.5), Edge("I", "K", 0.5), Edge("K", "L", 1)};
    vector<Edge> actual = Alg::shortest_path(graph, "A", "L");
    REQUIRE(actual == expected);
}

TEST_CASE("short path in complex graph", "[shortestPath]") {
    ifstream file("tests/complex_graph_weights.tsv");
    Graph graph(file, true);

    vector<Edge> expected = {Edge("D", "C", 1)};
    vector<Edge> actual = Alg::shortest_path(graph, "D", "C");
    REQUIRE(actual == expected);
}

TEST_CASE("non-zero weighted path in disconnected graph") {
    ifstream file("tests/disconnected_graph_weights.tsv");
    Graph graph(file, true);

    vector<Edge> expected = {Edge("E", "G", 2), Edge("G", "H", 1.5)};
    vector<Edge> actual = Alg::shortest_path(graph, "E", "H");
    REQUIRE(actual == expected);
}

TEST_CASE("Connected graph PageRank", "[pagerank]") {
    ifstream file("tests/connected_graph.tsv");
    Graph graph(file);

    // vector<Vertex> expected_verts = {"A", "B", "C", "D", "E", "F", "G"};
    vector<double> expected_scores = {0.16309524, 0.16309524, 0.16309524, 0.16309524, 0.16309524, 0.16309524,
                                      0.02142857};

    auto results = Alg::pagerank(graph);
    vector<double> actual_scores;
    std::transform(results.begin(), results.end(), std::back_inserter(actual_scores), [](auto pair) { return pair.second; });

    REQUIRE(pr_comparison(actual_scores, expected_scores) == true);
}

TEST_CASE("Disconnected graph PageRank", "[pagerank]") {
    ifstream file("tests/disconnected_graph.tsv");
    Graph graph(file);

    // vector<Vertex> expected_verts = {"A", "B", "C", "D", "E", "F", "G", "H"};
    vector<double> expected_scores = {0.27403041, 0.26382188, 0.1430203 , 0.1430203 , 0.07028836,
                                      0.04402678, 0.03089598, 0.03089598};

    auto results = Alg::pagerank(graph);
    vector<double> actual_scores;
    std::transform(results.begin(), results.end(), std::back_inserter(actual_scores), [](auto pair) { return pair.second; });

    REQUIRE(pr_comparison(actual_scores, expected_scores) == true);
}

TEST_CASE("Complex graph PageRank", "[pagerank]") {
    ifstream file("tests/complex_graph.tsv");
    Graph graph(file);

    // vector<Vertex> expected_verts = {"A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L"};
    vector<double> expected_scores = {0.21098858, 0.15846934, 0.15011459, 0.10217013, 0.09473939,
        0.06646371, 0.06348671, 0.05946397, 0.05660358, 0.0125, 0.0125, 0.0125};

    auto results = Alg::pagerank(graph);
    vector<double> actual_scores;
    std::transform(results.begin(), results.end(), std::back_inserter(actual_scores), [](auto pair) { return pair.second; });

    REQUIRE(pr_comparison(actual_scores, expected_scores) == true);
}

TEST_CASE("Test Circular BFS Traversal", "[BFS][defaultConstructor][connectedGraph]") {
    Graph graph = createMediumCircleGraph();
    Vertex start = graph.vertexList[0];
    std::vector<Vertex> result = Alg::bfs(graph, start);

    REQUIRE(result[0] == "A");
    REQUIRE(result[1] == "B");
    REQUIRE(result[2] == "C");
    REQUIRE(result[3] == "D");
    REQUIRE(result[4] == "E");
    REQUIRE(result[5] == "F");
    REQUIRE(result[6] == "G");
    REQUIRE(result[7] == "H");
}

TEST_CASE("Test Basic Disconnected Graph", "[BFS][defaultConstructor][disconnectedGraph]") {
    Graph graph = createBasicDisconnectedGraph();

    Vertex start = graph.vertexList[0];
    std::vector<Vertex> result = Alg::bfs(graph, start);

    REQUIRE(result[0] == "A");
    REQUIRE(result[1] == "C");
    REQUIRE(result[2] == "B");
    REQUIRE(result[3] == "D");
    REQUIRE(result[4] == "E");
    REQUIRE(result[5] == "F");
    REQUIRE(result[6] == "G");
    REQUIRE(result[7] == "H");
    REQUIRE(result[8] == "I");
}

TEST_CASE("BFS with One vertex", "[BFS][defaultConstructor][connectedGraph]") {
    Graph graph;
    graph.insertVertex("A");
    graph.createAdjMat();

    Vertex start = graph.vertexList[0];
    std::vector<Vertex> result = Alg::bfs(graph, start);

    REQUIRE(result[0] == "A");
}

TEST_CASE("Disconnected BFS with input stream", "[BFS][ifStreamConstructor][disconnectedGraph]") {
    ifstream file("tests/disconnected_graph.tsv");
    Graph graph(file);

    Vertex start = graph.vertexList[0];
    std::vector<Vertex> result = Alg::bfs(graph, start);

    REQUIRE(result[0] == "A");
    REQUIRE(result[1] == "B");
    REQUIRE(result[2] == "C");
    REQUIRE(result[3] == "D");
    REQUIRE(result[4] == "E");
    REQUIRE(result[5] == "F");
    REQUIRE(result[6] == "G");
    REQUIRE(result[7] == "H");
}

TEST_CASE("complex BFS with input stream", "[BFS][ifStreamConstructor][disconnectedGraph]") {
    ifstream file("tests/complex_graph.tsv");
    Graph graph(file);

    Vertex start = graph.vertexList[0];
    std::vector<Vertex> result = Alg::bfs(graph, start);

    REQUIRE(result[0] == "A");
    REQUIRE(result[1] == "E");
    REQUIRE(result[2] == "K");
    REQUIRE(result[3] == "J");
    REQUIRE(result[4] == "C");
    REQUIRE(result[5] == "I");
    REQUIRE(result[6] == "H");
    REQUIRE(result[7] == "L");
    REQUIRE(result[8] == "B");
    REQUIRE(result[9] == "F");
    REQUIRE(result[10] == "D");
    REQUIRE(result[11] == "G");
}

TEST_CASE("Test  Disconnected Graph starting in the middle of vertex List" , "[BFS][defaultConstructor][disconnectedGraph]") {
    Graph graph = createBasicDisconnectedGraph();

    Vertex start = graph.vertexList[4];
    std::vector<Vertex> result = Alg::bfs(graph, start);

    REQUIRE(result[0] == "E");
    REQUIRE(result[1] == "F");
    REQUIRE(result[2] == "G");
    REQUIRE(result[3] == "H");
    REQUIRE(result[4] == "A");
    REQUIRE(result[5] == "C");
    REQUIRE(result[6] == "B");
    REQUIRE(result[7] == "D");
    REQUIRE(result[8] == "I");
}
