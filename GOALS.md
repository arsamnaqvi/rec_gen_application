# Goals For the Final Project (Recommendation Engine)

Main objective:
The main idea of the project is to be able to create recommendations in real time, according to the user input. Using graph data structures and traversal algorithms, we achieve our main purpose.
Another purpose we achieve with the same code structure is a visual representation of the data as described below in the algorithms section. The algorithms are described below.

Dataset(s):
The datasets we use have information about movies of multiple genres and a record of what actors were casted in them, as well as the rating of the movie. Using a graph, we organize the data into vertices and connect them in two ways, by common genres and by common actors/actresses. These two are two different graph data structures a defined in the readme. This links the data and allows us to carry out the intended functionality.

example link:
https://www.kaggle.com/PromptCloudHQ/imdb-data

Algorithms:

BFS Traversal:
We use BFS traversal algo to traverse the entire graph structure of the genre graph in our project, and use a force directed graph drawing algorithm to print the visual representation of the graph structure onto a png file.

Dijkstra's Algorithm:
This algorithm is purely for finding the shortest path between two vertices represented by the two movie titles given as user input in our recommendation generator. The algorithm is applied to both the genre and actor graphs in the recommendation generator class (read the readme for more info on the build structure) and a vector with the best choices for a recommendation is created using the resulting path from both graphs which is then returned to the user (recommendations will vary from 1-5 numerically depending on the result we achieve after executig dijkstra's on both graphs).

Force directed graph algorithm:
This algorithm is used to produce a graphical output to represent the graph that we are using to traverse for the recommendation generator. What it actually does is making sure that every node are apart from one another depending on the edge weight between them. This algorithm updates the position of the node for every iteration by simulating attractive forces, repulsive forces, cooling and temperature. We also added some more function to visualize the graph better. Every edge is drawn on a PNG canvas by using Bresenham's line algorithm and every vertex is drawn on the same canvas as circles that have different colors depending on their genre.