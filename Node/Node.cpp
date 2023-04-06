#include <iostream>
#include <string>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "Tracker.h"
#include "Node.h"
#include "Routing.h"

#define REQUEST 0
#define RECEIVE 1

#define IP_LEN 20
#define MX_STR_LEN 100
#define ROW_LEN 80
#define nList_size 5000

// globals 

edge * EdgeList[nList_size] = {NULL};
node * NodeList[nList_size] = {NULL};
// include func for...
//  - parsing recieved msg
//  - build send msg
//  - route msg
//  - vector routing

using namespace std;


int Node::init_node(char * argv[]){
    
    address = atoi(argv[1]);
    printf("Port Set: %i\n", address);
    
    printf("loading node info...\n");
    if(!load_node_info(argv[2])){
        printf("Err loading node info\n");
        return 0;
    }
    printf("Loading nodes.. \n");
    address_book = NULL;
    load_nodes(argv[3]);
    printf("Loading edges...\n");
    edge_list = load_edges(argv[4]);
    printf("Loading list of files...\n");
    memset(file_list, 0,fList_size);
    load_files(argv[5]);
    printf("Calculating static map...\n");

    map = shortest_path(address, edge_list, address_book);
    return 1;
}

int Node::load_node_info(char *fname){
    FILE * csv = fopen(fname, "r");
    if(csv == NULL){
          printf ("@rror\n");
        exit (1);
    }
    // set check var
    file->id = 69;//possible point
    char row[ROW_LEN];
    char * token;
    fgets(row, ROW_LEN, csv);

    while(!feof(csv)){
        // find the corresponding row in the node info datasheet...
        token = strtok(row, ",");
        while(atoi(token) != address){
            fgets(row, ROW_LEN, csv);
            token = strtok(row, ",");
        }
        // read in relative info...
        token = strtok(NULL, ",");
        // node name
        strcpy(name, token);
        printf("Imported Node name: %s\n", name);
        // file num
        token = strtok(NULL, ",");
        file->id = atoi(token);
        printf("Imported File id: %i\n", file->id);
        // file data
        token = strtok(NULL, "\n");
        file->char_count = strlen(token);
        strcpy(file->word, token);
        printf("Imported Dataset: %s\n", file->word);
        break;
    }
    if(!file->id) return 0;
    printf("Loaded data into node\n");
    return 1;
}        

void Node::load_nodes (char *fname){
    // init
    FILE * csv = fopen(fname, "r");
    char row[MX_STR_LEN];
    node * N = (node*)malloc(sizeof(node));
    node * temp, * head = N;
    head = NULL;
    // go though the file and add all nodes to the list.
    while(!feof(csv)){
        fgets(row, MX_STR_LEN, csv);
        node * N = (node*)malloc(sizeof(node));
        if(address_book){
            N->next = address_book;
        }
        address_book = N;
        N->id = atoi(row);
    }
    printf("Loaded nodes\n");
}

edge ** Node::load_edges (char *fname){

    FILE * csv = fopen(fname, "r");

    char row[MX_STR_LEN];
    char * token;

    while(!feof(csv)){
        edge * D1 = (edge*)malloc(sizeof(edge));
        edge * D2 = (edge*)malloc(sizeof(edge));
        fgets(row, MX_STR_LEN, csv);

        D1->e_next = NULL;
        D2->e_next = NULL;

        edge * adj_head;
        // char * buffer = (char*)malloc(MX_STR_LEN * sizeof(char));
        token = strtok(row, ",");
        for(int i=0; token != NULL; i++){
            switch (i) {
            case 0: // V1
                // from D1 to D2..
                adj_head = EdgeList[atoi(token)];
                D1->id = atoi(token);
                if(adj_head)
                    D2->e_next = adj_head;
                EdgeList[atoi(token) ] = D2;
                break;
            case 1: // V2
                // from D2 to D1
                D2->id = atoi(token);
                adj_head = EdgeList[atoi(token) ];
                if(adj_head)
                    D1->e_next = adj_head;
                EdgeList[atoi(token) ] = D1;
                break;
            case 2: //weight
                D1->weight = atoi(token);
                D2->weight = atoi(token);
                break;
            default:
                break;
            }
            token = strtok(NULL, ",");
        }
        //printf("Edge: %i <-> %i\n", D1->id, D2->id);
    }
    printf("Loaded edges\n");
    return &(EdgeList[0]);
} 

void Node::load_files(char *fname){
    FILE * csv = fopen(fname, "r");
    char row[MX_STR_LEN];
    fgets(row, MX_STR_LEN, csv);
    int index = 0;
    while(!feof(csv)){
        file_list[index] = atoi(row);
        // printf("file added: %i\n", atoi(row));
        index++;
        fgets(row, MX_STR_LEN, csv);
    }
    printf("Loaded files\n");
}

int Node::book_update(int node_id, int action){
    // action = 1 -> add, action = 0 -> remove
    if(action){
        // Add Node 
        node * temp = address_book;
        node * new_node = (node*)malloc(sizeof(node));
        // assign attributes to new node
        new_node->id = node_id;
        new_node->next = temp;
        // set new node as head of addressbook
        address_book = new_node;
        printf("Node %i successfully added from address book\n", node_id);
    }
    else {
        // Remove node.
        node * curr = address_book;
        node * temp;
        while(curr){
            if(curr->next->id == node_id){
                curr->next = temp;
                curr->next = curr->next->next;
                delete(temp);
                printf("Node %i successfully removed from address book\n", node_id);
            }
        }
    }
    printf("Nodes updated\n");
    return 1;
} 

void remove_edge(edge * edge_list[], int D1, int D2){
    edge * adj_head = edge_list[D1];
    edge * curr, * prev;
    curr = adj_head;
    //special case for if struct for removal is head...
    if(adj_head->id == D2){
        adj_head = curr->e_next;
        delete(curr);
    } else {
        while(curr){
            if(curr->id == D2){
                prev->e_next = curr->e_next;
                delete(curr);
                printf("%i <-> %i connection removed\n", D1, D2);
                break;
            }
            prev = curr;
            curr = curr->e_next;
        }
    }
}

int Node::edge_update(int new_node, int connection, int action, int qual){
    // if adding action to list.
    edge * adj_head;
    if(action){
        edge * D1 = (edge*)malloc(sizeof(edge));
        edge * D2 = (edge*)malloc(sizeof(edge));
        // connection going from D1 -> D2
        adj_head = edge_list[new_node];
        if(adj_head)
            D2->e_next = adj_head;
        edge_list[new_node] = D2;
        D2->id = connection;
        D2->weight = qual;
        // conneciton going from D2 -> D1
        adj_head = edge_list[connection];
        if(adj_head)
            D1->e_next = adj_head;
        edge_list[connection] = D1;
        D1->id = new_node;
        D1->weight = qual;
        printf("Connection acknowledged: %i <-> %i\n", new_node, connection);
    }
    else{
        // remove instances of new_node & connection from edge_list.
        remove_edge(edge_list, new_node, connection);
        remove_edge(edge_list, connection, new_node);
    }
    return 1;
}

int Node::add_file(char * dataseg, dataset * data_file){ 
    //create new data package...
    dataset * new_data = (dataset*)malloc(sizeof(dataset));
    new_data->word = (char*)malloc(MX_STR_LEN * sizeof(char));
    // add struct to list
    if(data_file){
        // add datagram to the list of data
        new_data->next = data_file;
    }
    data_file = new_data;
    char * parse = (char*)malloc(MX_STR_LEN * sizeof(char));
    // parse msg
    parse = strtok(dataseg, "-");
    printf("Adding file to node %s..", parse);
    // read in file ID
    parse = strtok(NULL, "-");
    parse = strtok(NULL, "-");
    data_file->id = atoi(parse);
    // read in seg ID
    parse = strtok(NULL, "-");
    data_file->seg = atoi(parse);
    // read in data
    parse = strtok(NULL, "\0");
    strcpy(data_file->word, parse);

    printf(" file read in\n\n\n");

    return 1;

}

char * Node::share_file(dataset * file, int seg, int seg_size, int index, int dest){
    // parse the file into x amount of pieces.
    printf("create data packet: %i\n", seg);
    char * point = (char*)malloc(sizeof(char));
    point[0] = '-';

    char * msg = (char*)malloc(MX_STR_LEN * sizeof(char));
    if(msg ==NULL){
        printf("ERROR IN MSG L242\n");
    }
    //memset(msg, 0, strlen(msg));//sets to null
    char * int_char = (char*)malloc(10*sizeof(char));
    if(int_char==NULL){
        printf("ERROR MEM L248\n");
    }
    memset(int_char,0,10*sizeof(char));
    memset(msg,0,sizeof(char)*MX_STR_LEN);

    // add appropriate dest port from array
    sprintf(int_char, "%i", dest);
    strcat(msg, int_char);
    strcat(msg, "-");
    // declare this is a 'send' msg
    sprintf(int_char, "%i", RECEIVE);
    strcat(msg, int_char);
    strcat(msg, "-");
    //printf("%s\n", msg);
    // cout << msg << endl;
    sprintf(int_char, "%i", file->id);
    strcat(msg, int_char);
    strcat(msg, "-");
    //printf("%s\n", msg);
    // cout << msg << endl;
    sprintf(int_char, "%i", seg);
    strcat(msg, int_char);
    strcat(msg, "-");
    //printf("%s\n", msg);
    //cout << msg << endl;

    // // read in data
    //char * buffer = (char*)malloc(seg_size * sizeof(char));
    char buffer;
    char end = '\0';

    //sends 1 for final segment, 0 for every other segment
    if(seg == 109){
        strcat(msg,"1-");
    }
    else{
        strcat(msg,"0-");
    }
    //printf("%s\n", msg);
    // special case final seg.
    if(seg == 109){
        int i = 0;
        for(int j=index; j<file->char_count; j++){
            buffer = file->word[j];
            strcat(msg, &buffer);
        }
        strcat(msg, "\0");
        //printf("%s\n", msg);
        free(int_char);
        free(point);
        return msg;
    }
    else{
        for(int j=index; j<index+seg_size; j++){
            buffer = file->word[j];
            strcat(msg, &buffer);
        }
        strcat(msg, "\0");
        //printf("%s\n", msg);
        free(int_char);
        free(point);
        return msg;
    }    
}

// getters

char * Node::return_file_seg(int dest_port, int file_id, int file_seg){
    dataset * curr = data;
    char * data_seg = (char*)malloc(MX_STR_LEN*sizeof(char));
    char buffer[MX_STR_LEN];
    while(curr){
        if(curr->id == file_id && curr->seg == file_seg){
            // build msg.
            sprintf(buffer, "%i", dest_port);
            strcat(data_seg,buffer);
            strcat(data_seg, "-");
            sprintf(buffer, "%i", RECEIVE);
            strcat(data_seg, buffer);
            strcat(data_seg, "-");
            sprintf(buffer, "%i", curr->id);
            strcat(data_seg, buffer);
            strcat(data_seg, "-");
            sprintf(buffer, "%i", curr->seg);
            strcat(data_seg, buffer);
            strcat(data_seg, "-");
            strcpy(buffer, curr->word);
            strcat(data_seg, buffer);
            return data_seg;
        }
        curr = curr->next;
    }
    printf ("No data seg found!\n");
    return NULL;

}

void Node::printFileList(){
    // lazy method, but only runs once upon user input.
    for(int i=0; i<fList_size; i++){
        if(file_list[i]){
            printf("File: %i\n", file_list[i]);
        }
    }
}

// getters

unsigned Node::get_address(){return address;}
node * Node::get_node_list(){return address_book;}
edge ** Node::get_edge_list(){return edge_list;}
int * Node::get_file_list(){return file_list;}
dataset * Node::get_file(){return file;}
dataset * Node::get_data_list(){return data;}
int * Node::get_map(){return map;}



    



/*
int main(int argc, char *argv[]){
	Node N1;
	if(!N1.init_node(argv)){
		printf("Err in init node (port id: %i)\n", atoi(argv[1]));
	}

    node * list = N1.get_node_list();
    node * curr = list;
    edge ** e_arr = (N1.get_edge_list());
    edge * e_head;

    // while(curr){
    //     printf("Port: %i\n", curr->id);
    //     // printf("Connections:\n");
    //     // e_head = *(e_arr + curr->id);
    //     // while(e_head){
    //     //     printf(" -> %i", e_head->id);
    //     //     e_head = e_head->e_next;
    //     // }
    //     // printf("\n");
    //     curr = curr->next;
    // }
    if(!N1.share_file()){
        printf("err: sharing file\n");
    }
    
    int end;
    printf("\nshortest path proof\n\n");
    cout << "Destination: ";
    cin >> end;
    if((end == N1.get_address()){
        printf("Already at node\n");
    }
    else{
        int next_hop;
        list = N1.get_node_list();
        while(1){
            if(list->id == end){
                next_hop = shortest_path(N1.get_address(), end, 
                            N1.get_edge_list(), N1.get_node_list());
                printf("Next Hop: %i\n", next_hop);
                break;
            }
            list = list->next;
            if(list == NULL){
                printf("Port node found in list of known ports!\n");
                break;
            }
        }
    }
   
    return 0;
}
*/

// nodes know about other nodes throught the 'address book', DHT
// the DHT could be organised by a central authourity but for the purpose and functionality of this network
// a more distributed approach is preferred... 
// A change in the DHT in one node will be pinged to each node in the network, then each node will compare the TIEMSTAMP on its DHT with the one it has just been sent
// and will choose the newest one as its list... 

//book_date: