#pragma once

#include "project.h"
#include "graph.h"
#include "genre_graph.h"
#include "actor_graph.h"
#include <vector>
#include <map>
#include <iostream>
#include <algorithm>
#include <iterator>

graph makeSimpleGraph();
graph makeSimpleGraphWithEdge();
graph makeWeightedGraph();
project makeSimpleProject();
void testSearchByGenre();
void testSearchByActor();
void testAddVertex();
void testAddEdge();
void testAdjacentVertex();
void testConstructor_SetEdgeWeight_genreGraph();
void testConstructor_SetEdgeWeight_actorGraph();
void testAdjacentVertexWeight();
void testBFS_traversal();
void testDijkstras();
void testDijkstrasDisconnected();
void testIO();
void testPrintGraph();