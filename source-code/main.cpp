#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <algorithm>
#include "project.h"
#include "graph.h"
#include "structures.h"
#include "genre_graph.h"
#include "actor_graph.h"
#include "recommendation_generator.h"




/*
 * search engine type 4
 * DESCRIPTION: searches our database according to the minimum 
 *              rating criteria given
 * @param: reference to the current session's project object
 * OUTPUT: movie titles that match the criteria
 * RETURN: none
 */
void search_engine_type_4(project & session)
{
    // variable to hold user given criteria
    double arg;
    std::cout << "Enter minimum rating:" << std::endl;

    // take in input from user
    std::cin.clear();
    std::cin >> arg;

    // get the vector of movie titles that match the criteria 
    std::vector<std::string> out = session.search_by_rating(arg);
    
    // counter
    unsigned i;

    // print out all titles
    for (i = 0; i < out.size() - 1; ++i)
    {
        std::cout << out[i] << std::endl;
    }

    // if there were no titles in the vector, then notify the user
    if (i == 0) {
        std::cout << "No movies meeting your criteria were found :(" << std::endl;
    }
}

/*
 * search engine type 3
 * DESCRIPTION: searches our data base according to given genre
 *              (adds a ratings filter if asked to)
 * @param: reference to the current session's project object
 * OUTPUT: movie titles that match the criteria
 * RETURN: none
 */
void search_engine_type_3(project & session)
{
    // variables to hold the user given input
    std::string arg;
    std::string arg1;
    double filter;

    // user prompts and readin in user input
    std::cout << "What genre would you like:" << std::endl;
    std::cin.clear();
    std::cin >> arg;
    std::cout << "Would you like to add a ratings filter? Y/N" << std::endl;
    std::cin.clear();
    std::cin >> arg1;
    std::vector<std::string> out;
    // calling the search function depending on the user filter request
    if (arg1 == "Y") 
    {
        // reading in filter input by user
        std::cout << "Input minimum rating: " << std::endl;
        std::cin.clear();
        std::cin >> filter;

        // calling search with filter
        out = session.search_by_genre(arg, filter, true);
    } 
    else 
    {
        // calling search with no filter
        out = session.search_by_genre(arg, 0, false);
    }

    unsigned i; // counter

    // print out all movie titles that match the criteria
    for (i = 0; i < out.size() - 1; ++i)
    {
        std::cout << out[i] << std::endl;
    }

    // if no movies were found then notify user
    if (i == 0) {
        std::cout << "No movies meeting your criteria were found :(" << std::endl;
    }
}

/*
 * search engine type 2
 * DESCRIPTION: searches our data base according to given title
 * @param: reference to the current session's project object
 * OUTPUT: movie title that matches the criteria
 * RETURN: none
 */
void search_engine_type_2(project & session)
{
    // variable to hold user input
    std::string arg;

    // user prompt and reading in user input
    std::cout << "What movie would you like to search for?" << std::endl;
    std::cin.clear();
    std::cin >> arg;

    // variabel to hold movie info
    movie out;

    // if the movie exists in the databse then print out its info
    if (1 == session.search_movie(arg, out))
    {
        std::cout << "Title: " + out.title << std::endl;
        std::cout << "Genres:" << std::endl;
        for (unsigned i = 0; i < out.genres.size() - 1; ++i)
        {
            std::cout << out.genres[i] << std::endl;
        }
        std::cout << "Actors:" << std::endl;
        for (unsigned i = 0; i < out.actors.size() - 1; ++i)
        {
            std::cout << out.actors[i] << std::endl;
        }
        std::cout << "Rating: " + std::to_string(out.rating) << std::endl;
        session.user_history.push_back(arg);
    }

    // otherwise notify user
    else 
    {
        std::cout << "Movie not found :(" << std::endl;
    }

}

/*
 * search engine type 1
 * DESCRIPTION: searches our data base according to given actor
 *              (adds a ratings filter if asked to)
 * @param: reference to the current session's project object
 * OUTPUT: movie title that matches the criteria
 * RETURN: none
 */
void search_engine_type_1(project & session)
{
    // variables to hold user input
    std::string arg;
    std::string arg1;
    double filter;

    // user prompts and readin user input
    std::cout << "Name of actor: ";
    std::cin.clear();
    std::cin >> arg;
    std::cout << "Would you like to add a ratings filter? Y/N" << std::endl;
    std::cin.clear();
    std::cin >> arg1;
    std::vector<std::string> out;
    // if filter is on then search with filter on
    if (arg1 == "Y") 
    {
        // user prompts and readin user input for rating filter
        std::cout << "Input minimum rating: " << std::endl;
        std::cin.clear();
        std::cin >> filter;

        // call search function
        out = session.search_by_actor(arg, filter, true);
    } 

    // otherwise search wothout filter
    else 
    {
        out = session.search_by_actor(arg, 0, false);
    }

    // counter
    unsigned i;

    // print out the movie titles that meet the criteria
    for (i = 0; i < out.size() - 1; ++i)
    {
        std::cout << out[i] << std::endl;
    }

    // otherwise notify user
    if (i == 0) {
        std::cout << "No movies meeting your criteria were found :(" << std::endl;
    }
}


