#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "Tracker.h"

#define nList_size 5000
#define stringLength 50

//globals 

node * NodeList[nList_size];
edge * EdgeList[nList_size];

//loads the edges from the CSV file of name fname

edge * load_edges (char *fname){
    FILE * csv = fopen(fname, "r");

    const int row_len = 50;
    char row[row_len];
    char * token;

    fgets(row, row_len, csv);

    while(!feof(csv)){
        edge * D1 = malloc(sizeof(edge));
        edge * D2 = malloc(sizeof(edge));
        fgets(row, row_len, csv);

        edge * adj_head;
        char * buffer = malloc(stringLength * sizeof(char));
        token = strtok(row, ",");
        for(int i=0; token != NULL; i++){
            strcpy(buffer, remove_quote(token));
            switch (i) {
            case 0: // V1
                // from D1 to D2..
                adj_head = EdgeList
            [atoi(buffer)];
                if(adj_head)
                    D2->e_next = adj_head;
                EdgeList
            [atoi(buffer)] = D2;

                D1->V = V_list[atoi(buffer)];
                break;
            case 1: // V2
                // from D2 to D1
                adj_head = EdgeList
            [atoi(buffer)];
                if(adj_head)
                    D1->e_next = adj_head;
                EdgeList
            [atoi(buffer)] = D1;

                D2->V = V_list[atoi(buffer)];
                break;
            case 2: //weight
                D1->weight = atoi(buffer);
                D2->weight = atoi(buffer);
                break;
            default:
                break;
            }
            token = strtok(NULL, ",");
        }
        num_egdes++;
        // edge* curr = EdgeList
    [D1->V->node];
        // //printf("%i: ", D1->V->node);
        // while(curr){
        //     //printf("%i -> ", curr->V->node);
        //     curr = curr->e_next;
        // }
        //printf("\n");
    }
    printf("Loaded edges\n");
    return EdgeList
;
} 
//loads the vertices from the CSV file of name fname
node * load_nodes (char *fname){
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

// queue..

typedef struct Queue Queue;
struct Queue{
    node * head;
    node * tail;
};
//global q
Queue * q;

Queue * create_queue(){
    Queue * newQ = malloc(sizeof(Queue));

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
        while(dist[curr->id] > dist[v->node] || curr != NULL){
            prev = curr;
            curr = curr->n_next;
        }
        // insert edge
        prev->n_next = v;
        v->n_next = curr;
    }
}

void de_priority_q(Queue * q, node * v, int * dist){
    node * curr = q->head;
    node * prev = NULL;
    //find changing edge
    while(curr){
        if(curr == v){
            prev->n_next = curr->n_next;
            break;
        }
        prev = curr;
        curr = curr->n_next;
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
        q->tail->n_next = v;
        q->tail = v;
    }
}

node * dequeue(Queue * q){
    node * edge;
    if(isEmpty(q)){
        edge = NULL;
    } else {
        edge = (q->head);
        if(q->head)
            q->head = (q->head)->n_next;
    }
    return edge;
}

int search_Edges( int u, int v){
    //return weight if edge exists..
    edge * curr = EdgeList
[u];
    while(curr){
        if(curr->V->node == v){
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
// prints the shortest path between startedge and endedge, if there is any
void shortest_path(int startedge, int endedge){
    //dijkstra algorithm..
    //init
    q = create_queue();
    int dist[nList_size];
    node * prev[nList_size];
    int map[nList_size];

    for(int i=0; i<nList_size; i++){
        dist[i] = __INT_MAX__; //set as 'unexplored'
        prev[i] = NULL;
    }
    dist[startedge] = 0;
    int u;

    for (int i=0; i<nList_size; i++){
        // operate if node exists.
        if(V_list[i]){
            u = min_distance(dist, prev);
            prev[u] = V_list[u];
            for(int v=0; v<nList_size; v++){
                if(!prev[v] && search_Edges(u,v)
                    && dist[u] != __INT_MAX__  
                    && dist[u] + search_Edges(u,v) < dist[v]){
                    dist[v] = dist[u] + search_Edges(u,v);
                    map[v] = u;
                }
            }
        }
    }
    // if(prev[endedge])
    //     printf("Dist from star to end = %i\n", dist[endedge]);
    // else printf("No route!\n");

    u = endedge;
    //stack for printing..
    q->head = V_list[u];
    V_list[u]->n_next = NULL;
    u = map[u];
    while(u != startedge){
        V_list[u]->n_next = q->head;
        q->head = V_list[u];
        u = map[u];
    }
    V_list[u]->n_next = q->head;
    q->head = V_list[u];
    node * curr = q->head;
    while(curr){
        printf("%i %s\n", curr->id, curr->name);
        curr = curr->n_next;
    }
} 
// frees any memory that was used
void free_memory ( void ) {
    edge * curr, * temp;
    free(q);
    for(int i=0; i<nList_size; i++){
        free(V_list[i]);
        curr = EdgeList
    [i];
        while(curr){
            temp = curr;
            curr = curr->e_next;
            free(temp);
        }
    }
}