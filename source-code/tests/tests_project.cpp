#include "cs225/catch/catch.hpp"

#include "graph.h"
#include "project.h"

//helper function to create simple project class with 3 movies
project makeSimpleProject(){
  project p;
  std::vector<movie> movies;
  movies.push_back(movie a{"Movie 1", <"Genre A">, <"Actor X">, 1.0});
  movies.push_back(movie b{"Movie 2", <"Genre B">, <"Actor Y">, 2.0});
  movies.push_back(movie c{"Movie 3", <"Genre B">, <"Actor Y">, 3.0});
  movies.push_back(movie c{"Movie 4", <"Genre B","Genre C">, <"Actor Y", "Actor Z">, 4.0});
  
  std::map<std::string, movie> map1;
  for(movie tmp: movies){
    map1.insert(std::pair<tmp.title, tmp>);
  }
  
  num_datasets = 1;
  p.total_data = map1;
  p.datasets.push_back(map1);
  
  return p;
}



TEST_CASE("search_by_genre test", "[weight = 1][valgrind]"){
  project p = makeSimpleProject();
  
  //TEST 1.0: Search without Flag Works
  vector<string> v1 = p.search_by_genre("Genre A", 0, false);
  REQUIRE(v1.size() == 1);
  REQUIRE(v1[0] = "Movie 1");
  
  vector<string> v2 = p.search_by_genre("Genre B", 0, false);
  REQUIRE(v2.size() == 3);
  
  vector<string> v2 = p.search_by_genre("Genre C", 0, false);
  REQUIRE(v2.size() == 1);
  REQUIRE(v1[0] = "Movie 4");
  
  //TEST 2: Search with Flag Works
  vector<string> v2 = p.search_by_genre("Genre B", 2.5, true);
  REQUIRE(v1.size() == 2);
}

TEST_CASE("search_by_actor test", "[weight = 1][valgrind]"){
  project p = makeSimpleProject();
  
  //TEST 1.0: Search without Flag Works
  vector<string> v1 = p.search_by_actor("Actor X", 0, false);
  REQUIRE(v1.size() == 1);
  REQUIRE(v1[0] = "Movie 1");
  
  vector<string> v2 = p.search_by_actor("Actor Y", 0, false);
  REQUIRE(v2.size() == 3);
  
  vector<string> v2 = p.search_by_actor("Actor Z", 0, false);
  REQUIRE(v2.size() == 1);
  REQUIRE(v1[0] = "Movie 4");
  
  //TEST 2: Search with Flag Works
  vector<string> v2 = p.search_by_actor("Actor Y", 2.5, true);
  REQUIRE(v1.size() == 2);
}