/*
 * intro display
 * DESCRIPTION: writes out information for the user to understand how 
 *              our program works
 * no inputs
 * OUTPUT: info is displayed to user on the console
 * RETURN: none
 */
void intro()
{
    std::cout << "******************************************************************************" << std::endl;
    std::cout << "*           Written for the final project of course CS 225 at UIUC           *" << std::endl;
    std::cout << "*               Members include: ARSAM, HADI, RIDHWAN, MUSTAFA               *" << std::endl;
    std::cout << "*    This tool has multiple uses, which we will describe and list out the    *" << std::endl;
    std::cout << "*    prompts for activateing them as well in the following information:      *" << std::endl;
    std::cout << "*    USE 1:                                                                  *" << std::endl;
    std::cout << "*         DESCRIPTION: search engine, options for specifying search          *" << std::endl;
    std::cout << "*         criterias described after prompt is given                          *" << std::endl;
    std::cout << "*         PROMPT: type 1.                                                    *" << std::endl;
    std::cout << "*    USE 2:                                                                  *" << std::endl;
    std::cout << "*         DESCRIPTION: feed in data in the form of a csv file and have       *" << std::endl;
    std::cout << "*         the database expanded. More information on the format of the       *" << std::endl;
    std::cout << "*         file is given when prompt is typed.                                *" << std::endl;
    std::cout << "*         PROMPT: type 2.                                                    *" << std::endl;
    std::cout << "*    USE 3:                                                                  *" << std::endl;
    std::cout << "*         DESCRIPTION: ask for a recommendation on which movies to           *" << std::endl;
    std::cout << "*         watch and our algorithm will try to find the movies that match     *" << std::endl;
    std::cout << "*         your taste.                                                        *" << std::endl;
    std::cout << "*         To get the best result, have some search history in the            *" << std::endl;
    std::cout << "*         duration of the execution of this program                          *" << std::endl;
    std::cout << "*         PROMPT: type 3.                                                    *" << std::endl;
    std::cout << "*    USE 4:                                                                  *" << std::endl;
    std::cout << "*         DESCRIPTION: ask for a visual output of the movies stored in       *" << std::endl;
    std::cout << "*         the databse of the program and we will output a PNG which          *" << std::endl;
    std::cout << "*         contains a scatter of points representing movies clustered by      *" << std::endl;
    std::cout << "*         genre, each genre being a different color.                         *" << std::endl;
    std::cout << "*         PROMPT: type 4.                                                    *" << std::endl;
    std::cout << "*                                                                            *" << std::endl;
    std::cout << "*    To quit the program, type 5.                                            *" << std::endl;
    std::cout << "*                   TO VIEW THE LIST OF USES AGAIN, TYPE 6                   *" << std::endl;
    std::cout << "******************************************************************************" << std::endl;
}


/*
 * all uses
 * DESCRIPTION: prints out all uses details on the console
 * no inputs
 * OUTPUTS: all uses displayed on the console
 * RETURN: none
 */
void all_uses()
{
    std::cout << "******************************************************************************" << std::endl;
    std::cout << "*    USE 1:                                                                  *" << std::endl;
    std::cout << "*         DESCRIPTION: search for a movie and have its genres, actors and    *" << std::endl;
    std::cout << "*         rating listed out.                                                 *" << std::endl;
    std::cout << "*         PROMPT: type 1.                                                    *" << std::endl;
    std::cout << "*    USE 2:                                                                  *" << std::endl;
    std::cout << "*         DESCRIPTION: feed in data in the form of a csv file and have       *" << std::endl;
    std::cout << "*         the databse expanded. More information on the format of the        *" << std::endl;
    std::cout << "*         file is given when prompt is typed.                                *" << std::endl;
    std::cout << "*         PROMPT: type 2.                                                    *" << std::endl;
    std::cout << "*    USE 3:                                                                  *" << std::endl;
    std::cout << "*         DESCRIPTION: ask for a recommendation on which movies to           *" << std::endl;
    std::cout << "*         watch and our algorithm will try to find the movies that match     *" << std::endl;
    std::cout << "*         your taste.                                                        *" << std::endl;
    std::cout << "*         To get the best result, have some search history in the            *" << std::endl;
    std::cout << "*         duration of the execution of this program                          *" << std::endl;
    std::cout << "*         PROMPT: type 3.                                                    *" << std::endl;
    std::cout << "*    USE 4:                                                                  *" << std::endl;
    std::cout << "*         DESCRIPTION: ask for a visual output of the movies stored in       *" << std::endl;
    std::cout << "*         the databse of the program and we will output a PNG which          *" << std::endl;
    std::cout << "*         contains a scatter of points representing movies clustered by      *" << std::endl;
    std::cout << "*         genre, each genre being a different color.                         *" << std::endl;
    std::cout << "*         PROMPT: type 4.                                                    *" << std::endl;
    std::cout << "*                                                                            *" << std::endl;
    std::cout << "*    To quit the program, type 5.                                            *" << std::endl;
    std::cout << "******************************************************************************" << std::endl;
}


