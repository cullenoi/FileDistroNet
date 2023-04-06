#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

#include "Tracker.h"

#define MX_MSG_LEN 20
#define LIST_ADD "0001"
#define LIST_REMOVE "0002"
#define VOID_SEG "000"

// construct list update message
char * list_update(int dest, int cmd, int new_node, int connect, int qual){

    char * msg = (char*)malloc(MX_MSG_LEN * sizeof(char));
    char buffer[MX_MSG_LEN];
    
    sprintf(buffer, "%i", dest);
    strcat(msg, buffer);
    strcat(msg, ".");
    // add/remove node command
    // using cmd as a bool condition
    (cmd) ? strcat(msg, LIST_ADD):strcat(msg, LIST_REMOVE);
    strcat(msg, "|");

    strcat(msg, VOID_SEG);
    strcat(msg, "|");

    //TODO
    //xxxx.yyyy.zzz
    sprintf(buffer, "%i", new_node);
    strcat(msg, buffer);
    strcat(msg, ".");
    sprintf(buffer, "%i", connect);
    strcat(msg, buffer);
    strcat(msg, ".");
    sprintf(buffer, "%i", qual);
    strcat(msg, "\0");

    return msg;
}
// void list_add(node * n_head, edge ** e_head, int new, int connect, int qual){

//     // Node list

//     node * temp = n_head;
//     // create new node struct
//     node * new_node = (node*)malloc(sizeof(node));
//     // assign values
//     new_node->id = new;
//     new_node->next = temp;
//     // assign new head of the list
//     n_head = new_node;

//     // Edge list
// }

void list_remove(node * old_node, node * head){

    node * curr = head;
    node * prev; 
    if(head->id == old_node->id){
        prev = head;
        head->next = head;
        free(prev);
    }
    while(curr->next != NULL){
        if(curr->id == old_node->id){
            prev->next = curr->next;
            free(curr);
            printf("Node succesfully removed from list... data re-allocated\n");
            return;
        }
        prev = curr;
        curr = curr->next;
    }
    printf("Error: node not found (list_remove)\n");
    return;
}

// finds the node with the highest weighting...
// i.e. the node of which to distribute for a certain segment of a certain file...
int * rendezvous(int file_key, int file_seg, node * head, int self){

    // lists: index 0 has the highest value, index 1 has the second highest value...
    int  * best_node = (int*)malloc(REDUNDANCY * sizeof(int));
    memset(best_node, 0, REDUNDANCY);

    int best_hash[REDUNDANCY] = {0,0,0};
    int hash_val;
    node * curr = head;
    while(curr){
        if(curr->id != self){
            hash_val = hash(file_key, file_seg, curr->id);
            if(hash_val > best_hash[0]){
                // node...
                // shift lists down by one.
                best_node[2] = best_node[1];
                best_node[1] = best_node[0];
                // hash...
                // shift lists down by one.
                best_hash[2] = best_hash[1];
                best_hash[1] = best_hash[0];
                //assign new value
                best_node[0] = curr->id;
                best_hash[0] = hash_val;
                
            }
            else if(hash_val > best_hash[1]){
                // node...
                // shift lists down by one.
                best_node[2] = best_node[1];
                // hash...
                // shift lists down by one.
                best_hash[2] = best_hash[1];
                //assign new value
                best_node[1] = curr->id;
                best_hash[1] = hash_val;
            }
            else if(hash_val > best_hash[2]){
                //assign new value
                best_node[2] = curr->id;
                best_hash[2] = hash_val;
            }
        }
        curr = curr->next;
    }
    return best_node;
}

// devolops a hash key based on the file, file segment, and target node...
int hash(int key, int seg, int node){

    long long unsigned mul = 1;
    mul = mul * (node - 30000) * 17 * seg;
    mul = mul % 1432;
    mul = mul * key % 191;
    mul = mul * 54 * seg;
    mul = mul + (node - 34422);
    mul = mul + seg * 3;
    mul = mul % 12487;
    return mul;
}