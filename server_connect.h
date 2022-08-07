//Run on Client side

int client(int sock){
	int choice,valid;
	//system("clear");
	printf("\n\n\t\t\tTRAIN TICKET SYSTEM\n\n");
	printf("\t1) SIGN IN\n");
	printf("\t2) SIGN UP\n");
	printf("\t3) EXIT\n");
	printf("\tEnter Your Choice:: ");
	scanf("%d", &choice);
	write(sock, &choice, sizeof(choice));
	if (choice == 1){					
		int id,type;
		char password[50];
		printf("\tLogin ID: ");
		scanf("%d", &id);
		strcpy(password,getpass("\t Password:: "));
		write(sock, &id, sizeof(id));
		write(sock, &password, sizeof(password));
		read(sock, &valid, sizeof(valid));
		if(valid){
			printf("\tlogin successfully\n");
			read(sock,&type,sizeof(type));
			while(menu(sock,type)!=-1);
			//system("clear");
			return 1;
		}
		else{
			printf("\tLOGIN FAILED : Incorrect password or login id\n");
			return 1;
		}
	}

	else if(choice == 2){					
		int type,id;
		char name[50],password[50],secret_pin[6];
		system("clear");
		printf("\n\tEnter The Type Of Account:: \n");
		printf("\t0) Admin\n\t1) Agent\n\t2) Customer\n");
		printf("\tYour Response: ");
		scanf("%d", &type);
		printf("\tEnter Your Name: ");
		scanf("%s", name);
		strcpy(password,getpass("\tPassword: "));

		if(!type){
			while(1){
				strcpy(secret_pin, getpass("\tENTER KEY: "));
				if(strcmp(secret_pin, "secret")!=0) 					
					printf("\tInvalid PIN. Please Try Again.\n");
				else
					break;
			}
		}

		write(sock, &type, sizeof(type));
		write(sock, &name, sizeof(name));
		write(sock, &password, strlen(password));
		
		read(sock, &id, sizeof(id));
		printf("\tLOGIN ID : %d\n", id);
		return 2;
	}
	else							
		return 3;
	
}
