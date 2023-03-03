#include <stdio.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h> // read(), write(), close()
#include <arpa/inet.h> // inet_addr()
#include <strings.h> // bzero()
#include <sys/socket.h>
#include <unistd.h> // read(), write(), close()
#include <pthread.h>

#include "Node/Node.h"

#define MAX 80
#define PORT 8080
#define SA struct sockaddr

void* Server(void* a){
    int err =0;
    int sockfd, connfd, len;
	struct sockaddr_in servaddr, cli;
    // errn =ServerCreate();
    err = ServerConstruct(&sockfd, &connfd , &len, servaddr ,cli);
    if(err==0){
        printf("Server Error on Construction Stage Terminating.");
        exit(0);
    }
	// inf. loop 
    while(1){
        // int client = accept(Server.socket)

    }
}
void* Client(void* b){

}

int main(int argc, char *argv[]){
	Node node;
	if(!node.init_node(*argv)){
		printf("Err in init node (port id: %i)\n", argv[1]);
	}



static pthread_t client,server;
	long rc;

printf("Server Creating\n");
 	rc = pthread_create(&server,NULL,Server,(void *)0);
	if (rc) {
			printf("@P-ERROR %ld\n",rc);
			exit(-1);
		}
  printf("Client Creating\n");
 	rc = pthread_create(&client,NULL,Client,(void *)0);
	if (rc) {
			printf("@C-ERROR %ld\n",rc);
			exit(-1);
		}

    return 0;
}

int ServerConstruct(int* sockfd,int* connfd,int* len, sockaddr_in servaddr,sockaddr_in cli){


	// socket create and verification
	*(sockfd) = socket(AF_INET, SOCK_STREAM, 0);
	if (*(sockfd) == -1) {
		printf("socket creation failed...\n");
		return(0);
	}
	else
		printf("Socket successfully created..\n");
	bzero(&servaddr, sizeof(servaddr));

	// assign IP, PORT
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(PORT);

// Binding newly created socket to given IP and verification
	if ((bind((*sockfd), (SA*)&servaddr, sizeof(servaddr))) != 0) {
		printf("socket bind failed...\n");
		return 0;
	}
	else
		printf("Socket successfully binded..\n");

        

return 1;

}