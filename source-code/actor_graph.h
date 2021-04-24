#pragma once
#include "graph.h"


class actor_graph : public graph {

    /* public functions specific to the derived class */
    public:
        /* empty constructor */
        actor_graph();
        /*
         * constructor:
         * constructs the given graph type according to the class name
         */
        actor_graph(const std::map<std::string, movie> & dataset);

        /*
         * constructor helper function
         * made for use elsewhere as well to use wothout constructor
         */
        void make_graph(const std::map<std::string, movie> & dataset);

        /*
         * virtual edge weight setting function:
         * sets the weight of the edge between 2 vertices
         * the weight is set according to the specifications of the child class
         * @param1: vertex one to which the edge should be connected
         * @param2: vertex two to which the edge should be connected
         */
        void set_edge_weight(edge & e);

        /*
         * should edge exist function
         * determines if an edge should exist between 2 given vertices
         * checks the actor list of both movies corresponding to the two
         * vertices, and returns true if there is even one common actor/actress
         * @param1: first vertex
         * @param2: second vertex
         * @return value: true if edge should exist, false if it shouldn't
         */
        bool should_edge_exist(vertex v1, vertex v2);

};