/*
 * the following functions aren't used anywhere, i planned to use them in
 * case 6 of the main program to ask if the user wanted to see some
 * specific use instead of the entire paragraph above becaue its big and
 * takes up a lot of space on the console, but i got lazy and didn't want
 * to write more switch statements so these weren'e used at all
 * but i put in an effort to write these and i didn't want to erase them :)
 */


void use1()
{
    std::cout << "******************************************************************************" << std::endl;
    std::cout << "*    USE 1:                                                                  *" << std::endl;
    std::cout << "*         DESCRIPTION: search engine, options for specifying search          *" << std::endl;
    std::cout << "*         criterias described after prompt is given                          *" << std::endl;
    std::cout << "*         PROMPT: type 1.                                                    *" << std::endl;
    std::cout << "******************************************************************************" << std::endl;
}


void use2()
{
    std::cout << "******************************************************************************" << std::endl;
    std::cout << "*    USE 2:                                                                  *" << std::endl;
    std::cout << "*         DESCRIPTION: feed in data in the form of a csv file and have       *" << std::endl;
    std::cout << "*         the database expanded. More information on the format of the       *" << std::endl;
    std::cout << "*         file is given when prompt is typed.                                *" << std::endl;
    std::cout << "*         PROMPT: type 2.                                                    *" << std::endl;    
    std::cout << "******************************************************************************" << std::endl;
}


void use3()
{
    std::cout << "******************************************************************************" << std::endl;
    std::cout << "*    USE 3:                                                                  *" << std::endl;
    std::cout << "*         DESCRIPTION: ask for a recommendation on which movies to           *" << std::endl;
    std::cout << "*         watch and our algorithm will try to find the movies that match     *" << std::endl;
    std::cout << "*         your taste.                                                        *" << std::endl;
    std::cout << "*         To get the best result, have some search history in the            *" << std::endl;
    std::cout << "*         duration of the execution of this program                          *" << std::endl;
    std::cout << "*         PROMPT: type 3.                                                    *" << std::endl;
    std::cout << "******************************************************************************" << std::endl;
}


void use4()
{
    std::cout << "******************************************************************************" << std::endl;
    std::cout << "*    USE 4:                                                                  *" << std::endl;
    std::cout << "*         DESCRIPTION: ask for a visual output of the movies stored in       *" << std::endl;
    std::cout << "*         the databse of the program and we will output a PNG which          *" << std::endl;
    std::cout << "*         contains a scatter of points representing movies clustered by      *" << std::endl;
    std::cout << "*         genre, each genre being a different color.                         *" << std::endl;
    std::cout << "*         PROMPT: type 4.                                                    *" << std::endl;
    std::cout << "******************************************************************************" << std::endl;
}


void case1(project & session)
{ 
      // variabel to hold user input
      int search_type;
      
      // prompts to display to the user
      std::cout << "What would you like to search for? (type in the option number)" << std::endl;
      std::cout << "1- movies of a specific actor." << std::endl;
      std::cout << "2- movie with a specific title." << std::endl;
      std::cout << "3- movies of a specific genre." << std::endl;
      std::cout << "4- movies above a specified rating." << std::endl;
      
      // reading in the user input
      std::cin.clear();
      std::cin >> search_type;
      
      // switch statements to do different searches based on the user input
      switch (search_type) {
      
      case 1:
        search_engine_type_1(session);
        break;
        
      case 2:
        search_engine_type_2(session);
        break;
        
      case 3:
        search_engine_type_3(session);
        break;
        
      case 4:
        search_engine_type_4(session);
        break;
        
      default:
        std::cout << "Invalid prompt! in search case1" << std::endl;
      break;
      
      };
}

