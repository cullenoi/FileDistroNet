#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void data_insert_order(struct data_node * root);struct data_node *get_data_node(int value,char *word);
struct data_node * data_insert(struct data_node * root,int ID,char * message);
struct file_node *getNode(int value);
struct file_node *insert(struct file_node *root, int value);
void insertorder(struct file_node *root);
void data_insert_order(struct data_node *root);
struct file_node * find_node(struct file_node * root, int value);
struct file_node *parse_message(struct file_node *root,char*dataseg);
void create_file(struct file_node * root, int value);
void add_to_file(FILE * f, struct data_node * root);


struct file_node{
int ID;
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

struct data_node *get_data_node(int value,char *word){
struct data_node *newNode = malloc(sizeof(struct data_node));
newNode->left = NULL;
newNode->right = NULL;
newNode->ID = value;
int wordlength = strlen(word);
newNode->message = (char*)malloc(sizeof(wordlength));
strcpy(newNode->message,word);
printf("HHHHHHHHHHHHHHEEEEEEEEEERERERER %s\n", newNode->message);
return newNode;
}

struct data_node * data_insert(struct data_node * root,int ID,char * message){
if(root == NULL){
return get_data_node(ID,message);
}
if(root->ID < ID){
root->right = data_insert(root->right,ID,message);
}
else if(root->ID > ID){
root->left = data_insert(root->left,ID,message);
}
return root; 
}

struct file_node *getNode(int value){
struct file_node *newNode = malloc(sizeof(struct file_node));
newNode->left = NULL;
newNode->right = NULL;
newNode->data = NULL;
newNode->ID = value;
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
if(root == NULL)
return;
insertorder(root->left);
printf("%d ",root->ID);
insertorder(root->right);
}

void data_insert_order(struct data_node *root){
if(root == NULL){
return;
}
data_insert_order(root->left);
printf("%d%s ",root->ID,root->message);
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
    int id, seg, wordlength;
    char* word;

    // parse msg
    char * parse = strtok(dataseg, ".");
    printf("1. |NEW ENTRY| Adding file to node %s...\n", parse);
    // read in file ID
    parse = strtok(NULL, ".");
    id = atoi(parse);
    printf("2.Input ID is %d\n",id);
    // read in seg ID
    parse = strtok(NULL, ".");
    seg = atoi(parse);
    // read in data
    parse = strtok(NULL, "\0");
    wordlength = strlen(parse);
    word = (char*)malloc(sizeof(wordlength));
    strcpy(word, parse);

    //put file node in binary tree
    root = insert(root,id);
    printf("root is currently %d\n",root->ID);

    //find file node to insert seg
    struct file_node * c = root;
    c = find_node(root,id);
    printf("c is currently %d\n",c->ID);
    
    //inserting seg in file node binary tree
    c->data = data_insert(c->data,seg,word);
    printf("the message in c->data is %s\n",c->data->message);
    return root;
}

void create_file(struct file_node * root, int value){
    //go through file binary tree to find match of file id
    //when find match, create file
    if(root == NULL){
        printf("This file does not exist\n");
    }
    else if(root->ID == value){
        printf("here is %d\n",root->ID);
        FILE * fp;
        fp = fopen("file_test.txt","w+");
        fputs("This is a new file\n",fp);
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
    //while(root->message){
        fputs(root->message,f);
    //}
    add_to_file(f,root->right);
}

int main(){
struct file_node *root = NULL;

/*root = parse_message(root,"1111.13.100.bleh");
root = parse_message(root,"1111.15.101.bleh");
//root = parse_message(root,"1111.2222.102.bleh");
//root = parse_message(root,"1111.2222.103.bleh");
root = parse_message(root,"1111.2224.104.bleh");
root = parse_message(root,"1111.13.105.bleh");
//root = parse_message(root,"1111.2222.106.bleh");
root = parse_message(root,"1111.1012.107.bleh");*/

root = parse_message(root,"1111.2222.100.123456789101112 ");
root = parse_message(root,"1111.2222.101.123456 ");
root = parse_message(root,"1111.2222.102.123456 ");
root = parse_message(root,"1111.2222.103.d ");
root = parse_message(root,"1111.2222.104.eez ");
root = parse_message(root,"1111.2222.105.fnut ");
root = parse_message(root,"1111.2222.106.zzzzzz ");

/*root = parse_message(root,"1111.2222.100.a");
root = parse_message(root,"1111.2222.101.b");
root = parse_message(root,"1111.2222.102.c");
root = parse_message(root,"1111.2222.103.d");
root = parse_message(root,"1111.2222.104.e");
root = parse_message(root,"1111.2222.105.f");
root = parse_message(root,"1111.2222.106.g");*/

insertorder(root);
//root = root->right;
//root = root->right;
printf("\n");
data_insert_order(root->data);

create_file(root,2222);

return 0;
}