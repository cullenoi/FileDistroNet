#ifndef NODE_H
#define NODE_H

#include "Tracker.h"

class Node {

    private:
        unsigned address;
        node * address_book;
        unsigned date;
    public:
        int init_node(char * argv);
        int book_update();
        int BellmanFort();
        

};


#endif NODE_H