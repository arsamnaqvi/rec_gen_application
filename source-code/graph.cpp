#include "graph.h"



/*
 * djikstras algorithm:
 * @param1: vertex one, starting point of djikstras algo
 * @param2: vertex two, ending point of djikstras algo
 * returns a vector of all vertices in the shortest path
 */

struct compare{
  bool operator()(const vertex* a,const vertex* b){
    if(a->weight>b->weight){
      return true;
    }
    return false;
  }
};

std::vector<vertex> graph::dijkstras(vertex& one, vertex& two){
  // Create a priority queue to store vertices that 
  // are being preprocessed.
  for(auto& elem : vertices){
    elem.weight=UINT_MAX;
    elem.parent=NULL;
  }
  one.weight=0;
  std::priority_queue< vertex*, std::vector <vertex*> , compare > pq; 
  
  pq.push(&one); 
  
   //Looping till priority queue becomes empty (or all 
  //distances are not finalized) 
  while (!pq.empty()) 
  { 
    vertex* u = pq.top(); 
    pq.pop(); 
    
    // 'i' is used to get all adjacent vertices of a vertex 
    
    for (auto elem : u->incident_edges) 
    { 
      
      vertex* v2= adjacentVertex(*u,elem);
      if(v2==NULL){
        std::cout<<"You are trying to dereference a NULL pointer.\n Abort!!!"<<std::endl;
        return std::vector<vertex>();
      }
      //  If there is shorted path to v through u. 
      if (v2->weight > u->weight + elem->weight) 
      { 
        // Updating distance of v 
        v2->weight = u->weight + elem->weight;
        v2->parent=u;
        pq.push(v2); 
      } 
    }
  } 
  
  // Print shortest distances stored in dist[] 
  std::vector<vertex> output;
  
  output.push_back(two);
  vertex* parent=two.parent;
  if(parent==NULL){
    std::cout<<"The two vertices is disconnected."<<std::endl;
    return std::vector<vertex>();
  }
  while(parent!=&one){
    output.push_back(*parent);
    parent=parent->parent;
  }
  output.push_back(one);
//  for(auto v: output){
//    std::cout<<v.name<<std::endl;
//  }
  return output;
}


 // BFS traversal algo:
 // traverses the entire graqph BFS style
 // updates possible


 std::vector<vertex> graph::BFS_traversal(){
  std::vector<vertex> path;
  for(auto& elem: vertices){
    elem.label=0; //set the label to unvisited
  }
  for(auto& elem:edge_list){
    elem.label=0; //set the label to unvisited
  }

  for(auto& elem: vertices){
    if(elem.label==0){
      BFS_traversal(&elem, path);
    }
  }
   return path;
}


void graph::BFS_traversal(vertex* v, std::vector<vertex>& path){

  // Create a queue for BFS 
  std::queue<vertex*> queue_; 
  
  // Mark the current node as visited and enqueue it 
  v->label = 1; 
  queue_.push(v); 

  while(!queue_.empty()) 
  {
    // Dequeue a vertex from queue and print it 
    vertex* current = queue_.front(); 
    path.push_back(*current);
    queue_.pop(); 
    
    // Get all adjacent vertices of the dequeued 
    // vertex s. If a adjacent has not been visited,  
    // then mark it visited and enqueue it 
    for (auto& elem:current->incident_edges) 
    { 
      vertex* vertex2= adjacentVertex(*current,elem);
      if(vertex2==NULL){
        std::cout<<"You are trying to dereference a NULL pointer.\n Abort!!!"<<std::endl;
        return;
      }
      if(vertex2->label==0) 
      { 
        queue_.push(vertex2);
        vertex2->label=1;
        elem->label=1;
      }
      else if(elem->label==0){
        elem->label=2;
      }
    } 
  } 
}

vertex* graph::adjacentVertex(vertex& v, edge* e){
  if((e->vertex_1)->name==v.name){
    return e->vertex_2;
  }
  else if((e->vertex_2)->name==v.name){
    return e->vertex_1;
  }
  else{
    std::cout<<"The vertex is not in the edge!"<<std::endl;
    return NULL;
  }
}

/**
 * adding vertex function
 * @param: node to add into the graph
 */
void graph::addVertex(movie node){
  // argument for movie struct
  vertex v;
  v.name=node.title;
  v.info=node;
  // pushback using the argument
  vertices.push_back(v);
}

/**
 * adding edge function
 * @param1: vertex one to which the edge should be connected
 * @param2: vertex two to which the edge should be connected
 */
void graph::addEdge(vertex& first, vertex& second){
//void addEdge(vertex first, vertex second){ 
  
  //create edge
  edge e = {0, &first, &second,0}; 
  //struct edge e = {0, first.name, second.name};
  //update edge list
  edge_list.push_back(e);
  //update adjacency list for each vertex
  first.incident_edges.push_back(&edge_list.back());
  second.incident_edges.push_back(&edge_list.back());
  
}

/*
 * print graph function:
 * prints the entire graph onto a PNG
 * algorithm used is a forced directed graph drawing
 * no params
 */

