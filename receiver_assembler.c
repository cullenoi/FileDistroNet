#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MX_STR_LEN 100

void parse_message(struct file_node * f,char * dataseg);
struct file_node * find_file_node(struct file_node * f, int ID);
struct node * search_data(struct node * n,int ID);

//nugget of individual file
struct node {
    int segID;
    char * message;
    struct node * left;
    struct node * right;
};

//
struct file_node{
    int fileID;
    struct file_node * next;
    struct node * data;
};

int main(){
    printf("hello world\n");

    //what i have learned: make a temp variable first, then asign the p->next to it
    //need to assign a new temp variable->one per instance of function


    struct file_node *temp = (struct file_node*)malloc(sizeof(struct file_node));



    //keep head of File linked list in main
    struct file_node * head = NULL;
    head = (struct file_node*)malloc(sizeof(struct file_node));
    struct file_node * p = NULL;
    p = (struct file_node*)malloc(sizeof(struct file_node));
    p = head;
    p->next = NULL;
    p->data = NULL;


    parse_message(p,"1111.13.333.bleh");
    parse_message(p,"1111.15.333.bleh");
    parse_message(p,"1111.2222.333.bleh");
    parse_message(p,"1111.2222.333.bleh");
    parse_message(p,"1111.2224.333.bleh");
    parse_message(p,"1111.13.333.bleh");
    parse_message(p,"1111.2222.333.bleh");


    //Show full list
    while(head != NULL){
        printf("|%d|->",head->fileID);
        head = head->next;
    }
    printf("\n");

    return 0;
}

//Takes full message, uses individual bits to call function and sort messages
void parse_message(struct file_node * f,char * dataseg){
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

    //begin putting data in correct linked lists
    //ff contains element of linked list->either NULL or matching file ID
    struct file_node * ff = NULL;
    ff = find_file_node(f,id);
    if(ff == NULL){
        printf("|ff is NULL\n");
        ff = f;
        while(ff->next != NULL){
            ff = ff->next;
        }
        struct file_node * temp = (struct file_node*)malloc(sizeof(struct file_node));
        temp->fileID = id;
        temp->next = NULL;
        temp->data = NULL;
        ff->next = temp;
        ff = ff->next;
    }

    //put word in seg order
    //search_data(ff->data,seg);
     

}

//traverse binary tree to see if it contains node with seg ID
struct node * search_data(struct node * n,int ID){
    int check = 0;
    //find node with matcing id or NULL end of list
    while(n != NULL && check != 1){
        if(n->segID = ID){
            check = 1;
        }
        else{
            //n = n->next;
        }
        if(n = NULL){
            //create new node
        }
        else{
            //end of function
        }
    }
    return NULL;
}



    //find the corrosponding file node in linked list to dataseg
    //returns file node that has matching file ID
struct file_node * find_file_node(struct file_node * f, int ID){
    int check = 0;
    while(check != 1 && f != NULL){
        if(f->fileID == ID){
            check = 1;
        }
        else{
            f = f->next;
        }
    }
    if(f == NULL){
        return NULL;
    }
    else{
        return f;
    }
}
