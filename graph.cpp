#include "graph.h"
#include <iostream>

Graph::Graph(std::ifstream& fileStream) {
    Vertex V1, V2;
    while(!fileStream.eof()) {
        std::getline(fileStream, V1, '\t');
        std::getline(fileStream, V2, '\n');
        
        if (vert_to_ind.find(V1) == vert_to_ind.end()) { 
            vert_to_ind[V1] = vert_to_ind.size();
            vertexList.push_back(V1);
        }

        adjacencyList[V1].push_back(new Graph::Edge(V1, V2));
        
        if (adjacencyList.find(V2) == adjacencyList.end()) { 
            adjacencyList[V2] = std::vector<Graph::Edge *>();
            vert_to_ind.insert(std::make_pair(V2, vert_to_ind.size()));
            vertexList.push_back(V2);
        }
    }
    
    createAdjMat();
}

Graph::~Graph() {
    vert_to_ind.clear();
    vertexList.clear();

    for (std::pair<Vertex, std::vector<Graph::Edge *>> child : adjacencyList) {
        for (int i = 0; i < (int) child.second.size(); i++) if (child.second[i]) delete child.second[i];
    }
}

// createAdjMat() must be called after all insertions are complete!
void Graph::insertVertex(Vertex v) {
    //adding to vertex list
    vert_to_ind[v] = vert_to_ind.size();
    vertexList.push_back(v);

    //Could have problems later if we allow heavy mutation. refer to lab_ml's insertVertex()
    //adding to adjacency list
    adjacencyList[v] = std::vector<Edge *>();
}

// createAdjMat() must be called after all insertions are complete!
void Graph::insertEdge(Vertex v1, Vertex v2) {
    std::vector<Edge*> & edges = adjacencyList[v1];
    edges.insert(edges.begin(), new Edge(v1, v2));
}

std::vector<Graph::Edge*> Graph::incidentEdges(Vertex v) {
    std::vector<Graph::Edge*> incidentEdges = adjacencyList[v];
    return incidentEdges;
}

bool Graph::areAdjacent(Vertex source, Vertex dest) {
    int source_ind = vert_to_ind[source];
    int dest_ind = vert_to_ind[dest];
    return !adjacencyMatrix(source_ind, source_ind) && adjacencyMatrix(dest_ind, source_ind);
}

void Graph::createAdjMat() {
    size_t dim = adjacencyList.size();
    adjacencyMatrix = ublas::matrix<double>(dim, dim, 0);

    for(auto entry : adjacencyList) {
        Vertex vertex = entry.first;
        auto edges = entry.second;
        int col_ind = vert_to_ind[vertex];
        if(edges.size()) {
            double val = 1.0/edges.size();
            for(auto edge : edges) {
                int row_ind = vert_to_ind[edge->destination];
                adjacencyMatrix(row_ind, col_ind) = val;
            }
        } else {
            double val = 1.0/adjacencyList.size();
            for(size_t row_ind = 0; row_ind < adjacencyList.size(); row_ind++) {
                adjacencyMatrix(row_ind, col_ind) = val;
            }
        }
    }
}

void Graph::printAdjMat() {
    for(auto entry : vert_to_ind) {
        std::cout << entry.first + " is indexed at " << entry.second << std::endl;
    }
    for(size_t i = 0; i < adjacencyMatrix.size1(); i++) {
        for(size_t j = 0; j < adjacencyMatrix.size2(); j++) {
            std::cout << adjacencyMatrix(i, j) << "\t";
        }
        std::cout << std::endl;
    }
}