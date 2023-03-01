#include <iostream>
#include <vector>

#include "Tracker.h"


using namespace std;

class Node{

    private:
        unsigned address;
        node_list * address_book;
        int num_nodes;
        edge_list * head; 
        //book_date: yy/mm/dd/hh/mm/ss/..
        unsigned book_date;

    public:

        int init_node(node_list * book, unsigned address){
            
        }
        int book_update(int node_id, int action){
            // action = 1 -> add, action = 0 -> remove
            if(action){
                // Add Node 
                node_list * temp = address_book;
                node_list * new_node = (node_list*)malloc(sizeof(node_list));
                // assign attributes to new node
                new_node->id = node_id;
                new_node->next = temp;
                // set new node as head of addressbook
                address_book = new_node;
            }
            else {
                // Remove node.
                node_list * curr = address_book;
                node_list * temp;
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
            int i,u,v,k,distance[100],S,flag=1;
            for(i=0;i<V;i++)
                distance[i] = 10000 ;
                //get source
                distance[S-1]=0;
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
                if(flag)
                for(i=0;i<V;i++)
                cout<<"\nDistance from source "<<S<<" to vertex "<<i+1<<" is "<<distance[i];
            return flag;
        }
};
        
// nodes know about other nodes throught the 'address book', DHT
// the DHT could be organised by a central authourity but for the purpose and functionality of this network
// a more distributed approach is preferred... 
// A change in the DHT in one node will be pinged to each node in the network, then each node will compare the TIEMSTAMP on its DHT with the one it has just been sent
// and will choose the newest one as its list... 

//book_date: