#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MX_STR_LEN 100

void parse_message(struct file_node * f,char * dataseg);
struct file_node * find_file_node(struct file_node * f, int ID);

//nugget of individual file
struct node {
    int segID;
    char * message;
    struct node * next;
};

//
struct file_node{
    int fileID;
    struct file_node * next;
    struct node * data;
};

int main(){
    printf("hello world\n");

    //keep head of File linked list in main
    struct file_node * head = NULL;
    head = (struct file_node*)malloc(sizeof(struct file_node));
    head->fileID = 13;
    head->next = NULL;


    parse_message(head,"1111.2222.333.bleh");

    return 0;
}
/*
reciever code
takes all bits of message
use node.cpp parser to separate each value
main() holds linked-linked lists
linked list for each separate file ID
Each segment ID starts at 100 -> create a node per 1
If segID is out of order, create nodes in between, with no filling

*/

//Takes full message, uses individual bits to call function and sort messages
void parse_message(struct file_node * f,char * dataseg){
    int id, seg, wordlength;
    char* word;

    // parse msg
    char * parse = strtok(dataseg, ".");
    printf("Adding file to node %s...\n", parse);
    // read in file ID
    parse = strtok(NULL, ".");
    id = atoi(parse);
    // read in seg ID
    parse = strtok(NULL, ".");
    seg = atoi(parse);
    // read in data
    parse = strtok(NULL, "\0");
    wordlength = strlen(parse);
    word = (char*)malloc(sizeof(wordlength));
    strcpy(word, parse);

    //begin putting data in correct linked lists
    struct file_node * ff = find_file_node(f,14);

    if(ff == NULL){//TODO create new node and input data
        printf("NULL node given from function\n");
    }
    else{//TODO input seg data to node
        printf("Node has file ID = %d\n",ff->fileID);
    }

}
    //find the corrosponding file node in linked list to dataseg
    //returns file node that has matching file ID
    struct file_node * find_file_node(struct file_node * f, int ID){
        int check = 0;
        while(f != NULL && check != 1){
            printf("here\n");
            if(f->fileID == ID){
                check = 1;
            }
            else{
                printf("going next\n");
                f = f->next;
            }
        }
        return f;
    }