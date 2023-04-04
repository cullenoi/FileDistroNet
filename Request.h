#ifndef REQ_H
#define REQ_H

void RequestFile(int file_id, node * node_list, int * map, int self);

char * ReqAssemble(int file_id, int seg, int dest, int * map);

#endif