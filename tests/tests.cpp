#define CATCH_CONFIG_MAIN
#include "./catch/catch.hpp"
#include "../graph.h"
#include <iostream>
#include <vector>
#include "../algorithms.hpp"
#include <unordered_map>

using std::string;
using Edge = Graph::Edge;
using std::vector;
using std::ifstream;
using std::cout;
using std::endl;
using boost::numeric::ublas::matrix;

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
Graph createMediumGraph() {
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
    graph.insertEdge("E", "F");
    graph.insertEdge("G", "H");
    graph.insertEdge("H", "A");
    graph.insertEdge("A", "D");
    graph.insertEdge("H", "C");
    graph.insertEdge("B", "F");
    graph.insertEdge("A", "E");

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
    /*
TEST_CASE("simple graph adjacency matrix", "[defaultConstructor][insertVertex][insertEdge][simpleGraph][adjacencyMatrix][vertexList]") {
     Graph graph = createSimpleGraph();
     matrix<double> mat = graph.adjacencyMatrix;
     //size
     REQUIRE(sizeof(mat) / sizeof(mat[0]) == 9);

     auto v = graph.vertexList;
     size_t AIndex = std::find(v.begin(), v.end(), "A") - v.begin();
     auto BIndex = std::find(v.begin(), v.end(), "B") - v.begin();
     auto CIndex = std::find(v.begin(), v.end(), "C") - v.begin();
     //nonzero values
     REQUIRE(mat[transformCoordinates(AIndex, BIndex, 3)] == 1);
     REQUIRE(mat[transformCoordinates(BIndex, CIndex, 3)] == 1);
     //diaganols
     REQUIRE(mat[transformCoordinates(AIndex, AIndex, 3)] == 0);
     REQUIRE(mat[transformCoordinates(BIndex, BIndex, 3)] == 0);
     REQUIRE(mat[transformCoordinates(CIndex, CIndex, 3)] == 0);
     //reversed edges
     REQUIRE(mat[transformCoordinates(BIndex, AIndex, 3)] == 0);
     REQUIRE(mat[transformCoordinates(CIndex, BIndex, 3)] == 0);
     //everything else lol
     REQUIRE(mat[transformCoordinates(AIndex, CIndex, 3)] == 0);
     REQUIRE(mat[transformCoordinates(CIndex, AIndex, 3)] == 0);
}
*/
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
/*
TEST_CASE("connected graph adjacency matrix", "[ifstreamConstructor][connectedGraph][adjacencyMatrix]") {
    int size = 7;
    ifstream file("tests/connected_graph.tsv");
    Graph graph(file);
    auto actual = graph.adjacencyMatrix;
    REQUIRE (sizeof(actual) / sizeof(actual[0]) == (size * size));
    vector<vector<double>> expected = { {0, 0, 0, 0.5, 0, 0, 0}, {0, 0, 0, 0, 0, .5, 0}, 
    {0, 0.5, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0.5}, {0.5, 0.5, 0.5, 0.5, 0, 0.5, 0.5},
    {0.5, 0, 0, 0, 0, 0, 0}, {0, 0, 0.5, 0, 0, 0, 0}};

    vector<Vertex> vertexList = graph.vertexList;
    auto C = std::find(vertexList.begin(), vertexList.end(), "C") - vertexList.begin();
    auto B = std::find(vertexList.begin(), vertexList.end(), "B") - vertexList.begin();
    auto F = std::find(vertexList.begin(), vertexList.end(), "F") - vertexList.begin();

    // check a few diaganols
    REQUIRE(actual[transformCoordinates(C, C, size)] == 0);
    REQUIRE(actual[(transformCoordinates(C, C, size))] == 0);
    REQUIRE(actual[(transformCoordinates(C, C, size))] == 0);

    // a few expected 0.5s
    REQUIRE(actual[transformCoordinates(C, B, size)] == 0.5);
    REQUIRE(actual[transformCoordinates(B, F, size)] == 0.5);

    // a few reverse edges
    REQUIRE(actual[transformCoordinates(B, C, size)] == 0);
    REQUIRE(actual[transformCoordinates(F, B, size)] == 0);

    //just some random thing that should be 0
    REQUIRE(actual[transformCoordinates(F, C, size)] == 0);
    REQUIRE(actual[transformCoordinates(C, F, size)] == 0);


}
*/
TEST_CASE("basic bfs test") {
    Graph graph = createMediumGraph();
    Vertex start = graph.vertexList[0];
    std::vector<std::pair<Edge *, std::string>> result = Alg::bfs(graph, start);

    for (unsigned i = 0; i < result.size(); i++) {
        std::cout << result[i].first->source << " " << result[i].first->destination << " " <<result[i].second << std::endl;
    }

    std::unordered_map<Vertex, int> vertexTracker;

   for (unsigned i = 0; i < result.size(); i++) {
        if (vertexTracker.find(result[i].first->destination) != vertexTracker.end()) {
            REQUIRE(result[i].second == "cross");
        } else {
            REQUIRE(result[i].second == "discovery");

        }

       vertexTracker[result[i].first->source] = 1;
       vertexTracker[result[i].first->destination] = 1;

   }
}
