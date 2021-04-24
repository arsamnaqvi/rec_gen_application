# iarizal2-mrnasir2-mustafa6-smnaqvi2
# CS225 Final Project: Arsam,Hadi, Ridhwan, Mustafa
# link for presentation is the first line
https://drive.google.com/file/d/1usmgSzGpiOYliGZTLw-2JYiHJXYKx2q6/view

You will need to compile the code base before using the tool:

1- to compile the code for tests, type "make test" in the command line. This will generate the "test" executable. We do not have catch tests but all our tests are in the test.cpp file which are executed one by one and the results are clear to see if they pass or not in both the actual code in the test.cpp file and the statements printed out to console

2- to compile the actual user program, type "make". This will generate a "project" executable which when run will execute the complete user program we have generated with our code base

When run, the executable will show instructions on how to operate the program and get your desired functionality from it. 
But before any functionality can be extracted, a dataset will have to be added to the program, the instructions for which will be in the introductory user interface for the executable, which will be shown on the terminal.
You can also reference the below instructions for that specific functioanlity:

type in 2 as your prompt,
type in the name of the csv file you wish to add as the dataset (movie.csv is the example file in our repo)
Then continue as the program prompts you to.

Build Documentation:

classes used:

vertex: holds information for the vertex, that is what movie it holds and its info (stored in a movie clss to come later), also holds adjacency list for its edges and coordinates for graph drawing

edge: holds pointers to vertices connected by the object and weight

movie: holds movie info

graph: base class for all graphs used in our implementation; holds common functions for any graph class including add vertex, add edge, print graph, dijkstras and, BFS traversal. Has list of vertices and edges as its priate variables

genre_graph: inherits graph class, egde weights are defined by common genres between two movies represented by two vertices

actor_graph: inherits graph class, egde weights are defined by common actors between two movies represented by two vertices

(both of the above classes have functions that decide if edges should be present between them and their weights)

recommendation_generator: holds a genre and actor graph as its variables, has functions which call dijkstras algorithm on both the graphs to produce recommendations for the user

project: main class which encapsulates all other classes in our code base, the main program interacts with only this class directly. All functionalities are called on this class, after which this invokes proper parts of the code to execute the requested task. Only has a recommendatio_generator object as its private variable.
