#include "Client.h"
#include "Server.h"
#include "PublicDef.h"
#include <pthread.h>

#include <iostream>
#include <vector>
//#include <string>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "Node/Tracker.h"
#include "Node/Node.h"
#include "Node/Routing.h"
#include "Request.h"
#include "receiver_assembler.h"


using namespace std;

char * IP_index[nList_size] = {NULL};

// Globals...
///////////////////////////////////////////////NODE GLOBAL var
Node N1;
// node * list ;
// node * curr;
// edge ** e_arr;
// edge * e_head;

struct file_node *root = NULL;

int sockfd , talkfd ;//SOCKET FILE DESCRIPTOR returns -1 on errno
struct sockaddr_in hints;
struct sockaddr_in their_addr;
socklen_t addr_size;

int PORT;

typedef struct argy {
    int portptr;
    dataset * data_file;
    int * map;
} argy;



// void process_buffer(char *buffer, int max_len)
// {//ADDS NULL TO END OF STRING 
//     for (int i = 0; i < max_len; i++)
//     {
//         if ((buffer[i] == '\n') || (buffer[i] == '\r'))
//         {
//             buffer[i] = '\0';
//             break;
//         }
//     }
// }
pthread_mutex_t mutex;
int err=0;
void *ServerT( void* A){
    printf("IN server\n");
    argy *B = (argy *)A;

    int addr = B->portptr;
    dataset * data_file = B->data_file;
    int * map = B->map;

    if(listen(sockfd,BACKLOG)<0)//-1 = errno
    {
        printf("INIT_Server socket Listening failed...\n");
        return 0;
    }
    printf("Listening...\n");
    //accept time how it works is somewhere will try to call coonect()
    //to the port im listening on..
    // Their connection will be queued waiting to be accepted()
    // you call accept tell it to get the pending connection
    // IT WILL RETURN A NEW SOCKFD FOR THIS CONNECTIONTHE FIRST SOCKFD IS STILL LISTENING FOR NEWCOMERS
    // BUT THE NEW ONE HANDLES SOLELY THE BACK AND FORTH WITH THIS CONN
    
while(1){
    sleep(3);//Sleep for a bit to allow the client to do stuff..a
    Recieve(addr, data_file, map);//ATM NO NEED TO CALL ANYTHING BECAUSE WE USE GLOBAL VAR RN
// Command exits as connection is finished..
    //TODO simple messaging for DEV Please remove afterusage....
    }
    printf("all is well! :))\n");
    free(B);
    return 0;
}


int main(int argc, char *argv[]){
//////////////////////ININT ROOT HERE doublw pointer
    
//////////////////////////////////////////////////////////////////
//Node Initialisation: place where node PORT is generated and its address book...
/////////////////////////////////////////////////////////////////
    Node N1;
	if(!N1.init_node(argv)){
		printf("Err in init node (port id: %i)\n", atoi(argv[1]));
	}
    PORT = N1.get_address();//GLOBALLY SETS PORT NUMBER 
    int * map = N1.get_map();
    printf("Server thread start\n");

    node * curr = N1.get_node_list();
    while(curr){
        // FOR NOW: odd/even select on nodes
        char * IP_addr = (char*)malloc(MX_STR_LEN * sizeof(char));
        if(curr->id % 2 == 0){
            strcpy(IP_addr, RP1);
        } else strcpy(IP_addr, RP2);
        printf("-> %i\n", curr->id);
        IP_index[(curr->id - IPSTART)] = IP_addr;
        curr = curr->next;
    }
///////////////////////////////////////////////////////////////// 
//Server Section:
//////////////////////////////////////////////////////////////////
printf("Survived Conor Bowler\n");
pthread_mutex_init(&mutex,NULL);
argy A ;    //= (argy*)malloc(sizeof(argy));

int my_port = N1.get_address();
(A.portptr) = my_port;
(A).data_file = N1.get_data_list();
A.map = N1.get_map();

static pthread_t Serv;
int fail;
long xy;
 err =Server();
    if(err != 0 ){
        printf("Error on INIT Server see errors:\n");
        return 0;
    } 

xy = pthread_create(&Serv,NULL, ServerT ,&A);

if(xy){
    printf("@Thread ERROR\n");
    exit(-1);
}
int ch; 
    do {
        printf("\nPlease Select the following options: >>>\n1.Publish File\n");
        printf("2.Request File\n0.Quit\n");
        printf("\nEnter choice:");
        scanf("%d", &ch);
        switch (ch)
        {
        case 1:
            FileDistro(N1.get_file(),N1.get_address(), 
                    N1.get_node_list(), N1.get_map());
            break;
            
        case 2:
            printf("Enter a file ID to request the file.\n");
            cout << "Enter 0 to get a list of current known files.\n";
            int input;
            cin >> input;
            if(input){
                RequestFile(root, input, N1.get_node_list(), 
                            N1.get_map(), N1.get_address(), IP_index);//I NEED ASSISTANCE//call root
            } else {
                N1.printFileList();
            }
            break;
        case 0:
            printf("\nLeaving\n");
            break;
        default:
            printf("\nWrong choice\n");
        }
    } while (ch);
pthread_join(Serv,NULL);
// free(A);
pthread_mutex_destroy(&mutex);
    return 0;

}

