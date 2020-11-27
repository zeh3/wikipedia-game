#include "graph.h"

Graph::Graph() {

}

Graph::~Graph() {
    adjacencyList.clear();
    adjacencyMatrix.clear();
    vertexList.clear();
}
        
void Graph::insertVertex(Vertex v) {
    //adding to vertex list
    vertexList.push_back(v);

    //adding to adjacency list
    //maybe need to do a clear here?
    adjacencyList[v] = std::vector<Edge *>();



    //add to matrix

    //resize outer matrix
    int size = adjacencyMatrix.size();
    adjacencyMatrix.resize(size + 1);
    //loop through inner matrix and resize
    for (int i = 0; i < size + 1; i++) {
        int innerSize = adjacencyMatrix[i].size();
        adjacencyMatrix[i].resize(innerSize + 1);

    }




}

void Graph::insertEdge(Vertex v1, Vertex v2, Edge theEdge) {
    //Edge myEdge = new Edge();

}

std::vector<Graph::Edge*> Graph::incidentEdges(Vertex v) {
    std::vector<Graph::Edge*> incidentEdges;
    incidentEdges.push_back(&Graph::Edge());
    return incidentEdges;
}

bool Graph::areAdjacent(Vertex v1, Vertex v2) {

}