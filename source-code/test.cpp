#include "test.h"

int main(){
  
  testSearchByGenre();
  testSearchByActor();
  testAddVertex();
  testAddEdge();
  testAdjacentVertex();
  testConstructor_SetEdgeWeight_genreGraph();
  testConstructor_SetEdgeWeight_actorGraph();
  testAdjacentVertexWeight();
  testBFS_traversal();
  testDijkstras();
  testDijkstrasDisconnected();
  testIO();
  
  testPrintGraph();
  return 0;
}

graph makeSimpleGraph(){
  graph g;
  movie a{"Movie 1", {"Genre A,Genre B,Genre C"}, {"Actor X"}, 1.0};
  movie b{"Movie 2", {"Genre A"}, {"Actor Y"}, 2.0};
  movie c{"Movie 3", {"Genre A"}, {"Actor Z"}, 3.0};
  
  g.addVertex(a);
  g.addVertex(b);
  g.addVertex(c);
  return g;
}

graph makeWeightedGraph(){
  graph g;
  movie a{"Movie 1", {"Genre A"}, {"Actor X"}, 1.0};
  movie b{"Movie 2", {"Genre A"}, {"Actor Y"}, 2.0};
  movie c{"Movie 3", {"Genre A"}, {"Actor Z"}, 3.0};
  movie d{"Movie 4", {"Genre A"}, {"Actor Z"}, 3.0};
  std::vector<movie> movies;
  
  movies.push_back(a);
  movies.push_back(b);
  movies.push_back(c);
  movies.push_back(d);
  
  for(auto m :movies){
    g.addVertex(m);
    vertex& current = g.vertices.back();
    for(auto& v: g.vertices){
      if(v.name!=current.name){
        g.addEdge(v,current);
      }
    }
  }
 auto  it = g.edge_list.begin();
  (it)->weight =8;
  //std::cout<<"The weight of edge "<<0<<" is : "<<it->weight<<std::endl;
  (++it)->weight =2;
  (++it)->weight =3;
  (++it)->weight =11;
  (++it)->weight =4;
  (++it)->weight =10;
  return g;
}
graph makeSimpleGraphWithEdge(){

  graph g = makeSimpleGraph();
  
 // g.addEdge(*(g.vertices.begin()), *(++g.vertices.begin())); //Movie1 and Movie2 
  auto i = ++g.vertices.begin();
  g.addEdge(*(g.vertices.begin()), *(++i));                 //Movie1 and Movie3
  g.addEdge(*(++g.vertices.begin()), *i);                   //Movie2 and Movie3
  
  return g;
}


//helper function to create simple project class with 3 movies
project makeSimpleProject(){
  project p;
  std::vector<movie> movies;
  
  movie a{"Movie 1", {"Genre A"}, {"Actor X"}, 1.0};
  movie b{"Movie 2", {"Genre B"}, {"Actor Y"}, 2.0};
  movie c{"Movie 3", {"Genre B"}, {"Actor Y"}, 3.0};
  movie d{"Movie 4", {"Genre B","Genre C"}, {"Actor Y", "Actor Z"}, 4.0};
  movies.push_back(a);
  movies.push_back(b);
  movies.push_back(c);
  movies.push_back(d);
  
  //movies.push_back(movie a{"Movie 1", {"Genre A"}, {"Actor X"}, 1.0});
  //movies.push_back(movie b{"Movie 2", {"Genre B"}, {"Actor Y"}, 2.0});
  //movies.push_back(movie c{"Movie 3", {"Genre B"}, {"Actor Y"}, 3.0});
  //movies.push_back(movie c{"Movie 4", {"Genre B","Genre C"}, {"Actor Y", "Actor Z"}, 4.0});
  
  std::map<std::string, movie> map1;
  for(movie tmp: movies){
    map1.insert(make_pair(tmp.title, tmp));
  }
  
  p.num_datasets = 1;
  p.total_data = map1;
  p.datasets.push_back(map1);
  return p;
}