void RequestHandler(){

}
int Server()
{
    // int sockfd , talkfd ;//SOCKET FILE DESCRIPTOR returns -1 on errno
    // struct sockaddr_in hints;
    // struct sockaddr_storage their_addr;
    // socklen_t addr_size;

    int force =1;
//     char *usrname =get_name    
//    printf("Username = %s",usrname);
    printf("Host Port number: %d",PORT);
    // struct sigaction sa;
    // int yes=1;
    // int rv1;
 if( (sockfd = socket(AF_INET, SOCK_STREAM ,0))==-1){ //Lets you choose TCP||UDP STREAM||DATAGRAM AI_INET||AI_INET6(Ip_addresse types..)
        fprintf(stderr,"INIT_Server getting socket: %s\n",gai_strerror(sockfd));
        return 1;//returning one as error check in main..
   }
   //Since we will be listening down the line we must bind the socket and the address...
  if (setsockopt(sockfd, SOL_SOCKET,SO_REUSEADDR, &force, sizeof(force)))//FORCES THIS SOCKET FD TO THE PORT
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    memset(&hints, 0, sizeof hints);//resets the struct so its not holding any memory.. 
    hints.sin_family = AF_INET;//Sets this to IPV4
    // = SOCK_STREAM;//TCP
    hints.sin_port = htons(PORT);//COnverts to big endian format.. Good practice
    hints.sin_addr.s_addr = INADDR_ANY;
   

//SIMPLE VERSION WILL NEED TO BE CHANGED DOWN THE LINE..
  
   if( bind(sockfd, (struct sockaddr *)&hints,sizeof(hints))<0   )//binds to the port we gave it to at the start.
    {
        printf("INIT_Server socket bind failed...\n");
        return 1;
    }
 

return 0;
}




void Recieve(unsigned address, dataset * data_file, int * map)// delete after usage..
{
    
    fd_set active, read;
    addr_size=sizeof(their_addr);
    // Initialize my current set
    FD_ZERO(&active);
    FD_SET(sockfd, &active);
    int k=0;
    int n;
    char buff[MX_STR_LEN]={0};
        PORT = address;//GLOBALLY SETS PORT NUMBER 


        // TODO FIX THIS THINGY
      while (1)
    {
     
        read = active;

        if (select(FD_SETSIZE, &read, NULL, NULL, NULL) < 0)
        {
            perror("Error");
            exit(EXIT_FAILURE);
        }
//service all the sockets with inputs pending//
        for (int i = 0; i < FD_SETSIZE; i++)
        {
            if (FD_ISSET(i, &read))
            {
                        //connection request on orginal socket
                if (i == sockfd)
                {
                    int client_socket;
                    
                    if ((client_socket = accept(sockfd, (struct sockaddr *)&their_addr,
                                                (socklen_t *)&addr_size)) < 0)
                    {
                        perror("accept");
                        exit(EXIT_FAILURE);
                    }
                    printf("Accepting message\n\n");
                    FD_SET(client_socket, &active);
                }
                else
                {
                    int REC_PORT = 0;
                    //data is arriving on an already connected socket
                    n = recv(i, buff, sizeof(buff), 0);
                    //Take
                    //Recieved buffer and parse first part;
                    //ADD ERROR COND FOR N
                    printf("my_port: %i\n", PORT);
                    printf("%s  = buff\n",buff);
                    // REC_PORT = PortParser(buff);//replace with Node parser....
                    // int FLAGPARSER = FlagParser(buff);//Placeholder add function which seperates fully tbh
                    // int seg,port,fileid;
                    // char* IP;
                    NodeInfo N = PortParser(buff);

                    if(N.PORT == PORT)//Meant to be here 
                    {
                        if(!N.FLAG){
                            char * retReq;
                            if(!SendBack(N.SEGNUM, N.PORT, N.IP, N.FILEID, retReq)){
                                // construct fail msg...
                                retReq = RequestFail(N.PORT, N.FILEID, N.SEGNUM, PORT);   
                            }
                            // Send answer to request
                            // Either being successful -> SendBack | or Failure RequestFail.
                            int next = next_hop(N.PORT, PORT, map);
                            ClientCreate(N.IP, next, retReq);
                        }
                        else if (N.FLAG == 1){
                        printf("Recieved Package!\n");
                        ///
                        if(!N1.add_file(buff, data_file)){
                            printf("Error on adding file to NODE Struct\n");
                        }
                                
                                root = parse_message(root,buff);//store data into data storage *must let equal root*
                                if(root == NULL){
                                    printf("Error on storing data in file node\n");
                                }

                        //THis adds the file to a piece of memory like a pointer (NODES.CPP)
                        } else if(N.FLAG == 2){
                            // Request answered with a failure...
                            // Create new request msg for next node or quit...
                            
                        }    
                    } else {//CONOR HELP WITH DEFS PLEASE HERE :)
                        //#FIXME: DONE
                        int NEXT_PORT = next_hop(N.PORT, PORT, map);
                        //FIND NEXT BEST PLACE TO MOVE ON
                        //IPLOOKPU HERE TOO
                        int index = NEXT_PORT ;//all calculated through routing table
                        char* IP = IP_index[index];
                        printf("Message for %i: Relay to %d\n",N.PORT, NEXT_PORT);

                        ClientCreate(IP,NEXT_PORT,buff);//send it to this address and next port.
                    }//
                    close(i);
                    FD_CLR(i, &active);
                }
            }
        }

        if (k == (FD_SETSIZE * 2))
            break;
    }
    return;
}

