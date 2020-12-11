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

int main(int argc, char *argv[]) {

    // Defaults
    if (argc <= 3) {      
        // 2 Arguments Alone Doesn't Make Sense so just do Default Execution  
        if (argc > 1) std::cout << "Invalid Argument Count: Defaulting to Standard Execution\n";

        // Create Wikipedia Article Graph
        std::ifstream file("decoded_links.tsv");
        Graph defaultGraph(file);
        Vertex start = "Carrots"; // Pick Good Start and End Points Soon Plz
        Vertex end = "Peas";        
        
        std::string defaultMessage = "Default Algorithm Results: ";

        // Execute the Algorithms and Get Results
        std::vector<Edge> result_SP = Alg::shortest_path(defaultGraph, start, end);
        std::vector<Vertex> result_BFS = Alg::bfs(defaultGraph, start);
        std::list<std::pair<Vertex, double>> result_PR = Alg::pagerank(defaultGraph, 0.85, 1000, 1e-5);

        // Build Output File Message with Proper Formatting
        defaultMessage += "\n\n\tGraph Breadth-First Search Algorithm: \n\t\tStarting from: " + start + "\n";
        
        // BFS Output String Build Section
        for (unsigned stepCount = 0; stepCount < result_BFS.size(); stepCount++) {                
            if (stepCount != result_BFS.size() - 1) {
                defaultMessage += "\t\t\tStep " + std::to_string(stepCount) + ": " + result_BFS[stepCount] + "\n";
            } else {
                defaultMessage += "\t\t\tEnding Article - Step: " + std::to_string(stepCount) + ": " + result_BFS[stepCount] + "\n";
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

    } 
    // Complex Arguments
    else {             
        // Parsing Arguments and Converting to Lowercase for the Command for Comparison
        std::vector<std::string> arguments = argsToStrings(argc, argv);
        std::transform(arguments[1].begin(), arguments[1].end(), arguments[1].begin(), [](char c){ return std::tolower(c); });

        // Attempts to Read Passed in File Arguments
        std::ifstream file(arguments[2]);
        if (!file.is_open()) {std::cout << "Invalid File or Invalid File Path. Please ensure the file is reachable and has the correct path"; std::cout << "\nEnding Execution\n"; return 0;}
        
        // Builds Graph and Creates File Content String
        Graph inputTsv(file);
        std::string messageFile = "";

        /* 
        *
        *  PAGERANK ALGORITHM
        *
        */
        if (arguments[1] == "pagerank") {
            // Not Enough Arguments for Pagerank -> Break
            if (argc < 4) { std::cout << "Invalid Argument Count for PageRank Algorithm. Please look at \'How to Build\' section on Github to learn more!"; std::cout << "\nEnding Execution\n"; return 0; }
            std::list<std::pair<Vertex, double>> result = Alg::pagerank(inputTsv, 0.85, 1000, 1e-5);
            
            // Grabs Top n-articles from the Pagerank results and adds them to the output file string
            unsigned top_articles = std::stoi(arguments[3]);
            for(std::pair<Vertex, double> entry : result) {
                messageFile += entry.first + ": " + std::to_string(entry.second) + "\n";
                if (!top_articles--) break;
            }

            // Printing to File
            std::ofstream out("Outputs/pagerank_result.txt");
            out << messageFile;
            out.close();

        } 
        
        /* 
        *
        *  BFS ALGORITHM
        *
        */
        else if (arguments[1] == "bfs") {
            // Check to make sure Start Point is in the Graph
            if (inputTsv.adjacencyList.find(arguments[3]) == inputTsv.adjacencyList.end()) {
                std::cout << "Invalid Start Article. Please ensure that this Article is within the Dataset!";
                std::cout << "\nEnding Execution\n"; return 0;
            }
            std::vector<Vertex> traversalPath = Alg::bfs(inputTsv, arguments[3]);

            // Build Output File String
            messageFile += "Starting from: " + arguments[3] + "\n";
            for (unsigned stepCount = 0; stepCount < traversalPath.size(); stepCount++) {                
                if (stepCount != traversalPath.size() - 1) {
                    messageFile += "Step " + std::to_string(stepCount) + ": " + traversalPath[stepCount] + "\n";
                } else {
                    messageFile += "Ending Article - Step: " + std::to_string(stepCount) + ": " + traversalPath[stepCount] + "\n";
                }
            }

            // Printing to File
            std::ofstream out("Outputs/bfs_result.txt");
            out << messageFile;
            out.close();
        
        } 
        
        /* 
        *
        *  DIJKSTRA'S SHORTEST PATH ALGORITHM
        *
        */
        else if (arguments[1] == "dijkstras") {
            // Checks Quantity of Dijkstras algorithm
            if (argc < 5) { 
                std::cout << "Invalid Argument Count for Dijkstra's Algorithm. Please look at \'How to Build\' section on Github to learn more!"; 
                std::cout << "\nEnding Execution\n"; return 0; 
            }

            // Ensure Both Starting and Ending Points are in the Graph
            if (inputTsv.adjacencyList.find(arguments[3]) == inputTsv.adjacencyList.end() 
                || inputTsv.adjacencyList.find(arguments[4]) == inputTsv.adjacencyList.end()) {
                std::cout << "Invalid Start and/or End Articles. Please ensure that these Articles are within the Dataset!"; 
                std::cout << "\nEnding Execution\n"; return 0; 
            }
            std::vector<Edge> result = Alg::shortest_path(inputTsv, arguments[3], arguments[4]);

            // Build Output File String
            messageFile += "Starting from: " + arguments[3] + "\t Going to: " + arguments[4] + "\n";
            int counter = 0;
            for(Edge edge : result) {
                messageFile += "Step " + std::to_string(counter++) + ": " + edge.source + " to " + edge.destination + "\n";
            }

            // Printing to File
            std::ofstream out("Outputs/dijkstras_result.txt");
            out << messageFile;
            out.close();
        } 
        
        else {
            // Arguments Didn't Match Any Algorithm Definition
            std::cout << "Sorry, you have entered an invalid argument sequence! Please look at \'How to Build\' section on Github to learn more!";
        }
    }

    std::cout << "\nSuccess: Please Examine the Contents of the Outputs Folder in your Directory to find your Results!\n";
    return 0;
}