void testSearchByGenre(){
  std::cout<<"/* Testing searchByGenre() Function */"<<std::endl;
  std::cout<<"======================================"<<std::endl;
  project p = makeSimpleProject();
  std::vector<std::string> v1 = p.search_by_genre("Genre A", 0, false);
  std::cout<<"There is "<<v1.size()<<" movie containing Genre A \n";
  
  std::vector<std::string> v2 = p.search_by_genre("Genre B", 0, false);
  std::cout<<"There is "<<v2.size()<<" movie containing Genre B \n";
  std::vector<std::string> v3 = p.search_by_genre("Genre C", 0, false);
  std::cout<<"There is "<<v3.size()<<" movie containing Genre C \n";
  std::vector<std::string> v4 = p.search_by_genre("Genre B", 2.5, true);
  std::cout<<"There is "<<v4.size()<<" movie containing Genre B with min rating 2.5 \n"<<std::endl;
}

void testSearchByActor(){
  std::cout<<"/* Testing searchByGenre() Function */"<<std::endl;
  std::cout<<"======================================"<<std::endl;
  project p = makeSimpleProject();
  std::vector<std::string> v1 = p.search_by_actor("Actor X", 0, false);
  std::cout<<"There is "<<v1.size()<<" movie with cast Actor X \n";
  std::vector<std::string> v2 = p.search_by_actor("Actor Y", 0, false);
  std::cout<<"There is "<<v2.size()<<" movie with cast Actor Y \n";
  std::vector<std::string> v3 = p.search_by_actor("Actor Z", 0, false);
  std::cout<<"There is "<<v3.size()<<" movie with cast Actor Z \n";
  std::vector<std::string> v4 = p.search_by_actor("Actor Y", 2.5, true);
  std::cout<<"There is "<<v4.size()<<" movie with cast Actor Y with min rating 2.5 \n"<<std::endl;
}

void testPrintGraph(){
  std::cout<<"/* Testing printGraph() Function */"<<std::endl;
  std::cout<<"==================================="<<std::endl;
  std::cout<<"Check graph_output.png file in your folder. "<<std::endl<<std::endl;
  movie a{"Movie 1", {"Genre B"}, {"Actor X"}, 1.0};
  movie b{"Movie 2", {"Genre B"}, {"Actor Y"}, 2.0};
  movie c{"Movie 3", {"Genre B"}, {"Actor Z"}, 3.0};
  graph g = makeSimpleGraph();
  
  g.addVertex(a);
  g.addVertex(b);
  g.addVertex(c);
  
  g.addEdge(*(g.vertices.begin()), *(++g.vertices.begin()));
  auto i = ++g.vertices.begin();
  g.addEdge(*(g.vertices.begin()), *(++i));
  g.addEdge(*(++g.vertices.begin()), *i);
  g.addEdge(*(g.vertices.begin()), *(++i));
  g.addEdge(*(g.vertices.begin()), *(++i));
  
  g.print_graph();
  //graph_output.png should produce a graph with 6 vertices and 5 edges
}

void testAddVertex(){
  std::cout<<"/* Testing addVertex() Function */"<<std::endl;
  std::cout<<"=================================="<<std::endl;
  graph g = makeSimpleGraph();
  
  std::cout<<"After adding 3 vertex the number of vertices  is : "<<g.vertices.size()<<std::endl;
  int n=0;
  for(auto elem : g.vertices){
    std::cout<<"Vertex "<<n<<" name is "<<elem.name<<std::endl;
    n++;
  }
  
  movie a{"Movie 4", {"Genre B"}, {"Actor A"}, 0.0};
  movie b{"Movie 5", {"Genre B"}, {"Actor B"}, 1.0};
  movie c{"Movie 6", {"Genre B"}, {"Actor C"}, 4.0};
  
  g.addVertex(a);
  g.addVertex(b);
  g.addVertex(c);
  std::cout<<"After adding another 3 vertex the number of vertices  is : "<<g.vertices.size()<<std::endl;
  n=0;
  for(auto elem : g.vertices){
    std::cout<<"Vertex "<<n<<" name is "<<elem.name<<std::endl;
    n++;
  }
  std::cout<<std::endl;
}

