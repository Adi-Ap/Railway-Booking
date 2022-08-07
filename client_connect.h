void service_cli(int sock){
	int choice;
	printf("\n\tClient Connected\n");
	do{
		read(sock, &choice, sizeof(int));		
		if(choice==1)
			login(sock);
		if(choice==2)
			signup(sock);
		if(choice==3)
			break;
	}while(1);

	close(sock);
	printf("\n\tClient Disconnected\n");
}

//Run on Server side

