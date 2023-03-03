#include "Client.h"
#include "Server.h"
#include "PublicDef.h"
#include <pthread.h>
// TODO: make a thread for server run and call variables.
//TODO: Look into Gloabalisation and resetting variables (might be easier to just use sep var names and reuse the struscts)
 
//TODO: Clean up variables and get it to run...
//TODO: Look at cmd line 
//TODO URGENT  make a way of chosing which port number for multiple hosts...
void process_buffer(char *buffer, int max_len)
{//ADDS NULL TO END OF STRING 
    for (int i = 0; i < max_len; i++)
    {
        if ((buffer[i] == '\n') || (buffer[i] == '\r'))
        {
            buffer[i] = '\0';
            break;
        }
    }
}
pthread_mutex_t mutex;
int err=0;
void *ServerT(void* a){
   
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
    Recieve();//ATM NO NEED TO CALL ANYTHING BECAUSE WE USE GLOBAL VAR RN
// Command exits as connection is finished..
    //TODO simple messaging for DEV Please remove afterusage....
}

    printf("all is well! :))\n");
    return 0;
    

}


int main(int argc, char const *argv[]){


///////////////////////////////////////////////////////////////// 
//Server Section:
//////////////////////////////////////////////////////////////////
pthread_mutex_init(&mutex,NULL);
static pthread_t Serv;
int fail;
long xy;
 err =Server();
    if(err != 0 ){
        printf("Error on INIT Server see errors:\n");
        return 0;
    } 
    
xy = pthread_create(&Serv,NULL,ServerT,(void *)0);
if(xy){
    printf("@Thread ERROR\n");
    exit(-1);
}
int ch; 

printf("\nPlease Select the following options: >>>\n1.Publish File\n0.Quit\n Or ..Wait\n");
    printf("\nEnter choice:");

    do
    {
        scanf("%d", &ch);
        switch (ch)
        {
        case 1:
            ClientCreate();
            break;
        case 0:
            printf("\nLeaving\n");
            break;
        default:
            printf("\nWrong choice\n");
        }
    } while (ch);
pthread_join(Serv,NULL);

pthread_mutex_destroy(&mutex);
    return 0;

}

int Server()
{
    // int sockfd , talkfd ;//SOCKET FILE DESCRIPTOR returns -1 on errno
    // struct sockaddr_in hints;
    // struct sockaddr_storage their_addr;
    // socklen_t addr_size;

    int force =1;
   printf("Enter name:");
    scanf("%s", usrname);

    printf("Enter your port number:");
    scanf("%d", &PORT);
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




void Recieve()// delete after usage..
{
    
    fd_set active, read;
    addr_size=sizeof(their_addr);
    // Initialize my current set
    FD_ZERO(&active);
    FD_SET(sockfd, &active);
    int k=0;
    int n;
            char buff[MAX]={0};

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
                    FD_SET(client_socket, &active);
                }
                else
                {
                    int rec_PORT = 0;
                    //data is arriving on an already connected socket
                    n = recv(i, buff, sizeof(buff), 0);
                    //Take
                    //Recieved buffer and parse first part;
                    if(REC_PORT == PORT)//Meant to be here 
                    {
                        add_file();
                    }
                    else
                    {
                        int NEXT_PORT = 0;
                        NEXT_PORT = ShortestPath(REC_PORT); //FIND NEXT BEST PLACE TO MOVE ON
                        ClientCreate(NEXT_PORT,buff);//send it to this address and next port.
                    }
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

////////////Client Functions://///////////////////////////////////////////////////////////////

int ClientCreate()
{


    char buffer[2000] = {0};
    // Fetching port number
    int PORT_server;

    // IN PEER WE TRUST
    printf("Enter the port to send message:"); // Considering each peer will enter different port
    scanf("%d", &PORT_server);

    int sock = 0, valread;
    struct sockaddr_in serv_addr;
    char hello[1024] = {0};
//  memset(&Chints, 0, sizeof Chints);//resets the struct so its not holding any memory.. 
    Chints.sin_family = AF_INET;//Sets this to IPV4
    // = SOCK_STREAM;//TCP
    Chints.sin_port = htons(PORT_server);//COnverts to big endian format.. Good practice
    Chints.sin_addr.s_addr = INADDR_ANY;

 

//create a socket from the info found 
if( (Csockfd = socket(AF_INET,SOCK_STREAM,0))<0){ //Lets you choose TCP||UDP STREAM||DATAGRAM AI_INET||AI_INET6(Ip_addresse types..)
        fprintf(stderr,"ERROR Client getting socket: %s\n",gai_strerror(Csockfd));
        return 1;//returning one as error check in main..
   }
int force =1;
 if (setsockopt(Csockfd, SOL_SOCKET,SO_REUSEADDR, &force, sizeof(force)))//FORCES THIS SOCKET FD TO THE PORT
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

if (connect(Csockfd, (struct sockaddr *)&Chints,sizeof Chints) == -1) {
            close(Csockfd);
            perror("ERROR client: connect");
			return 1;
}

//TODO: Remove this later just for DEBUGging
// inet_ntop(Cres->ai_family, get_in_addr((struct sockaddr *)Cres->ai_addr),
//             s, sizeof s);
    printf("client: connecting to %s\n", s);

unsigned long ha =(MAX);

    	int n;
        char msg[2000] = {0};
        char X[1024] = {0};

	// 	char* name =(char*)malloc(sizeof(20));
    // 	printf("Enter the string : \n");
     char dummy;//dummy to enable terminal
    printf("Enter your message:");
    scanf("%c", &dummy); // a single newline character is kept from when the port number was read
   
    fgets(X, 1024, stdin);
    process_buffer(X, 1024);
    sprintf(msg, "[PORT:%d] says: %s", PORT, X); // format of data sent
    // this gets sent to the buffer

    send(Csockfd, msg, sizeof(buffer), 0); // send to the created socket
    printf("\nMessage sent\n");
	

	// close the socket
	close(Csockfd);



 return 0;   
	

	// close the socket
	close(Csockfd);
	return 0;
}
