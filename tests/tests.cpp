#define CATCH_CONFIG_MAIN
#include "./catch/catch.hpp"
#include "../graph.h"
#include <iostream>
#include <vector>

using std::string;
using Edge = Graph::Edge;
using std::vector;

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

    Edge AToB("A", "B");
    // AToB.source = new string("A");
    // AToB.destination = new string("B");
    graph.insertEdge("A", "B", AToB);

    Edge BToC("B", "C");
    // BToC.source = new string("B");
    // BToC.destination = new string("C");
    graph.insertEdge("B", "C", BToC);

    return graph;
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

// TEST_CASE("simple graph adjacency matrix", "[defaultConstructor][insertVertex][insertEdge][simpleGraph][adjacencyMatrix][vertexList]") {
//     Graph graph = createSimpleGraph();
//     auto mat = graph.adjacencyMatrix;
//     //size
//     REQUIRE(mat.size() == 3);
//     REQUIRE(mat[0].size() == 3);
//     REQUIRE(mat[1].size() == 3);
//     REQUIRE(mat[2].size() == 3);

//     auto v = graph.vertexList;
//     size_t AIndex = std::find(v.begin(), v.end(), "A") - v.begin();
//     auto BIndex = std::find(v.begin(), v.end(), "B") - v.begin();
//     auto CIndex = std::find(v.begin(), v.end(), "C") - v.begin();
//     //nonzero values
    
//     REQUIRE(mat[AIndex][BIndex] == 1);
//     REQUIRE(mat[BIndex][CIndex] == 1);
//     //diaganols
//     REQUIRE(mat[AIndex][AIndex] == 0);
//     REQUIRE(mat[BIndex][BIndex] == 0);
//     REQUIRE(mat[CIndex][CIndex] == 0);
//     //reversed edges
//     REQUIRE(mat[BIndex][AIndex] == 0);
//     REQUIRE(mat[CIndex][BIndex] == 0);
//     //everything else lol
//     REQUIRE(mat[AIndex][CIndex] == 0);
//     REQUIRE(mat[CIndex][AIndex] == 0);
// }
