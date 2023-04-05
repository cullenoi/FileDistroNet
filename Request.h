#ifndef REQ_H
#define REQ_H

#include "string.h"

int Req(char * msg);

// Returns 1 on success, 0 on failure to connect to a known PORT containing a seg
int RequestFile(int file_id, node * node_list, int * map, int self);

char * ReqAssemble(int dest, int file_id, int seg, int self);

#endif