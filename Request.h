#ifndef REQ_H
#define REQ_H

#include "string.h"
#include "receiver_assembler.h"


int Req(char * msg);

// Send msg on fail to find data...
char * RequestFail(int dest, int file_id, int seg, int self);

// Returns 1 on success, 0 on failure to connect to a known PORT containing a seg
int RequestFile(struct file_node * root, int file_id,
                node * node_list, int * map, int self, char ** IP_index);

char * ReqAssemble(int dest, int flag, int file_id, int seg, int self);

#endif