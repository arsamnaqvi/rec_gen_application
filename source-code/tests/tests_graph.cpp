#include "cs225/catch/catch.hpp"

#include "graph.h"

//helper function to create a simple graph with 3 vertices
void makeSimpleGraph(){
  graph g;
  movie a{"Movie 1", <"Genre A">, <"Actor X">, 1.0};
  movie b{"Movie 2", <"Genre A">, <"Actor Y">, 2.0};
  movie c{"Movie 3", <"Genre A">, <"Actor Z">, 3.0};
  
  g.addVertex(a);
  g.addVertex(b);
  g.addVertex(c);
}

TEST_CASE("addVertex test", "[weight = 1][valgrind]"){
  makeSimpleGraph();
  REQUIRE(vertices.size() == 3);
}

TEST_CASE("addEdge test", "[weight = 1][valgrind]"){
  makeSimpleGraph();
  g.addEdge(vertices[0], vertices[1]);
  g.addEdge(vertices[0], vertices[2]);
  g.addEdge(vertices[1], vertices[2]);
  REQUIRE(edge_list.size() == 3);
}