void testAddEdge(){
  std::cout<<"/* Testing addEdge() Function */"<<std::endl;
  std::cout<<"================================"<<std::endl;
  graph g = makeSimpleGraph();
  
  g.addEdge(*(g.vertices.begin()), *(++g.vertices.begin())); //Movie1 and Movie2 
  auto i = ++g.vertices.begin();
  g.addEdge(*(g.vertices.begin()), *(++i));                 //Movie1 and Movie3
  g.addEdge(*(++g.vertices.begin()), *i);                   //Movie2 and Movie3
  
  std::cout<<"Number of edges : "<<g.edge_list.size()<<std::endl;
  int n=0;
  for(auto elem : g.edge_list){
    std::cout<<"The first vertex of edge "<<n<<" is "<<elem.vertex_1->name<<std::endl;
    std::cout<<"The second vertex of edge "<<n<<" is "<<elem.vertex_2->name<<std::endl;
    n++;
  }
  std::cout<<std::endl;
}


void testAdjacentVertex(){
  std::cout<<"/* Testing adjacentVertex() Function with 3 vertices graph */"<<std::endl;
  std::cout<<"============================================================="<<std::endl;
  graph g = makeSimpleGraphWithEdge();
  
  std::cout<<"/* Testing AdjacentVertex() Function */"<<std::endl;
  int n = 0;
  int m=0;
  for(auto v : g.vertices){
    std::cout<<"The "<<m<<"th vertex :"<<std::endl;
    n=0;
    for(auto elem : v.incident_edges){
      std::cout<<"The second vertex of incident edge "<<n<<" is "<<g.adjacentVertex( v, elem)->name<<std::endl;
      n++;
    }
    std::cout<<std::endl;
    m++;
  }
  std::cout<<std::endl;
}

void testConstructor_SetEdgeWeight_actorGraph(){
  std::cout<<"/* Testing actorGraph constructor and setEdgeWeight_actorGraph() Function */"<<std::endl;
  std::cout<<"============================================================================"<<std::endl;
  movie a{"Movie 1", {"Horror","Fantasy","Mystery"}, {"Chris","Samuel","Tom","Robert"}, 0.0};
  movie b{"Movie 2", {"Horror","Thriller","Sci-Fi"}, {"Robert","Samuel","Chris"}, 1.0};
  movie c{"Movie 3", {"Fantasy","Mystery","Romance","Sci-Fi"}, {"Tom","Robert","Paul"}, 4.0};
  
  std::map<std::string, movie> data;
  data.insert(std::make_pair("Movie 1", a));
  data.insert(std::make_pair("Movie 2", b));
  data.insert(std::make_pair("Movie 3", c));
  
  actor_graph g(data);
  auto edge = g.edge_list.begin();
  g.set_edge_weight(*edge);
  std::cout<<"[common actor = 3][expected = 7] Weight for this edge: "<<edge->weight<<std::endl;
  edge++;
  g.set_edge_weight(*edge);
  std::cout<<"[common actor = 2][expected = 8] Weight for this edge: "<<edge->weight<<std::endl;
  edge++;
  g.set_edge_weight(*edge);
  std::cout<<"[common actor = 1][expected = 9] Weight for this edge: "<<edge->weight<<std::endl<<std::endl;
  
}

void testConstructor_SetEdgeWeight_genreGraph(){
  std::cout<<"/* Testing genreGraph constructor and setEdgeWeight_genreGraph() Function */"<<std::endl;
  std::cout<<"============================================================================"<<std::endl;
  movie a{"Movie 1", {"Horror","Fantasy","Mystery"}, {"Chris","Samuel","Tom","Robert"}, 0.0};
  movie b{"Movie 2", {"Horror","Thriller","Sci-Fi"}, {"Robert","Samuel","Chris"}, 1.0};
  movie c{"Movie 3", {"Fantasy","Mystery","Romance","Sci-Fi"}, {"Tom","Robert","Paul"}, 4.0};
  
  std::map<std::string, movie> data;
  data.insert(std::make_pair("Movie 1", a));
  data.insert(std::make_pair("Movie 2", b));
  data.insert(std::make_pair("Movie 3", c));
  
  genre_graph g(data);
  auto edge = g.edge_list.begin();
  g.set_edge_weight(*edge);
  std::cout<<"[common genre = 1][expected = 4] Weight for this edge: "<<edge->weight<<std::endl;
  edge++;
  g.set_edge_weight(*edge);
  std::cout<<"[common genre = 2][expected = 3] Weight for this edge: "<<edge->weight<<std::endl;
  edge++;
  g.set_edge_weight(*edge);
  std::cout<<"[common genre = 1][expected = 4] Weight for this edge: "<<edge->weight<<std::endl<<std::endl;
}

