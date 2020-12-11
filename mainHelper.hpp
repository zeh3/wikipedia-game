#include <iostream>
#include "algorithms.hpp"
#include "graph.h"
#include <cctype>

// Convert Char Array to String for Parsing Purposes
std::vector<std::string> argsToStrings(int argCount, char *args[]) {
    std::vector<std::string> ret;
    ret.resize(argCount);
    for (size_t i = 0; i < (size_t) argCount; i++) {
        for (size_t j = 0; j < std::strlen(args[i]); j++) {
            ret[i] += args[i][j];
        }            
    }
    return ret;
}

int defaultExecution(int argc, char * argv[]) {
    // 2 Arguments Alone Doesn't Make Sense so just do Default Execution  
    if (argc > 1) std::cout << "\nInvalid Argument Count: Defaulting to Standard Execution\n";

    // Create Wikipedia Article Graph
    std::ifstream file("decoded_links.tsv");
    Graph defaultGraph(file);


    int rand1 = rand() % defaultGraph.vertexList.size();
    int rand2 = rand() % defaultGraph.vertexList.size();
    while (rand2 == rand1) rand2 = rand() % defaultGraph.vertexList.size();
    Vertex start = defaultGraph.vertexList[rand1]; // Pick Good Start and End Points Plz
    Vertex end = defaultGraph.vertexList[rand2];       
    
    std::string defaultMessage = "Default Algorithm Results: ";

    // Execute the Algorithms and Get Results
    std::vector<Edge> result_SP = Alg::shortest_path(defaultGraph, start, end);
    std::vector<Vertex> result_BFS = Alg::bfs(defaultGraph, start);
    std::list<std::pair<Vertex, double>> result_PR = Alg::pagerank(defaultGraph, 0.85, 1000, 1e-7);

    // Build Output File Message with Proper Formatting
    defaultMessage += "\n\n\tGraph Breadth-First Search Algorithm: \n\t\tStarting from: " + start + "\n";
    
    // BFS Output String Build Section
    for (unsigned stepCount = 0; stepCount < result_BFS.size(); stepCount++) {                
        if (stepCount != result_BFS.size() - 1) {
            defaultMessage += "\t\t\tStep " + std::to_string(stepCount) + ": " + result_BFS[stepCount] + "\n";
        } else {
            defaultMessage += "\t\t\tEnd Step " + std::to_string(stepCount) + ": " + result_BFS[stepCount] + "\n";
        }
    }
    
    // Dijkstra's Output String Build Section
    defaultMessage += "\n\n\tDijkstra's Shortest Path Algorithm: \n\t\tStarting from: " + start + "\t Going to: " + end + "\n";
    unsigned counter = 0;
    for(Edge edge : result_SP) {
        defaultMessage += "\t\t\tStep " + std::to_string(counter++) + ": " + edge.source + " to " + edge.destination + "\n";
    }
    
    // Pagerank Output String Build Section (Default is Top 20 Articles)
    defaultMessage += "\n\n\tPagerank Algorithm for Wikipedia Dataset(http://snap.stanford.edu/data/wikispeedia.html):\n";
    unsigned top_articles = 20;
    for(std::pair<Vertex, double> entry : result_PR) {
        defaultMessage += "\t\t" + entry.first + ": " + std::to_string(entry.second) + "\n";
        if (!--top_articles) break;
    }

    // Printing to File
    std::ofstream out("Outputs/defaultOutput.txt");
    out << defaultMessage;
    out.close();
    return 1;
}

