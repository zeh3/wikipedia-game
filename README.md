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

* #### Results
  * Link to Results can be found [Here](https://github-dev.cs.illinois.edu/cs225-fa20/aehasan2-zeh3-noahrr2-mathewf2/blob/master/documentation/RESULTS.md)
</details>

## Installation
<details>
 <summary> <strong>Click to Expand</strong></summary>

To setup this project, clone the repository locally using the command
```bash
git clone https://github-dev.cs.illinois.edu/cs225-fa20/aehasan2-zeh3-noahrr2-mathewf2.git
```
then cd into the newly made directory to be able to utilize the commands in the <a href="https://github-dev.cs.illinois.edu/cs225-fa20/aehasan2-zeh3-noahrr2-mathewf2#how-to-build"><strong> How to Build </strong></a> section.
</details>

## Features
<details>
 <summary> <strong>Click to Expand</strong></summary>
 
Three main features are accessible within the project with a bit of customizability for each:
 1. The usage of Pagerank on any given .tsv file (although Pagerank won't make sense for a variety of datasets)
 	* PageRank implementation based on [CS357 content](https://courses.grainger.illinois.edu/cs357/fa2020/assets/lectures/complete-slides/13-Markov-Chains.pdf)
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

`make` will also create a `/Outputs/` folder where the outputs of our program will be saved as `.txt` files.

To clean the directory of any unwanted executibles and object files use the command:
```bash
make clean
```

There are 4 main commands that can be run after building the main executable from the main command:
```bash
./main
./main dijkstras [file] [source] [dest]
./main pagerank [file] [top]
./main bfs [file] [start]
```
The command `./main` will default to running all 3 algorithms with the randomized arguments to display the full program's functionalities and takes no arguments.

The command `./main dijkstras [file] [source] [dest]` will run the shortest-path algorithm (Dijkstra's algorithm) only given the required arguments in order of `[file]` which is the .tsv dataset, `[source]` which is a string of the starting article (i.e. "United States" is a valid source for the default .tsv since it is an article name), and finally `[dest]` which is a string of the ending article (similar to the starting article in requirements). This will return the article path from the `[source]` article to the `[dest]` article;

The command `./main pagerank [file] [top]` will run the Pagerank algorithm given the required arguments in order of `[file]` which is the .tsv dataset, and `[top]` which is an integer n that implies that the program should return the top n-articles that have the highest probability of being visited from the given file.

The command `./main bfs [file] [start]` will run the Graph Breadth-First Search algorithm given the required argument of `[file]` which is the .tsv dataset and `[start]` which is the starting article of vertex for the BFS traversal. This returns a full traversal of the provided dataset/graph with the path described by the vertices/articles traversed.

The results from program execution will be stored in an `Outputs/` folder as a `.txt`. This folder is generated by `make`. 

* Note: Ensure that the arguments for the commands are supplied in order with correct data types and also that the path to the file that you are passing in is correct and relative to your current working directory. If there are any problems (incorrect input), the program will terminate and not run. ***If an invalid filename has been selected, the program will enter an infinite loop***.

* **Warning**: Running `valgrind --leak-check=full ./main` can take over 20minutes to run.

<details>
 <summary><strong>Examples</strong></summary>
 
---
```
./main pagerank decoded_links.tsv 5
Success: Please Examine the Contents of the Outputs Folder in your Directory to find your Results!
Ending Execution

// Contents of pagerank_result.txt

Pagerank Algorithm for Wikipedia Dataset(http://snap.stanford.edu/data/wikispeedia.html):
	United_States: 0.009565
	France: 0.006445
	Europe: 0.006352
	United_Kingdom: 0.006247
	English_language: 0.004875
	Germany: 0.004836
```

```
./main bfs ./tests/connected_graph.tsv Latin
Invalid Start Article. Please ensure that this Article is within the Dataset!
Ending Execution

./main bfs ./tests/connected_graph.tsv A
Success: Please Examine the Contents of the Outputs Folder in your Directory to find your Results!
Ending Execution

// Contents of bfs_result.txt

Graph Breadth-First Search Algorithm:
Starting from: A
	Step 0: A
	Step 1: D
	Step 2: G
	Step 3: C
	Step 4: B
	Step 5: F
End Step 6: E
```

```
./main dijkstras decoded_links.tsv Esox Blokus

There appears to be no path from Esox to Blokus within the graph.
Please try again, using different Start and End Points!

./main dijkstras decoded_links.tsv Actuary ROT13

Success: Please Examine the Contents of the Outputs Folder in your Directory to find your Results!
Ending Execution

// Contents of dijkstras_result.txt

Dijkstra's Shortest Path Algorithm:
Starting from: Actuary	 Going to: ROT13
	Step 0: Actuary to Mathematics
	Step 1: Mathematics to Cryptography
	Step 2: Cryptography to Caesar_cipher
	Step 3: Caesar_cipher to ROT13

```
</details>

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
The tests that will be run are located within the tests folder of the project, along with many of the sample graphs that are useable as `./main` args.

</details>

## Project Structure
<details>
<summary> <strong>Click to Expand</strong></summary>

* #### Preprocessing and Test Generation
  We used python to preprocess our dataset as well as generate some of our PageRank tests. For more information, please see the included Jupyter notebook, `graph_prep.ipynb` in the root folder.
  
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


