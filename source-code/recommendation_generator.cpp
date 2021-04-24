#include "recommendation_generator.h"
#include <map>

/* empty constructor */
recommendation_generator::recommendation_generator(): graph_by_genre(genre_graph()),graph_by_actor(actor_graph()){}

/**
 * custom constructor
 * @param: map of our dataset
 * @return: none
 */
recommendation_generator::recommendation_generator(const  std::map<std::string, movie> & dataset)
{
  graph_by_genre = genre_graph(dataset);
  graph_by_actor = actor_graph(dataset);
}

/**
 * function to add data to our dataset
 * @param: map of new dataset
 * @return: none
 */
void recommendation_generator::add_data(const  std::map<std::string, movie> & dataset)
{
  graph_by_genre.make_graph(dataset);
  graph_by_actor.make_graph(dataset);
}

/**
 * function to invoke the print graph function for the genre graph
 * @param: none
 * @return: none
 */
void recommendation_generator::print_graph()
{
  graph_by_genre.print_graph();
}

/*
 * recgen function
 * DESCRIPTION: generates recommendations based on the given movie titles
 * @PARAM1: title of first movie
 * @PARAM2: title of second movie
 * OUTPUTS: none
 * RETURN: a vector of movie titles as reccomendations for the user
 */
std::vector<std::string> recommendation_generator::recgen(const std::string movie_1, const std::string movie_2)
{
  std::vector<std::string> rec;
  std::map<std::string, double> movie_map;
  
  vertex& v1 = *getVertex_GenreGraph(movie_1);
  vertex& v2 = *getVertex_GenreGraph(movie_2);
  vertex& v3 = *getVertex_ActorGraph(movie_1);
  vertex& v4 = *getVertex_ActorGraph(movie_2);
  
  std::vector<vertex> list1 = graph_by_genre.dijkstras((v1), (v2));
  std::vector<vertex> list2 = graph_by_actor.dijkstras((v3), (v4));
  
  if(list1.empty()&&list2.empty()){
    
      edge* elem = v1.incident_edges[0];
      vertex* vertex2= graph_by_genre.adjacentVertex(v1,elem);
      if(vertex2==NULL){
        std::cout<<"You are trying to dereference a NULL pointer.\n Abort!!!"<<std::endl;
        return std::vector<std::string>();
      }
      rec.push_back(vertex2->name);
      
      elem = v2.incident_edges[0];
      vertex2= graph_by_genre.adjacentVertex(v2,elem);
      if(vertex2==NULL){
        std::cout<<"You are trying to dereference a NULL pointer.\n Abort!!!"<<std::endl;
        return std::vector<std::string>();
      }
      rec.push_back(vertex2->name);
      
      elem = v3.incident_edges[0];
      vertex2= graph_by_actor.adjacentVertex(v3,elem);
      if(vertex2==NULL){
        std::cout<<"You are trying to dereference a NULL pointer.\n Abort!!!"<<std::endl;
        return std::vector<std::string>();
      }
      rec.push_back(vertex2->name);
      
      elem = v4.incident_edges[0];
      vertex2= graph_by_actor.adjacentVertex(v4,elem);
      if(vertex2==NULL){
        std::cout<<"You are trying to dereference a NULL pointer.\n Abort!!!"<<std::endl;
        return std::vector<std::string>();
      }
      rec.push_back(vertex2->name);
      return rec;
  }
  //if there are 5 or more common movies, return 5 common movies with highest rating
  for(vertex vertex1: list1){
    if((vertex1.name!=v1.name)&&(vertex1.name!=v2.name)){
    movie_map.insert(std::make_pair(vertex1.name, vertex1.info.rating));
    }
  }
  
  for(vertex vertex2: list2){
    if((vertex2.name!=v1.name)&&(vertex2.name!=v2.name)){
    if(movie_map.find(vertex2.name) != movie_map.end()){
      //found common movie = put in recommendation + erase from map
      rec.push_back(vertex2.name);
      movie_map.erase(vertex2.name);
    } else {
      //if not, insert into map
      movie_map.insert(std::make_pair(vertex2.name, vertex2.info.rating));
    }
    
    if(rec.size() == 5){
      return rec;
    }
    }
  }
  
  //  if there is less than 5 common movies
  //  --> return common movies + highest rating out of the rest
  //  if there is none,
  //  --> return 5 movies with highest rating  
  while(rec.size() != 5 && movie_map.size() > 0){
    
    double max = 0;
    string bestMovie;
    for(auto it = movie_map.begin(); it != movie_map.end(); it++){
      if(it->second > max){
        max = it->second;
        bestMovie = it->first;
      }
    }
    rec.push_back(bestMovie);
    movie_map.erase(bestMovie);
    
  }
  return rec;
}

/**
 * helper function to find movie vertex with the given title
 * @PARAM: name of movie
 * @RETURNS: vertex of the movie whose name matches input
 */
vertex* recommendation_generator::getVertex_GenreGraph(std::string title){
  for(auto & v: graph_by_genre.vertices){
    if(v.info.title == title){
      return &v;
    }
  }
  return NULL;
}

/**
 * helper function to find movie vertex with the given title
 * @PARAM: name of movie
 * @RETURNS: vertex of the movie whose name matches input
 */
vertex* recommendation_generator::getVertex_ActorGraph(std::string title){
  for(auto & v: graph_by_actor.vertices){
    if(v.info.title == title){
      return &v;
    }
  }
  return NULL;
}