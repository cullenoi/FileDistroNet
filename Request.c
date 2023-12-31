#include "PublicDef.h"
#include "Node/Tracker.h"
#include "Node/Node.h"
#include "Request.h"
#include "receiver_assembler.h"

#define REQUEST 0
#define REQ_ERR 2

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

char * RequestFail(int dest, int file_id, int seg, int self){
    char * msg = (char*)malloc(MX_STR_LEN * sizeof(char));
    // construct sending msg with an ERR value in the flag field
    msg = ReqAssemble(dest, REQ_ERR, file_id, seg, self);
    return msg;
}

//if file node holds (complete file?/file segment?), return 1. else return 0
int RequestFile(struct file_node * root, int file_id,
                node * node_list, int * map, int self, char ** IP_index){
    // assumptions for sim model...
    // each file consists of 10 segments.
    // 
    int seg = SEG_DFLT;
    int * dest, next;
//TODO ADD CHECK WHAT HAVE THEN DO THIS STUFF //Optional 
    printf("Searching for segs\n");
    int flag = 0;
    char * req;
    // Request each of the segments for the file
    for(int i=0; i<SEG_COUNT; i++){
        // Make a max of three attempts in getting a segment.
        if(!check_database(root, file_id, seg)){//check to see if message is in db 1 ==true 0 not
            //check database for seg by seg id
            //return 1 if there, 0 if not
            for(int j=0; j<REDUNDANCY; j++){
                // attempt 1 for request for seg
                dest = rendezvous(file_id, (seg + i), node_list, self);
                // create request msg...
                req = ReqAssemble(self, REQUEST, file_id, (seg + i), dest[j]);
                // if fail: request from dest[1]... dest[2]... return err
                // handles in seperate function...
                // send request message...
                printf("Requesting seg %i from %i\n", (seg + i), dest[j]);
                // get next hop to relay to...
                int next_hop, u = dest[j];
                // track back through the map
                while(u != self){
                    next_hop = u;
                    u = map[u];
                }
                int next = next_hop;
                char* IP = IP_index[next - IPSTART];
                // 0 indicates success...
                if(!ClientCreate(IP,next, req)){
                    flag = 1;
                    break;
                }
            }
            // error case
            if(!flag){
                printf("Error getting %i/%i. Closing request.\n", file_id, seg);
                return flag;
            }
        }
    }

    int complete = 0;
    while(!complete){
        sleep(3);
        // check if we have all segs
        int Complete = isComplete(root,file_id);// 
        if(1 == complete){
            printf("File has been recieved\n"); 
            complete =1;
        }
        // if so 
        //     Build seg
        //         return 1;
        }
    return flag;
}

char * ReqAssemble(int dest, int flag, int file_id, int seg, int self){
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
    sprintf(buff, "%i", self);
    strcat(msg, buff);

    free(buff);
    // return constructed request
    return msg;
}

