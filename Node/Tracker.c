#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "Tracker.h"

void list_add(node * new_node, node * head){

    node * temp = head;
    head = new_node;
    head->next = temp;
}

void list_remove(node * old_node, node * head){

    node * curr = head;
    node * prev; 
    if(head->id == old_node->id){
        prev = head;
        head->next = head;
        dalloc_node(prev);
    }
    while(curr->next != NULL){
        if(curr->id == old_node->id){
            prev->next = curr->next;
            dalloc_node(curr);
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
int rendezvous(int file_key, int file_seg, node * head){

    int best_node = 0, hash_val, best_hash = 0;
    node * curr = head;


    while(curr->next != NULL){
        hash_val = hash(file_key, file_seg, curr->id);
        if(hash_val > best_hash){
            best_node = curr->id;
            best_hash = hash_val;
        }
        curr = curr->next;
    }

    return best_node;

}

// devolops a hash key based on the file, file segment, and target node...
int hash(int key, int seg, int node){

    long long unsigned mul;
    mul = key * seg;
    mul = mul * node;
    mul = mul * key;
    mul = mul * 672;
    mul = mul * pow(seg, 4);
    mul = mul % 12487;
    return mul;
}