/* 
*
*  PAGERANK ALGORITHM
*
*/
int pageRankExecution(std::vector<std::string> arguments, int argc, Graph inputTsv) {
    
    std::string messageFile = "\nPagerank Algorithm for Wikipedia Dataset(http://snap.stanford.edu/data/wikispeedia.html):\n";

    // Not Enough Arguments for Pagerank -> Break
    if (argc < 4) { 
        std::cout << "\nInvalid Argument Count for PageRank Algorithm. Please look at \'How to Build\' section on Github to learn more!"; 
        std::cout << "\nEnding Execution\n\n"; return 0; 
    }
    std::list<std::pair<Vertex, double>> result = Alg::pagerank(inputTsv, 0.85, 1000, 1e-7);
    
    // Grabs Top n-articles from the Pagerank results and adds them to the output file string
    unsigned top_articles = std::stoi(arguments[3]);
    for(std::pair<Vertex, double> entry : result) {
        messageFile += "\t" + entry.first + ": " + std::to_string(entry.second) + "\n";
        if (!top_articles--) break;
    }

    // Printing to File
    std::ofstream out("Outputs/pagerank_result.txt");
    out << messageFile;
    out.close();
    return 1;
}

/* 
*
*  BFS ALGORITHM
*
*/
int BFSExecution(std::vector<std::string> arguments, Graph inputTsv) {

    std::string messageFile = "\nGraph Breadth-First Search Algorithm:\n";
;
    // Check to make sure Start Point is in the Graph
    if (inputTsv.adjacencyList.find(arguments[3]) == inputTsv.adjacencyList.end()) {
        std::cout << "\nInvalid Start Article. Please ensure that this Article is within the Dataset!";
        std::cout << "\nEnding Execution\n\n"; return 0;
    }
    std::vector<Vertex> traversalPath = Alg::bfs(inputTsv, arguments[3]);

    // Build Output File String
    messageFile += "Starting from: " + arguments[3] + "\n";
    for (unsigned stepCount = 0; stepCount < traversalPath.size(); stepCount++) {                
        if (stepCount != traversalPath.size() - 1) {
            messageFile += "\tStep " + std::to_string(stepCount) + ": " + traversalPath[stepCount] + "\n";
        } else {
            messageFile += "End Step " + std::to_string(stepCount) + ": " + traversalPath[stepCount] + "\n";
        }
    }

    // Printing to File
    std::ofstream out("Outputs/bfs_result.txt");
    out << messageFile;
    out.close();
    return 1;
}

/* 
*
*  DIJKSTRA'S SHORTEST PATH ALGORITHM
*
*/
int dijkstraExecution(std::vector<std::string> arguments, int argc, Graph inputTsv) {

    std::string messageFile = "\nDijkstra's Shortest Path Algorithm:\n";
    // Checks Quantity of Dijkstras algorithm
    if (argc < 5) { 
        std::cout << "\nInvalid Argument Count for Dijkstra's Algorithm. Please look at \'How to Build\' section on Github to learn more!"; 
        std::cout << "\nEnding Execution\n\n"; return 0; 
    }

    // Ensure Both Starting and Ending Points are in the Graph
    if (inputTsv.adjacencyList.find(arguments[3]) == inputTsv.adjacencyList.end() 
        || inputTsv.adjacencyList.find(arguments[4]) == inputTsv.adjacencyList.end()) {
        std::cout << "\nInvalid Start and/or End Articles. Please ensure that these Articles are within the Dataset!"; 
        std::cout << "\nEnding Execution\n\n"; return 0; 
    }
    std::vector<Edge> result = Alg::shortest_path(inputTsv, arguments[3], arguments[4]);

    if (result.size() == 0) {
        std::cout << "\nThere appears to be no path from " << arguments[3] << " to " << arguments[4] << " within the graph.";
        std::cout << "\nPlease try again, using different Start and End Points!\n\n";
        return 2;
    }

    // Build Output File String
    messageFile += "Starting from: " + arguments[3] + "\t Going to: " + arguments[4] + "\n";
    int counter = 0;
    for(Edge edge : result) {
        messageFile += "\tStep " + std::to_string(counter++) + ": " + edge.source + " to " + edge.destination + "\n";
    }

    // Printing to File
    std::ofstream out("Outputs/dijkstras_result.txt");
    out << messageFile;
    out.close();
    return 1;
}
