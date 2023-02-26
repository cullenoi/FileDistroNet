#ifndef MODULE_TRACKER
#define MODULE_TRACKER

// list of nodes within the network, can be updated...
typedef struct node_list{
    int id;
    node_list * next;
} node_list;

// add a node to the node list
void list_add(node_list * new_node, node_list * head);

// remove a node from the list.. re allocate all the data from the node into the network...
void list_remove(node_list * old_node, node_list * head);

// choose the node to send a segment of a file to... highest weighed node wins...
int rendezvous(int file_key, int file_seg, node_list * head);
 
// hash function develops a int based on input parameters... aim to be as distributed as possible among all possible outcomes...
int hash(int key, int seg, node);


#endif MODULE_TRACKER

/*** end of file ***/