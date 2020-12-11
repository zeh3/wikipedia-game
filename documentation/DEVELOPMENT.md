# CS 225 Final Project Development Document
## Week 1 (11/22/2020 ~ 11/28/2020)
---
The team produced a skeletal structure for many of the project's major components, as well as came up with design decisions for 
many of the classes that are necessary to implement (the graph and algorithms classes in particular). The team has setup the very
basics for creating test suites and also implemented a make file to ensure that all components are functioning properly
and will continue to function properly on the EWS environment. The team has also researched into many of the algorithms that
are planned to be used including Dijkstra's Shortest Path, Page-Rank, and Graph Breadth-First Search algorithms which are
critical for the project's success. A barebones Github scrumboard has also been created to help with work flow, as well as with
maintaining coordination between team members; the scrumboard will be further fleshed out as more
bugs and issues are discovered. Finally, Now that the foundation has been laid down, the team will be able to start developing more 
particular and detailed functionality for the project classes, and given the current pace, this project is set to be completed on-time.

## Week 2 (11/29/2020 ~ 12/05/2020)
---
This week, we continued to implement our graph and it's functionality. We finished the constructor, and implemented the insertion methods. We also cleaned our dataset with Python & Pandas for a more readable, yet equally functioning set. The constructor was implemented, and is using an ifstream argument to read in a file and build a graph based on a .tsv. Refactoring was done to simplify the process on us, as well as for efficiency/readability. In the end stages of finishing our normalized adjacency matrix; we took a different approach since the columns need to be normalized. Many test cases were written, and simple .tsvs generated for testing purposes. We are starting to look at the algorithm implementations

## Week 3 (12/06/2020 ~ 12/12/2020)
---
For our last week, we focused heavily on the development of the algorithms as well as on the setup within the main that will execute our program. During this period of time, we were able to complete the Pagerank algorithm that finishes in a reasonable amount of time for our realtively large Wikipedia article dataset, a Graph Breadth-First Search Algorithm that returns cross edges and a full graph traversal, and finally Dijkstra's algorithm which allowed us to find the shortest article path starting from one article and then traversing to an end article through following only the links between article pages. The main was then customized to allow for a variety of arguments with premade defaults as well so that the program could be accessed more easily from the user's end. The documentation was also updated to allow for easy understanding of program functionalities and how to use them. All in all, the project seems to have gone very well with respect to the goals that we created, and we were able to accomplish them on time.

