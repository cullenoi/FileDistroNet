#include <iostream>
#include <vector>

#include "Tracker.h"
#include "Node.h"
// include func for...
//  - parsing recieved msg
//  - build send msg
//  - route msg
//  - vector routing

using namespace std;

class Node{

    private:
        unsigned address;
        node * address_book;
        int num_nodes;
        edge * head;
        vector<int> next_node;
        //book_date: yy/mm/dd/hh/mm/ss/..
        unsigned book_date;

    public:

        int load_node_info (char *fname){
            FILE * csv = fopen(fname, "r");
            int v_count = 0;
            const int row_len = 100;
            char row[row_len];
            char * token;
            fgets(row, row_len, csv);


            while(!feof(csv)){
                node * N = malloc(sizeof(node));
                N->ipaddr = malloc(stringLength * sizeof(char));
                N->n_next = NULL;
                fgets(row, row_len, csv);
                char * buffer = malloc(stringLength * sizeof(char));
                token = strtok(row, ",");

                for(int i=0; token != NULL; i++){
                    strcpy(buffer, remove_quote(token));
                    switch (i) {
                    case 0: //Node Port Num.
                        N->id = atoi(buffer);  
                        break;
                    case 1: //name
                        strcpy(N->name, buffer);
                        break;
                    case 2: // latitude
                        V->lat = atof(buffer);
                        break;
                    case 3: // longitude
                        V->lng = atof(buffer);
                        break;
                    default:
                        break;
                    }
                    token = strtok(NULL, ",");
                }

                if(V_list[V->node])
                    printf("Err node ID collision\n");
                V_list[V->node] = V;
                v_count++;
            }
            printf("Loaded %i vertices\n", v_count);
            return 1;
        }        
            
    
        int book_update(int node_id, int action){
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
        }
        int Bellman_Ford(){

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
            */
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
};
       
// nodes know about other nodes throught the 'address book', DHT
// the DHT could be organised by a central authourity but for the purpose and functionality of this network
// a more distributed approach is preferred... 
// A change in the DHT in one node will be pinged to each node in the network, then each node will compare the TIEMSTAMP on its DHT with the one it has just been sent
// and will choose the newest one as its list... 

//book_date: