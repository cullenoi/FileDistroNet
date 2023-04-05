#include "PublicDef.h"
#include "Node/Tracker.h"
#include "Node/Node.h"
#include "Request.h"

#define REQUEST 0

#define SEG_DFLT 100
#define SEG_COUNT 10

int Req(char * msg){
    char * copy = (char*)malloc(MX_STR_LEN * sizeof(char));
    strcpy(copy, msg);
    char * parse = (char*)malloc(MX_STR_LEN * sizeof(char));
    parse = strtok(copy, "-");
    parse = strtok(NULL, "-");
    printf("%i\n req\n", atoi(parse));
    //printf("PASER SAYS %s.\n", parse);
    return atoi(parse);
}

void RequestFile(int file_id, node * node_list, int * map, int self){
    // assumptions for sim model...
    // each file consists of 10 segments.
    // 
    int seg = SEG_DFLT;
    int * dest, next;

    printf("Searching for segs\n");

    for(int i=0; i<SEG_COUNT; i++){
        char * req;
        // attempt 1 for request for seg
        dest = rendezvous(file_id, (seg + i), node_list, self);
        // create request msg...
        req = ReqAssemble(self, file_id, (seg + i),dest[0]);
        // if fail: request from dest[1]... dest[2]... return err
        // handles in seperate function...
        // send request message...
        printf("Requesting seg %i from %i\n", (seg + i), dest[0]);
        // get next hop to relay to...
        int next_hop, u = dest[0];
        // track back through the map
        while(u != self){
            next_hop = u;
            u = map[u];
        }
        int next = next_hop;
        ClientCreate(next, req);
    }
}

char * ReqAssemble(int client, int file_id, int seg, int dest){
    // assemble message
    //char sep = '|';
    char * msg = (char*)malloc(MX_STR_LEN * sizeof(char));
    char * buff = (char*)malloc(MX_STR_LEN * sizeof(char));
    memset(buff,0,MX_STR_LEN * sizeof(char));
    memset(msg,0,MX_STR_LEN * sizeof(char));

    // destination port
    sprintf(buff, "%i", dest);
    strcat(msg, buff);
    strcat(msg, "-");
    // * declare request *
    sprintf(buff, "%i", REQUEST);
    strcat(msg, buff);
    strcat(msg, "-");
    // file id
    sprintf(buff, "%i", file_id);
    strcat(msg, buff);
    strcat(msg, "-");
    // segment
    sprintf(buff, "%i", seg);
    strcat(msg, buff);
    strcat(msg, "-");
    // client port
    sprintf(buff, "%i", client);
    strcat(msg, buff);

    free(buff);
    // return constructed request
    return msg;
}