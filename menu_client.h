int menu(int sock,int type){
	int choice;
	if(type==2 || type==1){					
		printf("\t1) Book Ticket\n");
		printf("\t2) View Bookings\n");
		printf("\t3) Update Booking\n");
		printf("\t4) Cancel booking\n");
		printf("\t5) Logout\n");
		printf("\tYour Choice: ");
		scanf("%d",&choice);
		write(sock,&choice,sizeof(choice));
		return user_function(sock,choice);
	}
	else if(type==0){					
		printf("\n\t1) TRAIN OPERATIONS\n");
		printf("\t2) USER OPERATIONS\n");
		printf("\t3) LOGOUT\n");
		printf("\t CHOICE: ");
		scanf("%d",&choice);
		write(sock,&choice,sizeof(choice));
			if(choice==1){
				printf("\t1) ADD TRAIN\n");
				printf("\t2) VIEW TRAIN\n");
				printf("\t3) MODIFY TRAIN\n");
				printf("\t4) DELETE TRAIN\n");
				printf("\t CHOICE: ");
				scanf("%d",&choice);	
				write(sock,&choice,sizeof(choice));
				return crud_train(sock,choice);
			}
			else if(choice==2){
				printf("\t1) ADD USER\n");
				printf("\t2) VIEW ALL USERS\n");
				printf("\t3) MODIFY USER\n");
				printf("\t4) DELETE USER\n");
				printf("\t5) VIEW BOOKINGS\n");
				printf("\t CHOICE: ");
				scanf("%d",&choice);
				write(sock,&choice,sizeof(choice));
				return crud_user(sock,choice);
			
			}
			else if(choice==3)
				return -1;
	}	
	
}
