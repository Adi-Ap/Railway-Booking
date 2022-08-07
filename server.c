#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdio.h> 
#include <stdlib.h> 
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "structures.h"
#include "client_connect.h"
#include "login.h"
#include "menu.h"
#include "train.h"
#include "user.h"
#include "user_fun.h"


#define PORT 8000

int main(void) {
 
    int socket_desc, client_sock, c; 
    struct sockaddr_in server, client; 
    char buf[100]; 
  
    socket_desc = socket(AF_INET, SOCK_STREAM, 0); //Create Socket
    if (socket_desc == -1) { 
        printf("Could not create socket"); 
    } 
  
    server.sin_family = AF_INET; 
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(PORT); 
   
    if (bind(socket_desc, (struct sockaddr*)&server, sizeof(server)) < 0) //Bind the socket with the address
        perror("bind failed. Error"); 
   
 
    listen(socket_desc, 3);  //Listen and wait for connection, Queue size is 3;
    c = sizeof(struct sockaddr_in); 
    printf("Server ON");
  
    while (1){

	    client_sock = accept(socket_desc, (struct sockaddr*)&client, (socklen_t*)&c); //Accept the request form client
	  
	    if (!fork()){
		    close(socket_desc);
		    service_cli(client_sock);								
		    exit(0);
	    }
	    else
	    	close(client_sock);
    }
    printf("Server OFF");
    return 0;
}
