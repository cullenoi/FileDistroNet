#ifndef RECV_H
#define RECV_H

#define MX_STR_LEN 100

struct file_node{
int ID;
int complete;
int num_data_nodes;
int end_present;
int lastID;
struct data_node * data;
struct file_node *left;
struct file_node *right;
};

struct data_node{
int ID;
char * message;
struct data_node *left;
struct data_node *right;
};

void data_insert_order(struct data_node * root);struct data_node *get_data_node(int value,char *word);

struct data_node * data_insert(struct data_node * root,int ID,char * message,struct file_node * f);

struct file_node *getNode(int value);

struct file_node *insert(struct file_node *root, int value);

void insertorder(struct file_node *root);

void data_insert_order(struct data_node *root);

struct file_node * find_node(struct file_node * root, int value);

struct file_node *parse_message(struct file_node *root,char*dataseg);

void create_file(struct file_node * root, int value);

void add_to_file(FILE * f, struct data_node * root);

char *search_seg(struct file_node * root, int fileID, int segID);

struct data_node * find_data_node(struct data_node *temp,int segID);

void complete_files(struct file_node * root);

int check_database(struct file_node * root, int fileID, int segID);

int isComplete(struct file_node * root, int fileID);

#endif