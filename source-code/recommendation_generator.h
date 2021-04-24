#pragma once
#include <vector>
#include <string>
#include "graph.h"
#include "genre_graph.h"
#include "actor_graph.h"


/* class to carry out one of our tool's functionality, recommendation generation */
class recommendation_generator {

    /* public functions for the class go here */
    public:
      	/* empty constructor */
      	recommendation_generator();

      	/**
      	 * custom constructor
      	 * @param: map of our dataset
      	 * @return: none
      	 */
      	recommendation_generator(const  std::map<std::string, movie> & dataset);

      	/**
      	 * function to add data to our dataset
      	 * @param: map of new dataset
      	 * @return: none
      	 */
      	void add_data(const  std::map<std::string, movie> & dataset);

      	/**
      	 * function to invoke the print graph function for the genre graph
      	 * @param: none
      	 * @return: none
      	 */
      	void print_graph();

        /*
         * recommendation generator function:
         * the algorithm uses the djikstras algorithm to find the similar movies 
         * to the user's search history
         * no params
         * returns a vector of movie titles that are the best recommendation candidates
         */
        std::vector<std::string> recgen(const std::string movie_1, const std::string movie_2);

    /* all private variables go here */
    private:
      
        /* helper function to get movie vertex of the given title */
        vertex* getVertex_GenreGraph(std::string title);
      
      /* helper function to get movie vertex of the given title */
      vertex* getVertex_ActorGraph(std::string title);
      
        /* graph whose edge weights are based on common genres */
        genre_graph graph_by_genre;

        /* graph whose edge weights are based on common actors */
        actor_graph graph_by_actor;
};


