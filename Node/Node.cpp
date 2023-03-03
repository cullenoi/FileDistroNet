#include <iostream>
#include <vector>
#include <string>
#include <string.h>
#include <stdlib.h>

#include "Tracker.h"
#include "Node.h"
#include "Routing.h"

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
    printf("Loadinf nodes.. \n");
    address_book = load_nodes(argv[3]);
    printf("loading edges...\n");
    edge_list = load_edges(argv[4]);
    return 1;
}

int Node::load_node_info(char *fname){
    FILE * csv = fopen(fname, "r");
    // set check var
    file->id = 0;
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
        strcpy(file->data, token);
        printf("Imported Dataset: %s\n", file->data);
        break;
    }
    if(!file->id) return 0;
    printf("Loaded data into node\n");
    return 1;
}        

node * Node::load_nodes (char *fname){
    // init
    FILE * csv = fopen(fname, "r");
    char row[MX_STR_LEN];
    fgets(row, MX_STR_LEN, csv);
    node * N = (node*)malloc(sizeof(node));
    node * temp, * head = N;
    // go though the file and add all nodes to the list.
    while(!feof(csv)){
        node * N = (node*)malloc(sizeof(node));
        N->id = atoi(row);
        temp = head;
        N->next = head;
        head = N;
        fgets(row, MX_STR_LEN, csv);
    }
    printf("Loaded nodes\n");
    return head;
}

edge ** Node::load_edges (char *fname){

    FILE * csv = fopen(fname, "r");

    char row[MX_STR_LEN];
    char * token;

    fgets(row, MX_STR_LEN, csv);


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
                EdgeList[atoi(token)] = D2;
                break;
            case 1: // V2
                // from D2 to D1
                D2->id = atoi(token);
                adj_head = EdgeList[atoi(token)];
                if(adj_head)
                    D1->e_next = adj_head;
                EdgeList[atoi(token)] = D1;
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
        printf("Edge: %i <-> %i\n", D1->id, D2->id);
    }
    printf("Loaded edges\n");
    return &(EdgeList[0]);
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
            }
        }
    }
    printf("Nodes updated\n");
    return 1;
}

/*
int Node::Bellman_Ford(){

            int i,k,dist[num_nodes],S,flag=1;
            node * curr = address_book;
            node * u, * v;
            edge * edge_curr = head;

            /* set every dist to node to inf.
            complete this step during init of node...
            while(curr){
                if(curr->id == address){
                    curr->dist = 0;
                }
                else{
                    curr->dist = 10000;
                    curr = curr->next;
                }
            }
            
            while(curr){
                while(edge_curr){
                    // u = edge_curr->id1;
                    // v = edge_curr->id2;
                    //find u and v
                    node * node_curr = address_book;
                    // run through node list and find two edge nodes...
                    while(curr){
                        if(curr->id == edge_curr->id1) u = node_curr;
                        if(curr->id == edge_curr->id2) v = node_curr;
                        node_curr = curr->next;
                    }
                    // check if the dist through node u is shorter than the current route...

                    //TODO: implement a vector table for routing
                    if(u->dist + );
                    edge_curr = edge_curr->next;
                }
                curr = curr->next;
            }
            
            for(i=0;i<V-1;i++){
                for(k=0;k<E;k++){
                    u = edge[k][0];
                    v = edge[k][1];
                    if(distance[u]+G[u][v] < distance[v])
                        distance[v] = distance[u] + G[u][v];
                }
            }
            for(k=0;k<E;k++){
                u = edge[k][0];
                v = edge[k][1] ;
                if(distance[u]+G[u][v] < distance[v])
                flag = 0 ;
                }
            return flag;
        }
*/       

// getters

unsigned Node::get_address(){return address;}
node * Node::get_node_list(){return address_book;}
edge ** Node::get_edge_list(){return edge_list;}

// setters

void Node::set_name(char * new_name){ name = new_name;}

int main(int argc, char *argv[]){
	Node N1;
	if(!N1.init_node(argv)){
		printf("Err in init node (port id: %i)\n", atoi(argv[1]));
	}

    node * list = N1.get_node_list();
    node * curr = list;
    edge ** e_arr = (N1.get_edge_list());
    edge * e_head;

    while(curr){
        printf("Port: %i\n", curr->id);
        // printf("Connections:\n");
        // e_head = *(e_arr + curr->id);
        // while(e_head){
        //     printf(" -> %i", e_head->id);
        //     e_head = e_head->e_next;
        // }
        // printf("\n");
        curr = curr->next;
    }
    int start, end;
    printf("shortest path proof\n");
    cout << "Start Node: ";
    cin >> start;
    cout << "End Node: ";
    cin >> end;
    
    shortest_path(start, end, N1.get_edge_list(), N1.get_node_list());


    return 0;
}


// nodes know about other nodes throught the 'address book', DHT
// the DHT could be organised by a central authourity but for the purpose and functionality of this network
// a more distributed approach is preferred... 
// A change in the DHT in one node will be pinged to each node in the network, then each node will compare the TIEMSTAMP on its DHT with the one it has just been sent
// and will choose the newest one as its list... 

//book_date: