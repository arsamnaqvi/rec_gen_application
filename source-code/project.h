#pragma once
#include <map>
#include <vector>
#include <string>
#include "structures.h"
#include "recommendation_generator.h"
#include "graph.h"


class project {

    /* all public functions amd variables go here */
    public:
        /* empty constructor */
        project();

        /**
         * custom constructor to make a graph for the rgd 
         * @param: map containing our dataset
         * @return: none
         */
        project(const  std::map<std::string, movie> & dataset);

        /**
         * function to add datasets onto the current data
         * @param: map conatianing the new dataset
         * @return: none 
         */
        void add_data(const  std::map<std::string, movie> & dataset);

        /**
         * function to invoke the rec gen function of the recommendation
         * generator class
         * @param 1: movie 1 name to be used for rec gen
         * @param 2: movie 2 name to be used for rec gen
         * @return: a vector of movie titles
         */
        std::vector<std::string> get_rec(const std::string movie_1, const std::string movie_2);

        /**
         * function to invoke the print graph function for the genre graph
         * @param: none
         * @return: none
         */
        void print_graph();


        /* total number of datasets used */
        int num_datasets;

        /* public variable to hold the data set */
        std::vector<std::map<std::string, movie>> datasets;

        /* public variable to hold all movies from all datasets */
        std::map<std::string, movie> total_data;

        /* public variable to hold user search history */
        std::vector<std::string> user_history;

        /* public variable for holding recommendations */
        std::vector<movie> recs;

        // need to update description here
        /* function to read datasets from a csv file and update the database */
        int read_file_data(const std::string& filename);

        /* search functions for the tool */

        /**
         * search_movie
         * search the total_data map to find a movie struct that matches the 
         * given title
         * copy over the struct contents into the given movie struct reference
         * @param 1: the title of the movie to search for
         * @param 2: the reference to the movie struct into which the info of 
         *          the movie is to be stored
         * @return value: return 1 if the movie was found in the database
         *                return 0 if movie is not in the database
         */
        int search_movie(const std::string arg, movie & out);

        /**
         * search_by_actor
         * search the total_data map to find all movies that have the given actor
         * in them
         * search through the actors vector in each movie struct to find if he/she
         * is part of the movie
         * if he is, add the movie title to the output vector
         * if a rating criteria is required, then check if any movie found, which has
         * the actor in it, has rating equal to or more than the given min rating
         * if it does, then add it to the output vector
         * if it doesn't, don't add it
         * @param 1: name of actor to search with
         * @param 2: minimum rating for a movie to meet the criteria
         * @param 3: flag which tells us if we have a rating criteria to fullfill
         * @return value: output vector of movie names that meet all criterias
         */
        std::vector<std::string> search_by_actor(const std::string arg, double min_rating, bool filter);

        /**
         * search_by_genre
         * search the total_data map to find all movies that have the given genre
         * in them
         * search through the genres vector in each movie struct to find if the 
         * movie belongs to that genre
         * if it does, add the movie title to the output vector
         * if a rating criteria is required, then check if any movie found, which is
         * of that genre, has rating equal to or more than the given min rating
         * if it does, then add it to the output vector
         * if it doesn't, don't add it
         * @param 1: genre to search with
         * @param 2: minimum rating for a movie to meet the criteria
         * @param 3: flag which tells us if we have a rating criteria to fullfill
         * @return value: output vector of movie names that meet all criterias
         */
        std::vector<std::string> search_by_genre(const std::string arg, double min_rating, bool filter);

        /**
         * search_by_rating
         * search the total_data map to find all movies that have rating equal to
         * or greater than the given rating
         * @param 1: minimum rating for a movie to be included
         * @return value: output vector of movie names that meet all criterias
         */
        std::vector<std::string> search_by_rating(double min_rating);

    /* all private variables go here */
    private:

        /* variable for first functionality in our project: rec generator */
        recommendation_generator rdg;

};


