/*|********************************************|*
* |     by: ARSAM, HADI, RIDHWAN, MUSTAFA      |*
* |____________________________________________|*/

/* include all libraries needed in project class */

#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
#include "project.h"
#include "graph.h"
#include "structures.h"
#include "genre_graph.h"
#include "recommendation_generator.h"

/* empty constructor */
project::project():rdg(recommendation_generator()){}

/**
 * custom constructor to make a graph for the rgd 
 * @param: map containing our dataset
 * @return: none
 */
project::project(const  std::map<std::string, movie> & dataset)
{
  rdg = recommendation_generator(dataset);
}

/**
 * function to add datasets onto the current data
 * @param: map conatianing the new dataset
 * @return: none 
 */
void project::add_data(const  std::map<std::string, movie> & dataset)
{
  rdg.add_data(dataset);
}

/**
 * function to invoke the rec gen function of the recommendation
 * generator class
 * @param 1: movie 1 name to be used for rec gen
 * @param 2: movie 2 name to be used for rec gen
 * @return: a vector of movie titles
 */
std::vector<std::string> project::get_rec(const std::string movie_1, const std::string movie_2)
{
  return rdg.recgen(movie_1, movie_2);
}

/**
 * function to invoke the print graph function for the genre graph
 * @param: none
 * @return: none
 */
void project::print_graph()
{
  rdg.print_graph();
}

/**
 * read_file_data:
 * DESCRIPTION: reads data from a given filename and organizes 
 *              it into a map structure in our public variable datasets
 * INPUTS: filename given from which data is to be extracted
 * OUTPUTS: dataset is (further) populated
 * RETURNS: none
 */  
int project::read_file_data(const std::string& filename)
{
    /* push a new empty map into the datasets vector */
    datasets.push_back(std::map<std::string, movie>());

    /* decalred local variables */
    std::ifstream fin(filename); /* filestream to read from the given file */
    if (fin.fail())
    {
        std::cout << "File could not be opened" << std::endl;
        return -1;
    }
    std::string row, genre, actor; /* string to hold line data read from file */
    
    /* condition for reading from the file 
       only read if open */
    if (fin.is_open()) 
    {
        /* get the first line and discard as it is just the column headers */
        std::getline(fin, row);

        /* loop through all rows in the file and get row data */
        while (std::getline(fin, row))
        {

            /* movie to be added to our datasets map */
            movie new_movie;

            /* counter for declared vector of strings */
            // int i = 0;

            /* stream for getting the words from each row */
            std::stringstream line(row);

            /* get the movie title from the row */
            std::getline(line, new_movie.title, ',');

            int flag = 1;

            /* get the entire list of genres in the genre string
             * make a string stream out of the genre string
             * then move each genre into the genres vector in the
             * new movie struct */
            std::getline(line, genre, '"');
            if (genre == "") {
			    std::getline(line, genre, '"');
              	flag = 0;
            }
            std::stringstream G(genre);
			std::string temp_genre;
            while (std::getline(G, temp_genre, ','))
            {
                new_movie.genres.push_back(temp_genre); // add genre in the genres vector
            }

            /* reinitialize the vector counter */
            // i = 0;

            /* get the entire list of actors in the actor string
             * make a string stream out of the actor string
             * then move each actor into the actors vector in the
             * new movie struct */
			if (flag == 0) {
	            std::getline(line, actor, '"');
			}
			std::getline(line, actor, '"');
            std::stringstream A(actor);
			std::string temp_actor;
            while (std::getline(A, temp_actor, ','))
            {
                new_movie.actors.push_back(temp_actor); // add actor in the actors vector
				std::getline(A, temp_actor, ' ');	// getting rid of the extra space before the name
            }

            /* get the rating fromt the row string stream */
            std::string r;
            std::string::size_type sz;
            std::getline(line, r, ',');
			std::getline(line, r);
            new_movie.rating = std::stod(r, &sz);

            /* add the populated movie struct into the datasets and total_data map */
            datasets[datasets.size() - 1][new_movie.title] = new_movie;
            total_data[new_movie.title] = new_movie;
        }
        
    }
	// increment the number of datasets used in this project object
    num_datasets++;
    return 0;
}

/**
 * search movie
 * DESCRIPTION: searches our databse and updates the given movie 
 *				struct with info for the requested movie
 * @param 1: title of the movie requested
 * @param 2: reference to the struct to update
 * OUTPUT: none
 * RETURN: 1 if movie is found, 0 if otherwise
 */
int project::search_movie(const std::string arg, movie & out)
{
	/* search for the movie in the dataset */
	auto lookup = total_data.find(arg);

	/* return failure if movie not found */
	if (lookup == total_data.end()) {return 0;}

	/* else copy over data from the dataset into given movie out */
	out.title = lookup->second.title;	
	for (unsigned j = 0; j < lookup->second.genres.size(); j++)
	{
		out.genres.push_back(lookup->second.genres[j]);
	}	
	for (unsigned j = 0; j < lookup->second.genres.size(); j++)
	{
		out.actors.push_back(lookup->second.actors[j]);
	}
	out.rating = lookup->second.rating;

	/* return success if this point is reached */
	return 1;
}

/**
 * search by genre function
 * @param 1: genre to search with
 * @param 2: minimum rating for a movie to meet the criteria
 * @param 3: flag which tells us if we have a rating criteria to fullfill
 * @return value: output vector of titles that have the given genre
 */
std::vector<std::string> project::search_by_genre(const std::string arg, double min_rating, bool filter){
  std::vector<std::string> ret;
  
  for(auto it = total_data.begin(); it != total_data.end(); it++){
    std::vector<std::string> genres = it->second.genres;
    if(!filter || (filter && it->second.rating >= min_rating)){
      for(std::string genre: genres){
        if(arg == genre){
          ret.push_back(arg);
        }
      }
    }
  }
  return ret;
}

/**
 *search by actor function
 * @param 1: name of actor to search with
 * @param 2: minimum rating for a movie to meet the criteria
 * @param 3: flag which tells us if we have a rating criteria to fullfill
 * @return value: output vector of titles that have the given actor
 */
std::vector<std::string> project::search_by_actor(const std::string arg, double min_rating, bool filter){
  std::vector<std::string> ret;
  
  for(auto it = total_data.begin(); it != total_data.end(); it++){
    std::vector<std::string> actors = it->second.actors;
    
    if(!filter || (filter && it->second.rating >= min_rating)){
      for(std::string actor: actors){
        if(arg == actor){
          ret.push_back(actor);
        }
      }
    }
  }
  return ret;
}

/**
 * search by rating
 * DESCRIPTION: searches for movies that match the criteria
 * 				for the given min rating
 * @param: min rating for the mvoie criteria
 * OUTPUT: none
 * @return: vector of movie titles that meet the criteria
 */
std::vector<std::string> project::search_by_rating(double min_rating)
{
	/* variable to hold movie titles to return */
	std::vector<std::string> ret;

	/* iterate through the entire dataset and add to the returning
	 * vector if movie matches criteria */
	for (auto i = total_data.begin(); i != total_data.end(); ++i)
	{
		if (i->second.rating >= min_rating)
		{
			ret.push_back(i->second.title);
		}
	}

	/* return vector */
	return ret;
}
