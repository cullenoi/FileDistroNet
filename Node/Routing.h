#ifndef ROUTE_H_
#define ROUTE_H_

#include "Tracker.h"
#include "Node.h"

int next_hop(int dest, int self, int * map);

// prints the shortest path between startNode and endNode, if there is any
int * shortest_path(int startNode, edge ** e_list, node * n_list);

// frees any memory that was used
void free_memory(void) ;


#endif