void testAdjacentVertexWeight(){
  std::cout<<"/* Testing adjacentVertex() Function with 4 vertices graph */"<<std::endl;
  std::cout<<"============================================================="<<std::endl;
  graph g = makeWeightedGraph();
  
  std::cout<<"/* Testing AdjacentVertex() Function */"<<std::endl;
  int n = 0;
  int m=0;
  for(auto v : g.vertices){
    std::cout<<"The "<<m<<"th vertex :"<<std::endl;
    n=0;
    for(auto elem : v.incident_edges){
      std::cout<<"The weight of edge "<<n<<" is : "<<elem->weight<<std::endl;
      std::cout<<"The second vertex of incident edge "<<n<<" is "<<g.adjacentVertex( v, elem)->name<<std::endl;
      n++;
    }
    std::cout<<std::endl;
    m++;
  }
  std::cout<<std::endl;
}

void testBFS_traversal(){
  std::cout<<"/* Testing BFS_traversal() Function with 3 vertices graph */"<<std::endl;
  std::cout<<"============================================================"<<std::endl;
  graph g = makeSimpleGraphWithEdge();
  std::cout<<std::endl;
  std::cout<<"How the movies are ordered in the linked list."<<std::endl;
  for(auto& elem:g.vertices){
    std::cout<<elem.name<<std::endl;
  }
  std::cout<<std::endl;
  std::cout<<"Since makeSimpleGraphWithEdge() does not have an edge between Movie 1 and Movie 2, \nthe traversal should be Movie 1 -> Movie 3 -> Movie 2"<<std::endl;
  g.BFS_traversal();
  std::cout<<std::endl;
}

void testDijkstras(){
  std::cout<<"/* Testing dijkstrasl() function with 4 vertices graph */"<<std::endl;
  std::cout<<"========================================================="<<std::endl;
  std::cout<<std::endl;
  std::cout<<"The start point is Movie 1 and the destination is Movie 4"<<std::endl<<std::endl;
  std::cout<<"Since the ouput is inverted, the output should be: \nMovie4->Movie2->Movie3->Movie1"<<std::endl;
  std::cout<<std::endl;
  graph g = makeWeightedGraph();
  
  g.dijkstras(g.vertices.front(),g.vertices.back());
  g.print_graph();
  std::cout<<std::endl;
}
void testDijkstrasDisconnected(){
  std::cout<<"/* Testing dijkstrasl() function with 3 disconnect vertices graph */"<<std::endl;
  std::cout<<"===================================================================="<<std::endl;
  std::cout<<std::endl;
  std::cout<<"The start point is Movie 1 and the destination is Movie 4"<<std::endl<<std::endl;
  std::cout<<"Since the vertices is disconnected, the output should be: \n[The two vertices is disconnected.]"<<std::endl;
  std::cout<<std::endl;
  graph g = makeSimpleGraph();
  
  g.dijkstras(g.vertices.front(),g.vertices.back());
  std::cout<<std::endl;
}
void testIO(){
  std::cout<<"/* Testing I/O interface */"<<std::endl;
  std::cout<<"==========================="<<std::endl;
   project temp;
   temp.read_file_data("temp.csv");
   for (auto i = temp.datasets[0].begin(); i != temp.datasets[0].end(); ++i){
   std::cout << i->second.title << std::endl;
   for (unsigned j = 0; j < i->second.genres.size(); j++)
   {
   std::cout << i->second.genres[j] << std::endl;
   }
   //std::cout << "\n" << std::endl;
   for (unsigned j = 0; j < i->second.actors.size(); j++)
   {
   std::cout << i->second.actors[j] << std::endl;
   }
   //std::cout << "\n" << std::endl;
   std::cout << i->second.rating << std::endl;
   std::cout << "\n" << std::endl<<std::endl;
   }
}
