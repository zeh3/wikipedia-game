#include "graph.h"

Graph::Graph() {

}

Graph::~Graph() {
    adjacencyList.clear();
    adjacencyMatrix.clear();
    vertexList.clear();
}
        
void Graph::insertVertex(Vertex v) {

}

void Graph::insertEdge(Vertex v1, Vertex v2, Edge theEdge) {

}

std::vector<Graph::Edge*> Graph::incidentEdges(Vertex v) {
    std::vector<Graph::Edge*> incidentEdges;
    incidentEdges.push_back(&Graph::Edge());
    return incidentEdges;
}

bool Graph::areAdjacent(Vertex v1, Vertex v2) {

}