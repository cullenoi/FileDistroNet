#ifndef REQ_H
#define REQ_H

int Req(char * msg);

void RequestFile(int file_id, node * node_list, int * map, int self);

char * ReqAssemble(int client, int file_id, int seg, int dest);

#endif