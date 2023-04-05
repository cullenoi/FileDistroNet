#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "receiver_assembler.h"


struct data_node *get_data_node(int value,char *word){
struct data_node *newNode = malloc(sizeof(struct data_node));
newNode->left = NULL;
newNode->right = NULL;
newNode->ID = value;
int wordlength = strlen(word);
char * temp = (char*)malloc((MX_STR_LEN)*sizeof(char));
 strcpy(temp,word);
newNode->message = temp;
return newNode;
}

struct data_node * data_insert(struct data_node * root,int ID,char * message, struct file_node * f){
if(root == NULL){
    f->num_data_nodes++;//adds to the number of data nodes per file node
return get_data_node(ID,message);
}
if(root->ID < ID){
root->right = data_insert(root->right,ID,message,f);
}
else if(root->ID > ID){
root->left = data_insert(root->left,ID,message,f);
}
return root; 
}

struct file_node *getNode(int value){
struct file_node *newNode = malloc(sizeof(struct file_node));
newNode->left = NULL;
newNode->right = NULL;
newNode->data = NULL;
newNode->ID = value;
newNode->complete = 0;
newNode->num_data_nodes = 0;
newNode->end_present = 0;
newNode->lastID = 0;
return newNode;
}

struct file_node *insert(struct file_node *root, int value){
if(root == NULL){
return getNode(value);
}
if(root->ID < value){
root->right = insert(root->right,value);
}
else if(root->ID > value){
root->left = insert(root->left,value);
}
return root;
}

void insertorder(struct file_node *root){
if(root == NULL){
    return;
}
insertorder(root->left);
printf("%d ",root->ID);
insertorder(root->right);
}

void data_insert_order(struct data_node *root){
if(root == NULL){
return;
}
data_insert_order(root->left);
printf("%d %s ",root->ID,root->message);
data_insert_order(root->right);
}

struct file_node * find_node(struct file_node * root, int value){
    if(root == NULL){
        return NULL;
    }
    else if (root->ID == value){
        return root;
    }
    else if(root->ID > value){
        return find_node(root->left,value);
    }
    else if(root->ID < value){
        return find_node(root->right,value);
    }
    return NULL;
}

struct file_node *parse_message(struct file_node *root,char*dataseg){
    int id, seg, wordlength,end;
    char* word;

    // parse msg
    char * parse = strtok(dataseg, "-");
    // read in file ID
    parse = strtok(NULL, "-");
    parse = strtok(NULL, "-");
    parse = strtok(NULL, "-");
    id = atoi(parse);
    // read in seg ID
    parse = strtok(NULL, "-");
    seg = atoi(parse);
    parse = strtok(NULL, "-");
    end = atoi(parse);
    // read in data
    parse = strtok(NULL, "\0");
    wordlength = strlen(parse);
    word = (char*)malloc((MX_STR_LEN)*sizeof(char));
    strcpy(word, parse);

    //put file node in binary tree
    root = insert(root,id);

    //find file node to insert seg
    struct file_node * c = root;
    c = find_node(root,id);
    
    //inserting seg in file node binary tree
    c->data = data_insert(c->data,seg,word,c);
    //if the last segment in a file is present, mark that on the node
    if(end == 1){
        c->end_present = 1;
        c->lastID = seg;
    }
    //check to see if the file is complete
    if(c->lastID != 0 && (c->lastID - 99)==c->num_data_nodes){
        c->complete = 1;
    }
    return root;
}

void create_file(struct file_node * root, int value){
    //go through file binary tree to find match of file id
    //when find match, create file
    if(root == NULL){
        printf("This file does not exist\n");
    }
    else if(root->ID == value){
        FILE * fp;
        char id[MX_STR_LEN];
        sprintf(id,"%d",value);
        strcat(id,".txt");
        fp = fopen(id,"w+");
        fputs("COMPLETED FILE: ",fp);
        fputs(id,fp);
        fputs("\n",fp);
        add_to_file(fp,root->data);
        fclose(fp);

    }
    else if(root->ID > value){
        create_file(root->left,value);
    }
    else if(root->ID < value){
        create_file(root->right,value);
    }
}

void add_to_file(FILE * f, struct data_node * root){
    if(root == NULL){
        return;
    }
    add_to_file(f,root->left);
        fputs(root->message,f);
    add_to_file(f,root->right);
}

struct data_node * find_data_node(struct data_node * root,int value){
    if(root == NULL){
        return NULL;
    }
    else if (root->ID == value){
        return root;
    }
    else if(root->ID > value){
        return find_data_node(root->left,value);
    }
    else if(root->ID < value){
        return find_data_node(root->right,value);
    }
    return NULL;
}

char *search_seg(struct file_node * root, int fileID, int segID){
    root = find_node(root,fileID);
    struct data_node * temp = NULL;
    if(root == NULL){
        return NULL;
    }
    else{
        temp = root->data;
        temp = find_data_node(temp,segID);
        if(temp == NULL){
            return NULL;
        }
        else{
            return temp->message;
        }
    }
    return NULL;
}

