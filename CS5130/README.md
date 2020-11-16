## CS5130 - Advanced Algorithm 
**Most of Reference was taken from :** [CLRS - 3rd Edition](https://www.amazon.com/Introduction-Algorithms-3rd-MIT-Press/dp/0262033844#ace-g7448806443)

- HW1 : Compare & Contrast on different growth functions
- HW2 : Recursive & Dynamic Programming Approach(Top-down & Bottom-up) Comparison.
  - Cutting Rod Problem
- HW3 : Application & Example on Dynamic Programming Approach
  - Matrix Multiplication
  - Longest Common Sub-sequence
- HW4 : Dynamic Programming Approach & Greedy Algorithm
  - Background : Activity Selection Problem & Optimal Substructure
  - Recursive & Dynamic Programming Approach solving for Activity Selection Problem
  - Recursive & Iterative Greedy Algorithm
  - Running Comparison on Iterative Greedy Algorithm with sorted & unsorted inputs

- HW5 : Greedy Algorithm Application : Huffman Coding.
  - What is Prefix Code : Reference [Mathematics in Prefix Code](https://www.youtube.com/watch?v=HST2r5pvJCA&ab_channel=mathematicalmonk) and [Prefix Example](https://gist.github.com/joepie91/26579e2f73ad903144dd5d75e2f03d83)
  - What is Huffman Coding - CLRS(16.3)
  - Fixed Length vs Variable Length Codes.
  - How to construct Huffman Tree [How to Construct Huffman Tree](https://www.youtube.com/watch?v=qE4tfsiTGjE&feature=youtu.be&ab_channel=BadriAdhikari)
    - Canonical Huffman Tree (Elements have equal frequency)
  - Apply Huffman code to problem : reddit_relationshipadvice_legaladvice_2000

- HW6 : Amortized Analysis (One of Aggregate Analysis) & Average Analysis
  - Amorized Analysis versus Average Analysis
    - Stack Operation : POP, PUSH, MULTI-POP
    - K-bit Counter
    
- Extra Reading : Dealing with Disjoint-Sets Data Structures.
  - Disjoint-set Operation (Make-sets, Union(x, y), Find-Set(x))
    - Make-set(x) creates a new set whos only member is x. Since the sets are disjoint, we require that x not already be in the some other set --> Initializing
    - Union(x, y) unites the dynamic sets that contain x and y, says S_x and S_y, into a new set that is the union of these two sets
    - Find-Sets(x) returns a pointer to the represetative of the (unique) set containing x.
  - Linked-list representation of disjoint sets
    - weighted-union heuristics
  - Disjoint-set forest
    - union-by-rank
    - path compression 
    - Disjoint-set forest; Reference [Disjoint-set forest](https://www.youtube.com/watch?v=ID00PMy0-vE&ab_channel=TusharRoy-CodingMadeSimple)

- HW 7: Elementary Graph Algorithms
  - Topological Sorting; Referece : [Tracing the Topological Sorting](https://www.youtube.com/watch?v=ddTC4Zovtbc&ab_channel=TusharRoy-CodingMadeSimple)
    - GCC Library
  - Adjacency List & Adjacency Matrix
  - Breadth First Search
  - Depth First Search

- HW 8: Minimum Spanning Tree
  - Muddy City Problem
  - Kruskal's Algorithm
  - Prim's Algorithm
  - The Cut Property

- HW 9: Single Source Shortest Path
  - Negative Weighted Cycle; Reference : [Negative Weight Cycle](https://www.youtube.com/watch?v=0HXYTi6ZG5Q&feature=youtu.be&ab_channel=BadriAdhikari)
  - Dijkstra Algorithm (weighted directed graph); Reference : [Dijkstra Algorithm](https://www.youtube.com/watch?v=XB4MIexjvY0&ab_channel=AbdulBari)
  - Bellman-Ford Algorithm (weighted directed graph); Reference : [Bellman-Ford Algorithm](https://www.youtube.com/watch?v=7KGohCDej1s&ab_channel=AlgorithmswithAttitude)
  - Directed Acyclic Graph (DAG) Single Source shortest Paths; Reference : [DAG - Shortest Path Algorithm](https://www.youtube.com/watch?v=ePqBaDRHkdk&ab_channel=AlgorithmswithAttitude), [B bellman-Ford and DAG Shortest Path](https://www.youtube.com/watch?v=4Iy0RalrsXo&ab_channel=UHMICSAlgorithms)
