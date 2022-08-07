#include <string.h>
#include <sys/socket.h> 
#include <unistd.h> 
#include <arpa/inet.h> 
#include <stdio.h>
#include <stdlib.h> 
	 
#define PORT 8000  //TCP port 

#include "structures.h"
#include "server_connect.h"
#include "menu_client.h"
#include "train_client.h"
#include "user_client.h"
#include "user_fun_client.h"


int main(void) { 
	int sock; 
    	struct sockaddr_in server; 
    	char server_reply[50],*server_ip;
	server_ip = "127.0.0.1"; 
     
    	sock = socket(AF_INET, SOCK_STREAM, 0); //Create a new socket with domain, type and protocol SOCK_STREAM -> TCP, 0->IP;
    	if (sock == -1) { 
       	printf("Could not create socket"); 
    	} 
    
    	server.sin_addr.s_addr = inet_addr(server_ip); 
    	server.sin_family = AF_INET;           //IPv4
    	server.sin_port = htons(PORT); 
   
    	if (connect(sock, (struct sockaddr*)&server, sizeof(server)) < 0) //Connnect sock with server, server addresss
       	perror("Connect failed. Error"); 
    
	while(client(sock)!=3);
    	close(sock);  //Close connection on exit
    	
	return 0; 
} 
