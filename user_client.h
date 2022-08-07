int crud_user(int sock,int choice){
	int valid = 0;
	if(choice==1){							
		int type,id;
		char name[50],password[50];
		printf("\n\tEnter The Type Of Account:: \n");
		printf("\t1) Agent\n\t2) Customer\n");
		printf("\tYour Response: ");
		scanf("%d", &type);
		printf("\tUser Name: ");
		scanf("%s", name);
		strcpy(password,getpass("\tPassword: "));
		write(sock, &type, sizeof(type));
		write(sock, &name, sizeof(name));
		write(sock, &password, strlen(password));
		read(sock,&valid,sizeof(valid));	
		if(valid){
			read(sock,&id,sizeof(id));
			printf("\tLogin ID is: %d\n", id);
		}
		return valid;	
	}
	
	else if(choice==2){						
		int no_of_users;
		int id,type;
		char uname[50];
		read(sock,&no_of_users,sizeof(no_of_users));

		printf("\tUser ID\tUser name\tType\n");
		while(no_of_users--){
			read(sock,&id,sizeof(id));
			read(sock,&uname,sizeof(uname));
			read(sock,&type,sizeof(type));
			
			if(strcmp(uname, "deleted")!=0)
				printf("\t%d\t%s\t%d\n",id,uname,type);
		}

		return valid;	
	}

	else if (choice==3){						
		int choice=2,valid=0,uid;
		char name[50],pass[50];
		write(sock,&choice,sizeof(int));
		crud_user(sock,choice);
		printf("\n\t Enter the ID to modify: ");
		scanf("%d",&uid);
		write(sock,&uid,sizeof(uid));
		
		printf("\n\t1) User Name\n\t2) Password\n");
		printf("\t Your Choice: ");
		scanf("%d",&choice);
		write(sock,&choice,sizeof(choice));
		
		if(choice==1){
			read(sock,&name,sizeof(name));
			printf("\n\t Current name: %s",name);
			printf("\n\t Updated name:");
			scanf("%s",name);
			write(sock,&name,sizeof(name));
			read(sock,&valid,sizeof(valid));
		}
		else if(choice==2){
			printf("\n\t Enter Current password: ");
			scanf("%s",pass);
			write(sock,&pass,sizeof(pass));
			read(sock,&valid,sizeof(valid));
			if(valid){
				printf("\n\t Enter new password:");
				scanf("%s",pass);
			}
			else
				printf("\n\tIncorrect password\n");
			
			write(sock,&pass,sizeof(pass));
		}
		if(valid){
			read(sock,&valid,sizeof(valid));
			if(valid)
				printf("\n\t User data updated successfully\n");
		}
		return valid;
	}

	else if(choice==4){						
		int choice=2,uid,valid=0;
		write(sock,&choice,sizeof(int));
		crud_user(sock,choice);
		
		printf("\n\t Enter the ID to delete: ");
		scanf("%d",&uid);
		write(sock,&uid,sizeof(uid));
		read(sock,&valid,sizeof(valid));
		if(valid)
			printf("\n\t User deleted successfully\n");
		return valid;
	}
	else if(choice==5){									
		int no_of_bookings;
		int id,tid,seats;
		read(sock,&no_of_bookings,sizeof(no_of_bookings));

		printf("\tBooking id\tTrain\tSeats\n");
		while(no_of_bookings--){
			read(sock,&id,sizeof(id));
			read(sock,&tid,sizeof(tid));
			read(sock,&seats,sizeof(seats));
			
			if(seats!=0)
				printf("\t%d\t%d\t%d\n",id,tid,seats);
		}

		return valid;
	}
}
