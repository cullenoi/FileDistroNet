#ifndef NODE_H
#define NODE_H

#define nList_size 5000
#define MX_STR_LEN 100

#include <string>
#include "Tracker.h"
#include "Routing.h"

class Node {

    private:
        unsigned address;
        char * name;
        node * address_book;
        edge ** edge_list;
        dataset * data;
        dataset * file;
        int file_list[100];
        //book_date: yy/mm/dd/hh/mm/ss/..
        unsigned book_date;
    public:
    //comstructs node
        Node(){

            address = 0;

            name = (char*)malloc(MX_STR_LEN * sizeof(char));

            address_book = NULL;

            edge_list = NULL;

            data = (dataset*)malloc(sizeof(dataset));

            file = (dataset*)malloc(sizeof(dataset));

            file->id = 0;
            file->seg = 0;

            file->data = (char*)malloc(MX_STR_LEN * sizeof(char));

            book_date = 0;

        }
        //loads the vertices from the CSV file of name fname
        node * load_nodes (char *fname); 
        //loads the edges from the CSV file of name fname
        edge ** load_edges (char *fname);  
        int init_node(char * argv[]);
        int load_node_info (char *fname);
        

        int book_update(int node_id, int action);
        int BellmanFort();

        unsigned get_address();
        node * get_node_list();
        edge ** get_edge_list();

        void set_name(char * name);
};

#endif