void case2(project & session)
{   
      // prompt to user to display file format
      std::cout << "Format required: title, genres, actors, ratings" << std::endl;
      
      // reading in user input
      std::string arg;
      std::cin.clear();
      std::cin >> arg;
      
      // reading in data from the given file
      int ret = session.read_file_data(arg);
      
      // if the read was successful, then update our graphs
      if (ret == 0)
      {
        session.add_data(session.datasets[session.datasets.size() - 1]);
        //session.rdg.graph_by_actor.make_graph(session.datasets[num_datasets - 1]);
      }
}


void case3(project & session)
{  
      // variables to hold user input
      std::string m1, m2;
      
      // user prompts and readin in user input
      std::cout << "Enter 2 of your movies on which you wish to base the recommendations:" << std::endl;
      std::cout << "movie 1: " << std::endl;
      std::cin.clear();
      std::cin >> m1;
      std::cout << "movie 2: " << std::endl;
      std::cin.clear();
      std::cin >> m2;
      
      // checks to ensure user given input is valid for ojur database
      movie temp;
      std::cout << "Finding movie 1..." << std::endl;
      if (0 == session.search_movie(m1, temp)) 
      {
        std::cout << "movie not found :( try again from the start." << std::endl;
        return;
      }
      else 
      {
        std::cout << "movie found!" << std::endl;
      }
      std::cout << "Finding movie 2..." << std::endl;
      if (0 == session.search_movie(m2, temp)) 
      {
        std::cout << "movie not found :( try again from the start." << std::endl;
        return;
      }
      else 
      {
        std::cout << "movie found!" << std::endl;
      }
      
      // get the recommendations generated into a vector
      std::vector<std::string> rec = session.get_rec(m1, m2);
      
      // print out the recommended movie titles
      for (unsigned i = 0; i < rec.size() - 1; ++i)
      {
        std::cout << rec[i] << std::endl;
      }
}

void case4(project & session)
{ 
      // user prompt 
      std::cout << "Printing graph...." << std::endl;
      
      // print out the genre graph into a png
      session.print_graph();
      
      // notify the user 
      std::cout << "Graph stored as graph_output.png" << std::endl;
}

void case5()
{  
      // user prompts for aesthetics
      std::cout << "Halting program..." << std::endl;
      std::cout << "Halted." << std::endl;
      
      // return from the program
      return;
}

void case6()
{ 
      // print out all uses
      all_uses();
}

/*
 * main function of our project
 * DESCRIPTION: user interface of our project, carries out
 *              any functionality asked for by the user
 * @param1: number of arguments provided via command line
 * @param2: array of strings which holds all the arguments provided
 * OUTPUT: runs functions meant to carry out tasks which fullfill 
 *         our project goals
 * RETURN: dummy int
 */
int main(int argc, const char** argv)
{
  // start a new project every session
  project session;
  
  // parse through all arguments given by the user
  for (int i = 1; i < argc; ++i)
  {
    // read in any file and convert into data in our database
    std::cout << "Integrating file " + std::to_string(i) + "...." << std::endl;
    int ret = session.read_file_data(argv[i]);
    
    // if the read from file failed, skip this arg
    if (ret == -1) 
    {
      continue;
    }
    //std::cout << "num of datasets in session atm" << session.num_datasets << std::endl;
    //std::cout << "num of datasets in session atm" << session.datasets.size() << std::endl;
    // construct the graphs in the recommendation generator
    session = project(session.datasets[session.datasets.size() - 1]);
    //session.rdg.graph_by_actor(session.datasets[session.num_datasets - 1]);
  }
  
  // print out the intro for our program
  intro();
  
  // infinite loop for the entirety of the session so that user can do multiple things
  while(1)
  {
    // variable to hold user input typed
    int prompt;
    
    // reading in the user input
    std:: cout << "Waiting for prompt: ";
    std::cin.clear();
    //std::cin.ignore(10000, '\n');
    std::cin >> prompt;
    
    // switch statements to carry out different tasks according to the input
    switch (prompt) {
    
    // search engine case
    case 1:
      case1(session);
      break;
      
      // case to add datasets to our project during runtime
    case 2:
      case2(session);
      break;
      
      // case to generate recommendations for the user
    case 3:
      case3(session);
      break;
      
      // case to print out the genre graph
    case 4:
      case4(session);
      break;
      
      // case to halt the program
    case 5:
      case5();
      return 0;
      break;
      
      // case to display all uses for the program again
    case 6:
      case6();
      break;
      
    //default:
      //std::cout << "Invalid prompt! Try again." << std::endl;
      //break;
    };
  }
  return 0;
}


