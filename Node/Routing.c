#include <stdio.h>
//#include <string.h>
#include <stdlib.h>

#include "Routing.h"
#include "Tracker.h"
#include "Node.h"

#define PORT_OFFSET 30000
#define nList_size 5000
#define stringLength 50

//globals 

node * N_List[nList_size];

void create_N_List(node * n_list){
    node * curr = n_list;
    while(curr){
        N_List[(curr->id - PORT_OFFSET)] = curr;
        curr = curr->next;
    }
}

// queue..

typedef struct Queue Queue;
struct Queue{
    node * head;
    node * tail;
};

//global q
Queue * q;

Queue * create_queue(){
    Queue * newQ = (Queue*)malloc(sizeof(Queue));

    newQ->head = NULL;
    newQ->tail = NULL;
    
    return newQ;
}

int isEmpty(Queue * q){
    if(q->head == NULL)
        return 1;
    else return 0;
}

void priority_q(Queue * q, node * v, int * dist){
    node * curr = q->head;
    node * prev = NULL;
    if(curr == NULL)
        q->head = v;
    else{
        // find edge position in weighted priority queue
        while(dist[((curr->id) - PORT_OFFSET)] > dist[((v->id) - PORT_OFFSET)] || curr != NULL){
            prev = curr;
            curr = curr->q_next;
        }
        // insert edge
        prev->q_next = v;
        v->q_next = curr;
    }
}

void de_priority_q(Queue * q, node * v, int * dist){
    node * curr = q->head;
    node * prev = NULL;
    //find changing edge
    while(curr){
        if(curr == v){
            prev->q_next = curr->q_next;
            break;
        }
        prev = curr;
        curr = curr->q_next;
    }
    printf("found node\n");
    //re insert w/ new priority
    priority_q(q, v, dist);
}

void enqueue(Queue * q, node * v){
    if(isEmpty(q)){
        q->head = v;
        q->tail = v;
    } else {
        q->tail->q_next = v;
        q->tail = v;
    }
}

node * dequeue(Queue * q){
    node * n;
    if(isEmpty(q)){
        n = NULL;
    } else {
        n = (q->head);
        if(q->head)
            q->head = (q->head)->q_next;
    }
    return n;
}

int search_Edges(int u, int v, edge ** e_list){
    //return weight if edge exists..
    edge * curr = *(e_list + u);
    while(curr){
        if((curr->id - PORT_OFFSET) == v){
            return curr->weight;
        }
        curr = curr->e_next;
    }
    return 0;
}

int min_distance(int dist[], node * prev[]){
    int min = __INT_MAX__, min_index;
    for(int v=0; v < nList_size; v++){
        if(prev[v] == NULL && dist[v] < min){
            min = dist[v];
            min_index = v;
        }
    }
    //printf("min_index: %i\n", min_index);
    return min_index;
}
// prints the shortest path between startNode and endNode, if there is any
int * shortest_path(int startNode, edge ** e_list, node * n_list){
    //dijkstra algorithm..
    //init
    create_N_List(n_list);
    q = create_queue();
    int dist[nList_size];
    node * prev[nList_size];
    // create pointer to memory, that will be returned
    int * map = (int*)malloc(nList_size * sizeof(int));

    for(int i=0; i<nList_size; i++){
        dist[i] = __INT_MAX__; //set as 'unexplored'
        prev[i] = NULL;
    }
    dist[startNode - PORT_OFFSET] = 0;
    int u;

    for (int i=0; i<nList_size; i++){
        // operate if vertex exists.
        if(N_List[i]){
            u = min_distance(dist, prev);
            prev[u] = N_List[u];
            for(int v=0; v<nList_size; v++){
                if(!prev[v] && search_Edges(u,v,e_list)
                    && dist[u] != __INT_MAX__  
                    && dist[u] + search_Edges(u,v,e_list) < dist[v]){
                    dist[v] = dist[u] + search_Edges(u,v,e_list);
                    map[v] = (u + PORT_OFFSET);
                }
            }
        }
    }
    // if(prev[endNode])
    //     printf("Dist from star to end = %i\n", dist[endNode]);
    // else printf("No route!\n");


    // return next hop...
    // printf("route test to 1161\n");
    // int next_hop;
    // u = 1161;
    // while(u != startNode){
    //     printf("%i -> ", u);
    //     next_hop = u;
    //     u = map[u];
    // }
    // printf(" %i \n", u);

    // for(int i=0; i<nList_size; i++){
    //     printf("%i -> %i\n", i, map[i]);
    // }


    // return map array...
    free_memory();
    return map;
   
    // stack for printing..
    // q->head = N_List[u];
    // N_List[u]->q_next = NULL;
    // u = map[u];
    // while(u != startNode){
    //     N_List[u]->q_next = q->head;
    //     q->head = N_List[u];
    //     u = map[u];
    // }
    // N_List[u]->q_next = q->head;
    // q->head = N_List[u];
    // node * curr = q->head;
    // printf("Route...\n");
    // while(curr){
    //     printf("%i\n", curr->id);
    //     curr = curr->q_next;
    // }
} 
// frees any memory that was used
void free_memory ( void ) {
    edge * curr, * temp;
    free(q);
    // for(int i=0; i<nList_size; i++){
    //     free(N_List[i]);
    //     // curr = EdgeList[i];
    //     // while(curr){
    //     //     temp = curr;
    //     //     curr = curr->e_next;
    //     //     free(temp);
    //     // }
    // }
}

int next_hop(int dest, int self, int * map){
    int count = 0;
    int next_hop;
    int u = dest;
    while(u != self){
        count++;
        if(count > 100) break;
        next_hop = u;
        u = map[(u - PORT_OFFSET)];
    }
    return next_hop;
}


