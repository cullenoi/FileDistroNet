#include "PublicDef.h"

int main()
{
    int force =1;
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

  if(listen(sockfd,BACKLOG)<0)//-1 = errno
    {
        printf("INIT_Server socket Listening failed...\n");
        return 0;
    }
    printf("Listening...\n");


        //TODO FIX THIS THINGY
    while(1){
        int confd,i;
			int ret=0;
			char ip[17];
			char filename[30];
    addr_size = sizeof their_addr;
    if(talkfd = accept(sockfd, (struct sockaddr *)&their_addr, &addr_size)<0){//errno -1 for socket err will cal that variable gloabaly
      printf("INIT_Server Accept failed...\n");
        continue;
    }
    printf("Connected to a client\n");
    
        char buff[MAX];
 printf("in loop\n");
int n=0;
int len;
 len = strlen(buff);
        // read the message from client and copy it in buffer
      if((n= recv(talkfd, (void*)buff, len, 0))==-1){
        printf("ERROR HERE in RECIEVING THE FUCKING FILE\n");\
      }
                   printf("\n%s\n", buff);
        // print buffer which contains the client contents
        printf("From client: %s\t\n", buff);
      
   }   



close(talkfd);// Command exits as connection is finished..
    //TODO simple messaging for DEV Please remove afterusage....

return 0;
}