#include "Client.h"
#include "Server.h"
#include "PublicDef.h"
#include <pthread.h>
// TODO: make a thread for server run and call variables.
//TODO: Look into Gloabalisation and resetting variables (might be easier to just use sep var names and reuse the struscts)
 
//TODO: Clean up variables and get it to run...
//TODO: Look at cmd line 
//TODO URGENT  make a way of chosing which port number for multiple hosts...
pthread_mutex_t mutex;
int err=0;
void *ServerT(void* a){
    err = CreateServer();
    if(err != 0 ){
        printf("Error on INIT Server see errors:\n");
    }
    err = ListenA();
     if(err != 0 ){
        printf("Error on Listening Server see errors:\n");
    }
    else 
    printf("all is well! :))\n");
    return 0;

}


int main(int argc, char const *argv[]){

     printf("Enter name:");
    scanf("%s", usrname);

    printf("Enter your port number:");
    scanf("%d", &PORT);

pthread_mutex_init(&mutex,NULL);
static pthread_t Serv;
int fail;
long xy;
xy = pthread_create(&Serv,NULL,ServerT,(void *)0);
if(xy){
    printf("@Thread ERROR\n");
    exit(-1);
}
pthread_join(Serv,NULL);
//While that thread is runnign the client will take center stage...

fail = ClientCreate();
if(fail != 0 ){
        printf("Error on Client End see errors:\n");
    }
else 
printf("Ended fairly in love and war :)!\n");


pthread_mutex_destroy(&mutex);
    return 0;

}



//////////////////////////////////////////////////
///SERVER FUNCTIONS/////////////////////////




int CreateServer()
{
 
    // struct sigaction sa;
    // int yes=1;
    // int rv1;

    memset(&hints, 0, sizeof hints);//resets the struct so its not holding any memory.. 
    hints.ai_family = AF_UNSPEC;//Unknown IP IF ITS V4 OR V6
    hints.ai_socktype = SOCK_STREAM;//TCP
    hints.ai_flags = AI_PASSIVE; // use my IP
    hints.ai_addr = INADDR_ANY;
    if ((rz = getaddrinfo(NULL, PORT, &hints, &res)) != 0) {// error handling 
        fprintf(stderr, "init Function get addrinfo: %s\n", gai_strerror(rv));
        return 1;
    }

   // TODO://
//SIMPLE VERSION WILL NEED TO BE CHANGED DOWN THE LINE..
   if( sockfd = socket(res->ai_family,res->ai_socktype,res->ai_protocol)!=0){ //Lets you choose TCP||UDP STREAM||DATAGRAM AI_INET||AI_INET6(Ip_addresse types..)
        fprintf(stderr,"INIT_Server getting socket: %s\n",gai_strerror(sockfd));
        return 1;//returning one as error check in main..
   }
   //Since we will be listening down the line we must bind the socket and the address...

   if( bind(sockfd, res->ai_addr,res->ai_addrlen)!=0)//binds to the port we gave it to at the start.
    {
        printf("INIT_Server socket bind failed...\n");
        return 1;
    }
return 0;
}

int ListenA(){

    if(listen(sockfd,BACKLOG)!=0)
    {
        printf("INIT_Server socket Listening failed...\n");
        return 1;
    }
    printf("Listening...\n");
    //accept time how it works is somewhere will try to call coonect()
    //to the port im listening on..
    // Their connection will be queued waiting to be accepted()
    // you call accept tell it to get the pending connection
    // IT WILL RETURN A NEW SOCKFD FOR THIS CONNECTIONTHE FIRST SOCKFD IS STILL LISTENING FOR NEWCOMERS
    // BUT THE NEW ONE HANDLES SOLELY THE BACK AND FORTH WITH THIS CONN
while(1){
    addr_size = sizeof their_addr;
    if(talkfd = accept(sockfd, (struct sockaddr *)&their_addr, &addr_size)<0){//errno -1 for socket err will cal that variable gloabaly
      printf("INIT_Server Accept failed...\n");
        continue;
    }
    printf("Connected to a client\n");
    // inet_ntop(their_addr.ss_family,
            // get_in_addr((struct sockaddr *)&their_addr),//this function gets the address of the device connecting
            // s, sizeof s);
        // printf("server: got connection from %s\n", s);

Recieve(talkfd);
close(sockfd);// Command exits as connection is finished..
    //TODO//
    // simple messaging for DEV Please remove afterusage....
}
return 0; // all ran smoothly server is going to sleep
}