void complete_files(struct file_node * root){
    if(root == NULL){
        return;
    }
    complete_files(root->left);
    if(root->complete == 1){
        printf("%d ",root->ID);
    }
    complete_files(root->right);
}

int check_database(struct file_node * root, int fileID, int segID){
    root = find_node(root,fileID);
    struct data_node * temp = NULL;
    if(root == NULL){
        return 0;
    }
    else{
        temp = root->data;
        temp = find_data_node(temp,segID);
        if(temp == NULL){
            return 0;
        }
        else{
            return 1;
        }
    }
    return 0;
}

int isComplete(struct file_node * root, int fileID){
    root = find_node(root,fileID);
    if(root == NULL){
        return 0;
    }
    if(root->complete == 1){
        return 1;
    }
    else{
        return 0;
    }
}
/*
int main(){
struct file_node *root = NULL;

root = parse_message(root,"198.10.12.145|0|1111|13|100|0|hjksdlhgvshgrsvhnkcshdgvhniskrdgc\n");
root = parse_message(root,"198.10.12.145|0|1111|15|109|1|babbabbbabababadbflasdjfbsaf\n");
root = parse_message(root,"198.10.12.145|0|1111|13|101|0|shingodingobingo\n");
root = parse_message(root,"198.10.12.145|0|1111|15|103|0|aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa\n");
root = parse_message(root,"198.10.12.145|0|1111|222|107|0|1234567891011121314151617181920212223242526272829303132333435363738\n");
root = parse_message(root,"198.10.12.145|0|1111|13|103|1|1234567891011121314151617181920212223242526272829303132333435363738\n");
root = parse_message(root,"198.10.12.145|0|1111|15|102|0|1234567891011121314151617181920212223242526272829303132333435363738\n");
root = parse_message(root,"198.10.12.145|0|1111|13|102|0|1234567891011121314151617181920212223242526272829303132333435363738\n");
root = parse_message(root,"198.10.12.145|0|1111|15|100|0|1234567891011121314151617181920212223242526272829303132333435363738\n");

root = parse_message(root,"198.10.12.145|0|1111|2222|109|1|1234567891011121314151617181920212223242526272829303132333435363738\n");
root = parse_message(root,"198.10.12.145|0|1111|2222|108|0|1234567891011121314151617181920212223242526272829303132333435363738\n");
root = parse_message(root,"198.10.12.145|0|1111|2222|107|0|1234567891011121314151617181920212223242526272829303132333435363738\n");
root = parse_message(root,"198.10.12.145|0|1111|2222|106|0|1234567891011121314151617181920212223242526272829303132333435363738\n");
root = parse_message(root,"198.10.12.145|0|1111|2222|105|0|1234567891011121314151617181920212223242526272829303132333435363738\n");
root = parse_message(root,"198.10.12.145|0|1111|2222|104|0|1234567891011121314151617181920212223242526272829303132333435363738\n");
root = parse_message(root,"198.10.12.145|0|1111|2222|103|0|1234567891011121314151617181920212223242526272829303132333435363738\n");
root = parse_message(root,"198.10.12.145|0|1111|2222|102|0|1234567891011121314151617181920212223242526272829303132333435363738\n");
root = parse_message(root,"198.10.12.145|0|1111|2222|101|0|1234567891011121314151617181920212223242526272829303132333435363738\n");
root = parse_message(root,"198.10.12.145|0|1111|2222|100|0|1234567891011121314151617181920212223242526272829303132333435363738\n");


//TODO:
//EXPAND DATAGRAM AND SWITCH TO |||||||||||||||||
//MAKE FUNCTION THAT SEARCHES FOR EXACT DATASEG AND RETURNS IT AS A CHAR *
//FUNCTION CHECKS IF FILE IS COMPLETE
//ip|port|send/recieve|fileid|segid|message
//
//function to check if all nuggets are here
//create request create dest port, 
//change parser to , instead of .
//while loop check if file is all neggets theres, then build it
//datagram has flag saying send or recieve ->bool
//datagram has eof yes/no bool in it
//cool to have ->list files comleted and half completed and stored

insertorder(root);
printf("\n");
data_insert_order(root->data);

create_file(root,2222);
create_file(root,13);
create_file(root,15);
create_file(root,222);

char * temp = search_seg(root,13,100);
printf("char returned is %s\n",temp);
temp = search_seg(root,12,100);
printf("char returned is %s\n",temp);
temp = search_seg(root,15,103);
printf("char returned is %s\n",temp);
temp = search_seg(root,2222,100);
printf("char returned is %s\n",temp);

//root = root->right;
//root = root->right;
//root = root->right;
printf("the number of node is %d and the last id is %d and complete status is %d\n",root->num_data_nodes,root->lastID,root->complete);
complete_files(root);

return 0;
}*/