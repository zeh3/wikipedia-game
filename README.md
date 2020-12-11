# aehasan2-zeh3-noahrr2-mathewf2
# Final Project
## Table of Contents
* [Documentation](https://github-dev.cs.illinois.edu/cs225-fa20/aehasan2-zeh3-noahrr2-mathewf2#documentation)
* [Installation](https://github-dev.cs.illinois.edu/cs225-fa20/aehasan2-zeh3-noahrr2-mathewf2#installation)
* [Features](https://github-dev.cs.illinois.edu/cs225-fa20/aehasan2-zeh3-noahrr2-mathewf2#features)
* [How to Build](https://github-dev.cs.illinois.edu/cs225-fa20/aehasan2-zeh3-noahrr2-mathewf2#how-to-build)
* [Testing](https://github-dev.cs.illinois.edu/cs225-fa20/aehasan2-zeh3-noahrr2-mathewf2#testing)
* [Project Structure](https://github-dev.cs.illinois.edu/cs225-fa20/aehasan2-zeh3-noahrr2-mathewf2#project-structure)
## Documentation
<details>
 <summary> <strong>Click to Expand</strong></summary>
 
* #### Goals
  * Link to Goals Documentation can be found [Here](https://github-dev.cs.illinois.edu/cs225-fa20/aehasan2-zeh3-noahrr2-mathewf2/blob/master/documentation/GOALS.md)

* #### Development
  * Link to Development Documentation can be found [Here](https://github-dev.cs.illinois.edu/cs225-fa20/aehasan2-zeh3-noahrr2-mathewf2/blob/master/documentation/DEVELOPMENT.md)

* #### Team Contracts
  * Link to Team Contracts can be found [Here](https://github-dev.cs.illinois.edu/cs225-fa20/aehasan2-zeh3-noahrr2-mathewf2/tree/master/documentation/Contracts)
 </details>

## Installation
<details>
 <summary> <strong>Click to Expand</strong></summary>

To setup this project, clone the repository locally using the command
```bash
git clone https://github-dev.cs.illinois.edu/cs225-fa20/aehasan2-zeh3-noahrr2-mathewf2.git
```
then cd into the newly made directory to be able to utilize the command in the <a href="https://github-dev.cs.illinois.edu/cs225-fa20/aehasan2-zeh3-noahrr2-mathewf2#how-to-build"><strong> How to Build </strong></a> section.
</details>

## Features
<details>
 <summary> <strong>Click to Expand</strong></summary>
 
Three main features are accessible within the project with a bit of customizability for each:
 1. The usage of Pagerank on any given .tsv file (although Pagerank won't make sense for a variety of datasets)
 2. The usage of BFS on any given .tsv file (i.e. a full traversal with cross sections can be returned for a valid file)
 3. The usage of Dijkstra's Algorithm to find the shortest "article path" between two given articles. This basically returns
    a path (given that it exists) of articles that if visited in order will take you from the starting article to the ending article.
 
 * Note: Defaults have been provided for all 3 of these functions, as well as extra .tsv files located in `/test` if those are desired.

</details>

## How to Build
<details>
 <summary> <strong>Click to Expand</strong></summary>

To build the file, use the command:
```bash
make
```

To clean the directory of any unwanted executibles and object files use the command:
```bash
make clean
```

There are 4 main commands that can be run after building the main executible from the main command:
```bash
./main
./main dijkstras [file] [source] [dest]
./main pagerank [file] [top]
./main bfs [file] [start]
```
The command `./main` will default to running all 3 algorithms with the provided defaults to display the full program's functionalities and takes no arguments.

The command `./main dijkstras [file] [source] [dest]` will run the shortest-path algorithm (Dijkstra's algorithm) only given the required arguments in order of `[file]` which is the .tsv dataset, `[source]` which is a string of the starting article (i.e. "United States" is a valid source for the default .tsv since it is an article name), and finally `[dest]` which is a string of the ending article (similar to the starting article in requirements). This will return the article path from the `[source]` article to the `[dest]` article;

The command `./main pagerank [file] [top]` will run the Pagerank algorithm given the required arguments in order of `[file]` which is the .tsv dataset, and `[top]` which is an integer n that implies that the program should return the top n-articles that have the highest probability of being visited from the given file.

The command `./main bfs [file] [start]` will run the Graph Breadth-First Search algorithm given the required argument of `[file]` which is the .tsv dataset and `[start]` which is the starting article of vertex for the BFS traversal. This returns a full traversal of the provided dataset/graph with the path described by the vertices/articles traversed.

* Note: Ensure that the arguments for the commands are supplied in order with correct data types and also that the path to the file that you are passing in is correct and relative to your current working directory. If there are any problems (incorrect input), the program will terminate and not run.

</details>

## Testing
<details>
 <summary> <strong>Click to Expand</strong></summary>

The code provides a wide variety of tests for the various functions within the program. To run them and see the resulting account of success and failure use the command:
```bash
make test
```
to build them, and then run the test executible using:
```bash
./test
```
The tests that will be run are located within the tests folder of the project, along with many of the sample graphs that are usuable as defaults.

</details>

## Project Structure
<details>
<summary> <strong>Click to Expand</strong></summary>

* #### Algorithms Namespace

  * Dijkstra's Shortest-Path Algorithm
  * Graph Breadth-First Search Algorithm
  * Page-Rank Algorithm

* #### Graph Class
  * Adjacency List Graph Implementation
  * Adjacency-Matrix supplement for PageRank
  * String Type-Definition Vertex Implementation
 
* #### Edge Struct
  * Graph-Edge Object Implementation
</details>


