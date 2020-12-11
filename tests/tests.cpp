#define CATCH_CONFIG_MAIN
#include "./catch/catch.hpp"
#include "../graph.h"
#include <iostream>
#include <vector>
#include "../algorithms.hpp"

using std::string, std::vector, std::ifstream, std::cout, std::endl;
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
    // graph.printAdjMat();

    return graph;
}

// for checking adjacency matrix things
int transformCoordinates(int x, int y, int size) {
    return size * y + x;
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
    cout << "done with graph" << endl;
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
    int size = 7;
    ifstream file("tests/connected_graph.tsv");
    Graph graph(file);
    auto actual = graph.adjacencyMatrix;

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