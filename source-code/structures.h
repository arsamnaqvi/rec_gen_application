#pragma once
#include <string>
#include <vector>

class vertex;
/* structure to hold each movie's information found in the data set */
class movie {
public:
    std::string title;
    std::vector<std::string> genres;
    std::vector<std::string> actors;
    double rating;
};


/* 
 * struct to hold edge information, that is the vertices connected 
 * together by the edge and its weight
 */
class edge{
public:
    int weight;
    vertex* vertex_1;
    vertex* vertex_2; 
    unsigned label; //0:unvisited, 1:visited, 2:cross
};

class position_struct {
public:
  float x;
  float y;
};


class displacement_struct{
public:
  float x;
  float y;
};


/* struct to hold vertex info */
class vertex{
public:
    std::string name;
    movie info;
    std::vector<edge*> incident_edges; 
    unsigned label; //0:unvisited, 1:visited
    position_struct position;
    displacement_struct displacement;
    unsigned weight;
    vertex* parent;
};

