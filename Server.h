#ifndef Server_h
#define Server_h


//SFUNCTIONS
int Server();
int ListenA();


//TODO REMOVE || MODIFY HEAVILY
// void *get_in_addr(struct sockaddr *sa); Defined in Client already
void Recieve(Node X,edge ** e_list, node * n_list );  // Simple chat program which generates a string and sends it.


#endif  