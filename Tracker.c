#include <stdlib.h>
#include <stdio.h>
#include <math.h>


void list_add(node_list * new_node, node_list * head){

    node_list * temp = head;
    head = new_node;
    head->next = temp;
}

void list_remove(node_list * old_node, node_list * head){

    node_list * curr = head;
    node_list * prev; 
    if(head->id == old_node->id){
        prev = head;
        head->next = head;
        dalloc_node(prev);
    }
    while(curr->next != NULL){
        if(curr->id == old_node->id){
            prev->next = curr->next;
            dalloc_node(curr);
            printf("Node succesfully removed from list... data re-allocated\n")
            return void;
        }
        prev = curr;
        curr = curr->next;
    }
    printf("Error: node not found (list_remove)\n");
    return void;
}
 
// finds the node with the highest weighting...
// i.e. the node of which to distribute for a certain segment of a certain file...
int rendezvous(int file_key, int file_seg, node_list * head){

    int best_node = 0, hash_val, best_hash = 0;
    node_list * curr = head;


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
int hash(int key, int seg, node){

    long long unsigned mul;
    mul = key * seg;
    mul = mul * node;
    mul = mul * key;
    mul = mul * 672;
    mul = mul * pow(seg, 4);
    mul = mul % 12487;
    return mul;
}