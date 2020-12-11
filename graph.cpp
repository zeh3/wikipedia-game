#include "graph.h"
#include <iostream>
#include <iomanip>

Graph::Graph(std::ifstream& fileStream, bool weighted) {
    Vertex V1, V2;
    if (weighted) {
        std::string weightString;
        while(!fileStream.eof()) {
        std::getline(fileStream, V1, '\t');
        std::getline(fileStream, V2, '\t');
        std::getline(fileStream, weightString, '\n');
        double weight = std::stod(weightString);
        
        if (vert_to_ind.find(V1) == vert_to_ind.end()) { 
            vert_to_ind[V1] = vert_to_ind.size();
            vertexList.push_back(V1);
        }

        adjacencyList[V1].push_back(new Graph::Edge(V1, V2, weight));
        
        if (adjacencyList.find(V2) == adjacencyList.end()) { 
            adjacencyList[V2] = std::vector<Graph::Edge *>();
            vert_to_ind.insert(std::make_pair(V2, vert_to_ind.size()));
            vertexList.push_back(V2);
        }
    }
    } else {
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
    }
    
    createAdjMat();
}

Graph::Graph(const Graph & other) {
    unsigned size = other.adjacencyList.size();
    std::vector<Edge *> temp;

    for (auto entry : other.adjacencyList) {
        temp.clear();
        for (Edge * edge : entry.second) {
            temp.push_back(new Graph::Edge(edge->source, edge->destination));
        }
        this->adjacencyList.insert(std::make_pair(entry.first, temp));
    }

    for (unsigned i = 0; i < size; i++) {
        this->vertexList.push_back(other.vertexList[i]);
    }

    for (auto entry : vert_to_ind) {
        this->vert_to_ind.insert(std::make_pair(entry.first, entry.second));
    }

    this->adjacencyMatrix.resize(size, size);
    for (unsigned i = 0; i < size; i++) {
        for (unsigned j = 0; j < size; j++) {
            this->adjacencyMatrix.at_element(i, j) = other.adjacencyMatrix(i, j);
        }
    }
    
}

Graph::~Graph() {
    _clear();
}

void Graph::_clear() {
    vert_to_ind.clear();
    vertexList.clear();

    for (std::pair<Vertex, std::vector<Graph::Edge *>> child : adjacencyList) {
        for (unsigned i = 0; i < child.second.size(); i++) if (child.second[i]) delete child.second[i];
    }
}


Graph & Graph::operator=(const Graph & other) {
    if (*this == other) return *this;
    this->_clear();
    *this = Graph(other);
    return *this;
}

bool Graph::operator==(const Graph & other) const {
    unsigned size = other.adjacencyList.size();
    if (this->adjacencyList.size() != size) return false;

    for (auto entry : other.adjacencyList) {
        auto thisList = this->adjacencyList.at(entry.first);
        if (thisList.size() != entry.second.size()) return false;
        for (unsigned i = 0; i < entry.second.size(); i++) {
            if (entry.second[i]->source != thisList[i]->source 
                || entry.second[i]->destination != thisList[i]->destination) return false;
        }
    }

    return true;
}

// createAdjMat() must be called after all insertions are complete!
void Graph::insertVertex(Vertex v) {
    vert_to_ind[v] = vert_to_ind.size();
    vertexList.push_back(v);
    adjacencyList[v] = std::vector<Edge *>();
}

// createAdjMat() must be called after all insertions are complete!
void Graph::insertEdge(Vertex v1, Vertex v2) {
    std::vector<Edge*> & edges = adjacencyList[v1];
    edges.insert(edges.begin(), new Edge(v1, v2));
}

std::vector<Graph::Edge*> Graph::incidentEdges(Vertex v) const {
    std::vector<Graph::Edge*> incidentEdges = adjacencyList.at(v);
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