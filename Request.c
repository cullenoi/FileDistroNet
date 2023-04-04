#include "PublicDef.h"
#include "Node/Tracker.h"
#include "Node/Node.h"

#define REQUEST 0

#define SEG_DFLT 100
#define SEG_COUNT 10

void RequestFile(int client, int file_id, node * node_list, int * map, int self){
    // assumptions for sim model...
    // each file consists of 10 segments.
    // 
    int seg = SEG_DFLT;
    int * dest, next;

    printf("Searching for segs\n");

    for(int i=0; i<SEG_COUNT; i++){
        char * req;
        // attempt 1 for request for seg
        dest = rendezvous(file_id, seg, node_list, self);
        next = map[dest[0]];
        req = ReqAssemble(client, file_id, seg, next, map);
        // if fail: request from dest[1]... dest[2]... return err
        // handles in seperate function...
        // send request message...
        ClientCreate(next, req);
    }
}

char * ReqAssemble(int client, int file_id, int seg, int dest, int * map){
    // assemble message
    char sep = '|';
    char * msg = (char*)malloc(MX_STR_LEN * sizeof(char));
    char * buff = (char*)malloc(MX_STR_LEN * sizeof(char));

    // destination port
    sprintf(buff, "%i", dest);
    strcat(msg, buff);
    strcat(msg, &sep);
    // * declare request *
    sprintf(buff, "%i", REQUEST);
    strcat(msg, buff);
    strcat(msg, &sep);
    // file id
    sprintf(buff, "%i", file_id);
    strcat(msg, buff);
    strcat(msg, &sep);
    // segment
    sprintf(buff, "%i", seg);
    strcat(msg, buff);
    strcat(msg, &sep);
    // client port
    sprintf(buff, "%i", client);
    strcat(msg, buff);

    free(buff);
    // return constructed request
    return msg;
}