//Send back (FILE SEG NUM ,Sendindging port , //IP )
//find it in nugget make = to char pointer
int SendBack(int segnumber,int port, char* IP ,int fileid, char * msg){
// char* msg =  nuggetcollector(fileid,seg);
//ADD FIND THE SEGMENT FUNCTION HERE
    if (root == NULL) {//no files available
        printf("ERROR! There is no file.");
        return 0;
    } else {
        msg = search_seg(root, fileid, segnumber);//search for file segment by ID, return message
        if(msg == NULL){//specific file segment not available
            return 0;
        }
        else{
            ClientCreate(IP,port, msg);
            return 1;
        }
    }
}

////////////Client Functions://///////////////////////////////////////////////////////////////

int ClientCreate(char* IP,int PORT_server,char *buffer)
{
    printf("In CLIENT\n");
    PORT_server = PORT_server + IPSTART;
    int Csockfd =99;//SOCKET FILE DESCRIPTOR returns -1 on errno
    struct sockaddr_in Chints;// was using the addrinfo but doesnt work for single networking..
    char s[INET6_ADDRSTRLEN];//have it as length ipv6 incase good practise
    int yes =99;//DEFINING RANDOM NUMBERS
	int rv = 99,rz =99;

    int sock = 0, valread;
    struct sockaddr_in serv_addr;
    char hello[1024] = {0};
    //  memset(&Chints, 0, sizeof Chints);//resets the struct so its not holding any memory.. 
    Chints.sin_family = AF_INET;//Sets this to IPV4
    Chints.sin_port = htons(PORT_server);//COnverts to big endian format.. Good practice
    // = SOCK_STREAM;//TCP
    ///IRL MODE(UNCOMMENT FOR REAL TESTS)
    // Chints.sin_addr.s_addr = inet_addr(IP);//Change here - inaddr_any 
    // memset(Chints.sin_zero, '\0', sizeof Chints.sin_zero); //OLD APPROACH
 
    //////////SIM Mode....
    Chints.sin_addr.s_addr = INADDR_ANY;


    //create a socket from the info found 
    if( (Csockfd = socket(AF_INET,SOCK_STREAM,0))<0){ //Lets you choose TCP||UDP STREAM||DATAGRAM AI_INET||AI_INET6(Ip_addresse types..)
        fprintf(stderr,"ERROR Client getting socket: %s\n",gai_strerror(Csockfd));
        return 1;//returning one as error check i
    }

///////////////////IRL MODE UNCOMMENT FOR PIS/////////////////////////


//Try bind instead of connect
// bind(Csockfd, (struct sockaddr *)&Chints, sizeof Chints);
// int force =1;
//  if (setsockopt(Csockfd, SOL_SOCKET,SO_REUSEADDR, &force, sizeof(force)))//FORCES THIS SOCKET FD TO THE PORT
//     {
//         perror("setsockopt");
//         exit(EXIT_FAILURE);
//     }



///////////////////////////////////////////

    //////////SIM MODE///////-------------------
    int force = 1;

    if (setsockopt(Csockfd, SOL_SOCKET,SO_REUSEADDR, &force, sizeof(force)))//FORCES THIS SOCKET FileDESC TO THE PORT
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }



//////////////////////////////////////////////////////////
    if (connect(Csockfd, (struct sockaddr *)&Chints,sizeof Chints) == -1) {//connecting
            close(Csockfd);
            perror("ERROR client: connect");
			return 1;
    }   
    printf("CLIENT FINE\n");
    //TODO: Remove this later just for DEBUGging
    // inet_ntop(Cres->ai_family, get_in_addr((struct sockaddr *)Cres->ai_addr),
    //             s, sizeof s);
    printf("client: connecting to %s\n", s);

    unsigned long ha =(MAX);

    	int n;
        char msg[2000] = {0};
        char X[1024] = {0};

	
    printf("Sending message:%s\n",buffer);
   
    //process_buffer(buffer, MAX);//adds the \0 instaed of \n 
    sprintf(msg, "%s",buffer); // format of data not entirely nesicary if we have enough spac in first array
    //Basically puts the string csv into this message and adds a \0 to make sure it sends correct.
    // this gets sent to the buffer

    send(Csockfd, msg, sizeof(msg), 0); // send to the created socket
    printf("\nMessage sent\n\n\n");

	// close the socket
	close(Csockfd);
    return 0;   
	
}
//NOTE SHOULD PASS IN NODE ADDRESSLIST
void FileDistro(dataset * file, int address, node * node_list, int * map){
    //Generates the list of files and sends them
    //#FIXME:   
    //STEP 1 SPLITTING SEGMENT
    // STEP 2 IS ROUTING THE SEGMENT FINDING WHERE TO SEND IT FIRST
    //STEP 3 SEND THE PACKETS TO WHATEVER ROUTE FOUND BEST.        
    int seg = 100;
    int num_of_segs = 10;
    int seg_size = (file->char_count)/num_of_segs;
    int index = 0;
    
    printf("Init FileDistro\n");
    
    for(int i=0; i<num_of_segs; i++){
        // share multiple copies of each seg, for redundancy
        // get a list of DEST nodes...
        int * dest_port = rendezvous(file->id, seg, node_list, address);
        printf("\nFile: %i\n Seg: %i\n\n", file->id, seg);
        for (int i=0; i<REDUNDANCY; i++){
            char * message = (char*)malloc(MX_STR_LEN * sizeof(char));
            printf("Destination: %i\n", dest_port[i]);
            message = N1.share_file(file, seg, seg_size, index, dest_port[i]);
            //that makes string into segments and assigns the segments to portn numbers in the form "111.5345."ARG""
            printf("Finished assembling segment %i.\n", seg);
            printf("%s\n\n", message);
            //int DEST_PORT = PortParser(message); 
            // get the next hop;
            int NEXT = next_hop(dest_port[i], address, map);
            // func -> find IP
            //IP LOOKUP TODO
            printf("Next = %d\n",NEXT);
            int index = NEXT - IPSTART;
            char* IP = IP_index[index];
            printf("Send seg %i to port %i\n\n", seg, NEXT);
            ClientCreate(IP,NEXT,message);
            free(message);
        }
        index = index + seg_size;
        seg++;
    }
    return;
}

NodeInfo PortParser(char* buff){
    printf("Getting Port Info\n");
    NodeInfo N;
    char * copy = (char*)malloc(MX_STR_LEN * sizeof(char));
    strcpy(copy, buff);
    char * parse = (char*)malloc(MX_STR_LEN * sizeof(char));
    int count =0;
    parse = strtok(copy, "-");
    while (count <5){

        printf ("%s\n",parse);
        parse = strtok (NULL, "-");
        if(0 ==count){
        //Add specific sections lookinto 
        strcpy(parse,N.IP);
        }
        if(1 ==count){
        N.PORT = atoi(parse);
        }
        if(2 ==count){
        N.FLAG = atoi(parse);
        }
        if(3 ==count){
        N.FILEID = atoi(parse);
        }
        if(4 ==count){
        N.SEGNUM = atoi(parse);
            printf("Problem here");
        }
        if(5 == count){
            strcpy(buff,N.MSG);
        }
        count++;
  }
  free(copy);
  free(parse);//This might cause problems
    //FREE PARSE TEST IN TSTING)
  return N;
}