#pragma once
#include <map>
#include <vector>
#include <list>
#include <queue>
#include <climits>
#include "structures.h"
#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
#include <math.h>
#include <time.h>
#include <stdlib.h>

/* 
 * our main graph class that will hold information organized in the shape 
 * of the graph, the pillar of our project on which the entire 
 * functionality is based
 */
class graph {

    /* all private functions declared here */
    public:

        /*
         * dijkstras algorithm:
         * @param1: vertex one, starting point of djikstras algo
         * @param2: vertex two, ending point of djikstras algo
         * returns a vector of all vertices in the shortest path
         */

        std::vector<vertex> dijkstras(vertex& one, vertex& two);


        /*
         * BFS traversal algo:
         * traverses the entire graqph BFS style
         * updates possible
         */
        std::vector<vertex> BFS_traversal();
        
        
        /* helper function for BFS */
        void BFS_traversal(vertex* v, std::vector<vertex>& path);
  
        
        /* helper function for BFS */
        vertex* adjacentVertex(vertex& v, edge* e);
        
        cs225::HSLAPixel getColor(std::string genre);

    /* all public functions declared here */

        /*
         * virtual edge weight setting function:
         * sets the weight of the edge between 2 vertices
         * the weight is set according to the specifications of the child class
         * @param1: vertex one to which the edge should be connected
         * @param2: vertex two to which the edge should be connected
         
        virtual void set_edge_weight(vertex v1, vertex v2);
        */
        /**
         * adding vertex function
         * @param: node to add into the graph
         */
        void addVertex(movie node);
        
        /**
         * adding edge function
         * @param1: vertex one to which the edge should be connected
         * @param2: vertex two to which the edge should be connected
         */
        void addEdge(vertex& one, vertex& two);
        
        /*
         * print graph function:
         * prints the entire graph onto a PNG
         * algorithm used is a forced directed graph drawing
         * no params
         * returns a pointer to the PNG produced
         */
        void print_graph();

    /* all private variables declared here */
      
      /* helper function to assign position for each vertex */
      void compute(size_t iterations, float width, float height);
      
      /* helper function to draw graph on PNG */
      cs225::PNG* draw_graph(int width, int height);
      
        /* list of vertices in the graph */
        std::list<vertex> vertices;

        /* list of edges in the graph */
        std::list<edge> edge_list;
        
        std::map<std::string, cs225::HSLAPixel> color_map;
        
        std::queue<cs225::HSLAPixel> palette;


};


