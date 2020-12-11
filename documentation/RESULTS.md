### Results
---
Overall, we accomplished our goals.
* ##### Our deliverables
    * Our makefiles runs as expected
    * We properly read in our wikipedia set and built a graph based on it
    * We have thoroughly tested our graph and algorithms for bugs and memory leaks
    * Our results are printed to an `/Outputs/<name>.txt`
* #### Algorithms & Traversals
    * Our BFS traversal handles appopriately, and even continues to work in a disconnected graph
    * Our Dijkstra's algorithm returns the shortest path from A to B and is handled; it is often very short
    * Our PageRank algorithm is implemented appropriately; the top 3 ranks from our set are: United_States, France, & Europe
* #### Implementations
    * We have decomposed our project into a Graph class, and an Alg namespace, where our static functions algorithm functions are located.
    * Where possible, we have observed good programming habits; this may be through DRY, git, documentation, and etc.


* #### Example results:
```
// PageRank results; we found these results exceptionally interesting! The numbers represent the probability someone would land on that page from a random starting page
        United_States: 0.956482%
		France: 0.644452%
		Europe: 0.635166%
		United_Kingdom: 0.624720%
		English_language: 0.487520%
		Germany: 0.483599%
```
```
// Dijkstra's result; source and destination are randomized
    Starting from: Coal	 Going to: Special_relativity
			Step 0: Coal to 13th_century
			Step 1: 13th_century to Time
			Step 2: Time to Special_relativity
```
```
// A snippet of BFS; starting point randomized
    Starting from: Coal
			Step 0: Coal
			Step 1: 13th_century
			Step 2: Acid_rain
            . . . 
            Step 4588: Yotsuya_Kaidan
			Step 4589: You're_Still_the_One
			Step 4590: Yungay,_Peru
			End Step 4591: Zara_Yaqob
```