void graph::print_graph(){
  int png_width = 200*vertices.size();
  int png_height = 200*vertices.size();
  size_t iterations = 100*vertices.size();
  
  for(double i = 0; i < 360; i += 15){
    double n = rand()%360;
    cs225::HSLAPixel color(n, 1, 0.75);
    palette.push(color);
  }
  compute(iterations, png_width, png_height);
  cs225::PNG* out = draw_graph(png_width, png_height);
  out->writeToFile("graph_output.png");
}


/**
 * compute function
 * helper function to compute position for each vertex 
 * to be represented on the PNG canvas by using
 * the force-directed graph drawing algorithm
 * 
 * FORCE-DIRECTED GRAPH DRAWING ALGORITHM 
 * (FRUCHTERMAN - REINGOLD LAYOUT ALGORITHM)
 * For every iteration:
 * 1) REPEL - Calculate repulsive forces to make sure each vertices are 
 *            distant from each other
 * 2) ATTRACT - Calculate attractive forces according to weight
 * 3) LIMIT - Limit the maximum displacement to temperature t and
 *            prevent from being displaced outside the frame
 *    
 * 4) COOLING - This maximum displacement decreases for every iteration 
 *              in an inverse linear fashion.
 *    
 * Code modified from: https://rodic.fr/blog/c-weighted-graph-layout-fruchterman-reingold/
 * More explanation here: https://reingold.co/force-directed.pdf
 * 
 * @param1 number of iterations
 * @param2 height of PNG, but is float type
 * @param3 width of PNG, but is a float type
 */

void graph::compute(size_t iterations, float width, float height) {
  float vertexCount = vertices.size();
  
  // Initialize nodes positions on a circle
  float a = 0.f;
  
  //distribute each node on a circle circumference, each node have certain angle (in radian)
  float da = 2.f * M_PI / vertexCount;
  
  //convert circular coordinate to (x,y)-coordinate and save it into position
  for (auto vertex=vertices.begin(); vertex != vertices.end(); vertex++) {
    vertex->position.x = vertexCount * cos(a);
    vertex->position.y = vertexCount * sin(a);
    a += da;
  }
  
  // Initial parameters; other values can be chosen for &quot;area&quot;
  float area = width * height;
  float k2 = area / vertexCount;   //max area one vertex can take
  float k = sqrt(k2);
  
  for (size_t i=0; i<iterations; i++) {
    
    // COOLING - Temperature cools down; starts at 1, ends before 0
    // formula for "cooling" process is subject to change 
    float temperature = 1.f - i / (float)iterations;
    temperature *= temperature;
    
    // REPEL - Calculate repulsive forces for each pair of vertexs
    // Update displacement
    for (auto vertex1 = vertices.begin(); vertex1 != vertices.end(); vertex1++) {
      vertex1->displacement = {0.f, 0.f};
      for (auto vertex2 = vertices.begin(); vertex2 != vertices.end(); vertex2++) {
        float dx = vertex1->position.x - vertex2->position.x;
        float dy = vertex1->position.y - vertex2->position.y;
        if (dx && dy) {
          //continue if both dx & dy = 0 i.e. vertex1 = vertex2
          float d2 = dx*dx + dy*dy;
          float coefficient = k2 / d2;
          vertex1->displacement.x += coefficient * dx;
          vertex1->displacement.y += coefficient * dy;
        }
      }
    }
    
    // Calculate attractive forces for each connecting vertexs depending on weight
    // Updates displacement
    for (auto edge = edge_list.begin(); edge != edge_list.end(); edge++) {
      float dx = edge->vertex_1->position.x - edge->vertex_2->position.x;
      float dy = edge->vertex_1->position.y - edge->vertex_2->position.y;
      
      //remember to convert weight from int to float
      float coefficient = sqrt(dx*dx + dy*dy) / k * ((float) edge->weight);
      edge->vertex_1->displacement.x -= dx * coefficient;
      edge->vertex_1->displacement.y -= dy * coefficient;
      edge->vertex_2->displacement.x += dx * coefficient;
      edge->vertex_2->displacement.y += dy * coefficient;
    }
    
    // LIMIT - makes sure displacement is limited to max value, temperature 
    // Calculate new positions using updated displacement
    float sum = 0.f;
    //int k = 1;
    for (auto vertex=vertices.begin(); vertex!=vertices.end(); vertex++) {
      float d = sqrt(pow(vertex->displacement.x, 2) + pow(vertex->displacement.y, 2));
      if (d > temperature) {
        float coefficient = temperature / d;  //makes sure coefficient <= 1
        vertex->displacement.x *= coefficient;
        vertex->displacement.y *= coefficient;
        sum += temperature;
      } else {
        sum += d;
      }
      
      vertex->position.x += vertex->displacement.x;
      vertex->position.y += vertex->displacement.y;
    
      //k++;
    }
    
  }
  //By the end, edges with low weight will have closer length
  //Edges with high weight will have further length
  
  //std::cout<<"x:"<<

}

