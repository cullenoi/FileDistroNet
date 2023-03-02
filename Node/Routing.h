#ifndef ROUTE_H_
#define ROUTE_H_

#include "Tracker.h"

node * load_edges (char *fname); //loads the edges from the CSV file of name fname
edge * load_nodes (char *fname);  //loads the vertices from the CSV file of name fname
void shortest_path (int startNode, int endNode); // prints the shortest path between startNode and endNode, if there is any
void free_memory ( void ) ; // frees any memory that was used

#endif
