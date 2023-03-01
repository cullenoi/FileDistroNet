#ifndef NODE_H
#define NODE_H

#include "Tracker.h"

class Node {

    private:
        unsigned address;
        node_list * address_book;
        unsigned date;
    public:
        int init_node(node_list * book, unsigned address);
        int book_update();
        int BellmanFort();
        

};


#endif NODE_H