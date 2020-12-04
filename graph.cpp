#include "graph.h"
#include <iostream>

Graph::Graph() {
    // adjacencyMatrix = std::vector<std::vector<double>>(0, std::vector<double>(0,0)); 

}

Graph::Graph(std::ifstream& fileStream) {
    Vertex V1, V2;
    while(!fileStream.eof()) {
        std::getline (fileStream, V1, '\t');
        std::getline (fileStream, V2, '\n');
        adjacencyList[V1].push_back(new Graph::Edge(V1, V2));
        if (adjacencyList.find(V2) == adjacencyList.end()) adjacencyList[V2] = std::vector<Graph::Edge *>();
    }
}

Graph::~Graph() {
    // adjacencyList.clear();
    // adjacencyMatrix.clear();
    vertexList.clear();

    for (std::pair<Vertex, std::vector<Graph::Edge *>> child : adjacencyList) {
        for (int i = 0; i < (int) child.second.size(); i++) if (child.second[i]) delete child.second[i];
    }
}

//complete        
void Graph::insertVertex(Vertex v) {
    //adding to vertex list
    vertexList.push_back(v);

    //adding to adjacency list
    //maybe need to do a clear here?
    adjacencyList[v] = std::vector<Edge *>();



    // //resize outer matrix
    // unsigned size = adjacencyMatrix.size();
    
    // adjacencyMatrix.resize(size + 1.0);

    // //loop through inner matrix and resize
    // if (adjacencyMatrix.size() > 1) {
    //     for (unsigned i = 0; i < adjacencyMatrix.size(); i++) {
    //         unsigned innserSize = adjacencyMatrix[i].size();
    //         adjacencyMatrix[i].resize(size + 1);

    //     }
    // }




}

//complete
void Graph::insertEdge(Vertex v1, Vertex v2, Edge theEdge) {

    //grab a reference to the vector in my unordered map

    std::vector<Edge*> & edges = adjacencyList[v1];
    //insert the edge to the vertex
    edges.insert(edges.begin(), new Edge(theEdge.source, theEdge.destination));

    // loop through vertices list and find indeces;
    int firstVertex = 0;
    int secondVertex = 0;
    //loop through vertex list
    // for (unsigned i = 0; i < vertexList.size(); i++) {
    //     if (vertexList[i] ==  v1) {
    //         firstVertex = i;
    //     } else if (vertexList[i] == v2) {
    //         secondVertex = i;
    //     }
    // }

    // //adjust matrix appropiatley
    // if (adjacencyMatrix[firstVertex][secondVertex] == 0) {

    //     adjacencyMatrix[firstVertex][secondVertex] = 1;

    // } else {
    //     double recip = 1 / adjacencyMatrix[firstVertex][secondVertex];

    //     recip +=1;

    //     adjacencyMatrix[firstVertex][secondVertex] = 1/ recip;

    // }




}

//completed
std::vector<Graph::Edge*> Graph::incidentEdges(Vertex v) {

    std::vector<Graph::Edge*> incidentEdges = adjacencyList[v];

    return incidentEdges;
}
//completed
bool Graph::areAdjacent(Vertex v1, Vertex v2) {

    int indexOne = 0;
    int indexTwo = 0;
    //loop through vertexList to get Indices
    // for (unsigned  i = 0; i < vertexList.size(); i++) {
    //     if (vertexList[i] == v1) {
    //         indexOne = i;
    //     } else if (vertexList[i] ==(v2)) {
    //         indexTwo = i;
    //     }
    // }

    // if (adjacencyMatrix[indexOne][indexTwo] != 0) {
    //     return true;
    // }

    return false;
}