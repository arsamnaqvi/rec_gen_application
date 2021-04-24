#include "actor_graph.h"

/* empty constructor */
actor_graph::actor_graph(){
  vertices=(std::list<vertex>());
  edge_list=(std::list<edge>());
}

/*
 * constructor for the class
 * DESCRIPTION: creates a graph with edges based on common actors
 * INPUTS: map of keys as strings and value as movie structs
 * OUTPUTS: creates a graph with new vertices and edges based on
 *          the given map
 * RETURN: none
 */
actor_graph::actor_graph(const std::map<std::string, movie> & dataset)
{
  //create all vertices
  for(auto it = dataset.begin(); it != dataset.end(); it++){
    addVertex(it->second);
  }
  
  //checks whether there is an edge between every possible pair of vertices
  //if yes, addEdge
  for(auto i = vertices.begin()++; i != vertices.end(); i++){
    for(auto j = vertices.begin(); j != i; j++){
      if(should_edge_exist(*i, *j)){
        addEdge(*i, *j);
      }
    }
  }
  
  //give each edge weight accordingly
  for(auto & e : edge_list){
    set_edge_weight(e);
  }
}

/**
 * make graph (helper function for the constructor)
 * DESCRIPTION: does the same as constructor, essentially does
 *              everything the constructor is supposed to do but can
 *              be called by other functions in other places not just
 *              at initialization
 * INPUT: map of keys as strings and value as movie structs
 * OUTPUTS: makes addition to the existing graph which may or may not
 *          have anything in them
 * RETURN: none
 */
void actor_graph::make_graph(const std::map<std::string, movie> & dataset)
{
  //create all vertices
  for(auto it = dataset.begin(); it != dataset.end(); it++){
    addVertex(it->second);
  }
  
  //checks whether there is an edge between every possible pair of vertices
  //if yes, addEdge
  for(auto i = vertices.begin()++; i != vertices.end(); i++){
    for(auto j = vertices.begin(); j != i; j++){
      if(should_edge_exist(*i, *j)){
        addEdge(*i, *j);
      }
    }
  }
  
  //give each edge weight accordingly
  for(auto & e : edge_list){
    set_edge_weight(e);
  }
}

/**
 * set_edge_weight function
 * DESCRIPTION: update the weight of the edge between the 2 given vertices
 *              according to the criteria of the class
 * @param 1: first vertex
 * @param 2: second vertex
 * OUTPUTS: edge weight of one edge is updated
 * RETURN: none
 */
void actor_graph::set_edge_weight(edge & e)
{
    /* initialize local variable to hold the number of common actors in 
     * the 2 movies connected by this edge */
    int common = 0;

    /* nested loop to compare every single actor name in both movies */
    for (unsigned i = 0; i < e.vertex_1->info.actors.size(); i++)
    {
        for (unsigned j = 0; j < e.vertex_2->info.actors.size(); j++)
        {
            // increment common if a common actor is found
            if (e.vertex_1->info.actors[i] == e.vertex_2->info.actors[j])
            {
                common++;
            }
        }
    }

    /* the weight of the edge is 10 - number of common actors bewtween
     * the 2 movies connected by this edge */
    e.weight = 10 - common;
}

/*
 * should_edge_exist function
 * DESCRIPTION: checks if the two vertices given meet the criteria for
 *              having an edge in the class
 * @PARAM1: first vertex
 * @PARAM2: second vertex
 * OUTPUTS: none
 * RETURN: true if the two vertices meet the criteria and should have
 *         an edge in between, false if otherwise
 */
bool actor_graph::should_edge_exist(vertex v1, vertex v2)
{
    /* nested loop to compare every single actor name in both movies */
    for (unsigned i = 0; i < v1.info.actors.size(); i++)
    {
        for (unsigned j = 0; j < v2.info.actors.size(); j++)
        {
            /* we only return true if we find a common actor */
            if (v1.info.actors[i] == v2.info.actors[j])
            {
                return true;
            }
        }
    }

    /* if no actors are common, we return false */
    return false;
}