void *get_in_addr(struct sockaddr *sa)
{
    if (sa->sa_family == AF_INET) {
        return &(((struct sockaddr_in*)sa)->sin_addr);
    }

    return &(((struct sockaddr_in6*)sa)->sin6_addr);
}


void Recieve(int connfd)// delete after usage..
{
    char buff[MAX];
    int n;
    // infinite loop for chat
    for (;;) {
        bzero(buff, MAX);
   
        // read the message from client and copy it in buffer
        read(connfd, buff, sizeof(buff));
        // print buffer which contains the client contents
        printf("From client: %s\n: ", buff);
        bzero(buff, MAX);
        n = 0;
        // copy server message in the buffer
        while ((buff[n++] = getchar()) != '\n')
            ;
   
        // and send that buffer to client
   
        // if msg contains "Exit" then server exit and chat ended.
        if (strncmp("exit", buff, 4) == 0) {
            printf("Server Exit...\n");
            break;
        }
    }
}

////////////////////////////////////////////////////////////////////////////
///////////////////////////////////CLIENT FUNCTIONS/////////////////////////
#include"Client.h"
#include "PublicDef.h"

//REMOVE SOON....

// void *get_in_addr(struct sockaddr *sa)
// {
//     if (sa->sa_family == AF_INET) {
//         return &(((struct sockaddr_in*)sa)->sin_addr);
//     }

//     return &(((struct sockaddr_in6*)sa)->sin6_addr);
// }
void Send(int sockfd)// Simple chat program which generates a string and sends it.
{
	char buff[MAX];
	int n;
	for (;;) {
		bzero(buff, sizeof(buff));
		printf("Enter the string : ");
		n = 0;
		while ((buff[n++] = getchar()) != '\n')
			;
		write(Csockfd, buff, sizeof(buff));
		bzero(buff, sizeof(buff));
		if ((strncmp(buff, "exit", 4)) == 0) {
			printf("Client Exit...\n");
			break;
		}
	}
}

int ClientCreate()
{

 memset(&Chints, 0, sizeof Chints);//resets the struct so its not holding any memory.. 
    Chints.ai_family = AF_UNSPEC;//Unknown IP IF ITS V4 OR V6
    Chints.ai_socktype = SOCK_STREAM;//TCP
    Chints.ai_flags = AI_PASSIVE; // use my IP


 if ((rv = getaddrinfo(NULL, PORT, &Chints, &Cres)) != 0) {// error handling 
        fprintf(stderr, "init CLIENT get addrinfo: %s\n", gai_strerror(rv));
        return 1;
    }

//create a socket from the info found 
if( Csockfd = socket(Cres->ai_family,Cres->ai_socktype,Cres->ai_protocol)!=0){ //Lets you choose TCP||UDP STREAM||DATAGRAM AI_INET||AI_INET6(Ip_addresse types..)
        fprintf(stderr,"ERROR Client getting socket: %s\n",gai_strerror(Csockfd));
        return 1;//returning one as error check in main..
   }


if (connect(Csockfd, Cres->ai_addr, Cres->ai_addrlen) == -1) {
            close(Csockfd);
            perror("ERROR client: connect");
			return 1;
}

//TODO: Remove this later just for DEBUGging
inet_ntop(Cres->ai_family, get_in_addr((struct sockaddr *)Cres->ai_addr),
            s, sizeof s);
    printf("client: connecting to %s\n", s);


	Send(Csockfd);

	// close the socket
	close(Csockfd);
	return 0;
}