/**
 * draw graph function
 * function that draws graph on PNG
 * @param1: width of PNG output
 * @param2: height of PNG output
 */

cs225::PNG* graph::draw_graph(int width, int height){
   cs225::PNG* png = new cs225::PNG(width, height);
   double png_centerX = width/3;
   double png_centerY = height/3;
   //cs225::HSLAPixel black(0,0,0);

   cs225::HSLAPixel white(0,0,1);
   for(int i = 0; i < width; ++i){
     for(int j = 0; j < height; ++j){
       //png->getPixel(i, j) = black;    //color the background black/white first
       //std::cout<<"A: x="<<i<<" y="<<j<<"\n";
       png->getPixel(i, j) = white;
     }
   }
   
   /*
   * draw edge using Bresenham's line algorithm
   * color the edges blue (subject to change)
   * modified from: http://rosettacode.org/wiki/Bitmap/Bresenham%27s_line_algorithm#C.2B.2B
   */
   double scale = 1.5;
   cs225::HSLAPixel blue(200,1,0.5);

   for(auto edge = edge_list.begin(); edge != edge_list.end(); edge++){
     int x1 = scale*(edge->vertex_1->position.x + png_centerX); 
     int y1 = scale*(edge->vertex_1->position.y + png_centerY);
     int x2 = scale*(edge->vertex_2->position.x + png_centerX); 
     int y2 = scale*(edge->vertex_2->position.y + png_centerY);
     
     bool steep = ( fabs(y2 - y1) > fabs(x2 - x1) );
     if(steep){
       std::swap(x1, y1);
       std::swap(x2, y2);
     }
     if(x1 > x2){
       std::swap(x1, x2);
       std::swap(y1, y2);
     }
     
     const float dx = x2 - x1;
     const float dy = fabs(y2 - y1);
     float error = dx / 2.0f;
     const int ystep = (y1 < y2) ? 1 : -1;
     int y = (int)y1;
     
     const int maxX = (int)x2;
     
     for(int x=(int)x1; x<=maxX; x++){
       if(steep){
         //std::cout<<"B: x="<<y<<" y="<<x<<"\n";
         png->getPixel(y,x) = blue;
       } else {
         //std::cout<<"C: x="<<x<<" y="<<y<<"\n";
         png->getPixel(x,y) = blue;
       }
       
       error -= dy;
       if(error < 0){
         y += ystep;
         error += dx;
       }
     }
   }
   
   /*
   * color pixels corresponding to each vertex
   * draw & color circle with vertices' x and y coordinate as center
   */
   //int i = 1;
   //for(auto vertex=vertices.begin(); vertex!=vertices.end(); vertex++){
     for(vertex v : BFS_traversal()){
     ////
     //std::cout<<"vertex no:"<<i<<"\n";
     //i++;
     //////
     int centerX = scale*(v.position.x + png_centerX);
     int centerY = scale*(v.position.y + png_centerY);
     
     //cs225::HSLAPixel red(0,1,0.5);
     
     int radius = 20;
     ////////////////////////////////////// PREVIOUS ////////////////////////
     /*
     for(int i = -1*radius; i <= radius; i++){
     for(int j = -1*radius; j <= radius; j++){
     
     //check if corresponding pixel coords within PNG bound
     if(i + centerX < 0 || i + centerX >= width){
     continue;
     }
     if(j + centerY < 0 || j + centerY >= height){
     continue;
     }
     //color the pixels inside the circle red
     if(sqrt(pow(i,2) + pow(j,2)) <= radius){
     png->getPixel(i + centerX, j + centerY) = red;
     }
     
     }
     }
     */
     ////////////////////////////////////////// NEW /////////////////////////
     int diameter = 2*radius;
     int start = -1*radius;
     int colors = v.info.genres.size();
     int end;
     if(colors==1){
       end=radius;
     }
     else{
     end = (diameter/(colors)) + start;
     }
     
     for(string genre : v.info.genres){
       cs225::HSLAPixel color_for_this_genre = getColor(genre);
       // OR
       //cs225::HSLAPixel color_for_this_genre = color_map.find(genre);
       for(int i = start; i < end; i++){
         for(int j = -1*radius; j < radius; j++){
           if(i + centerX < 0 || i + centerX >= width){
             continue;
           } else if(j + centerY < 0 || j + centerY >= height){
             continue;
           }
           //color the pixels inside the circle red
           if(sqrt(pow(i,2) + pow(j,2)) <= radius){
             png->getPixel(i + centerX, j + centerY) = color_for_this_genre;
           }
         }
       }
       start = end;
       end += end;
        if(end>radius){
          break;
        }
     }
     //////////////////////////////////////////////////////////////////////////
     
   }
   return png;
   }

cs225::HSLAPixel graph::getColor(std::string genre){
  if (color_map.find(genre) != color_map.end()){
    return color_map.find(genre)->second; 
  } 
  else {
    cs225::HSLAPixel new_color = palette.front();
    palette.pop();
    color_map.insert(std::make_pair(genre, new_color));
    return new_color;
  }
  return cs225::HSLAPixel(0,0,0);
}