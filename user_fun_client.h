int user_function(int sock,int choice){
	int valid =0;
	if(choice==1){										
		int view=2,tid,seats;
		write(sock,&view,sizeof(int));
		crud_train(sock,view);
		printf("\n\tEnter the train number you want to book: ");
		scanf("%d",&tid);
		write(sock,&tid,sizeof(tid));
				
		printf("\n\tEnter the number of seats you want to book: ");
		scanf("%d",&seats);
		write(sock,&seats,sizeof(seats));
	
		read(sock,&valid,sizeof(valid));
		if(valid)
			printf("\n\tTicket booked successfully\n");
		else
			printf("\n\tSeats were not available\n");

		return valid;
	}
	
	else if(choice==2){									
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

	else if(choice==3){									
		int choice = 2,bid,val,valid;
		user_function(sock,choice);
		printf("\n\t Enter the id you want to modify: ");
		scanf("%d",&bid);
		write(sock,&bid,sizeof(bid));

		printf("\n\t1) Increase seats\n\t2) Decrease seats\n");
		printf("\t Your Choice: ");
		scanf("%d",&choice);
		write(sock,&choice,sizeof(choice));

		if(choice==1){
			printf("\n\tNumber of tickets to increase");
			scanf("%d",&val);
			write(sock,&val,sizeof(val));
		}
		else if(choice==2){
			printf("\n\tNumber of tickets to decrease");
			scanf("%d",&val);
			write(sock,&val,sizeof(val));
		}
		read(sock,&valid,sizeof(valid));
		if(valid)
			printf("\n\tBooking updated successfully\n");
		else
			printf("\n\t No more seats available\n");
		return valid;
	}
	
	else if(choice==4){									
		int choice = 2,bid,valid;
		user_function(sock,choice);
		printf("\n\t Enter the id you want to cancel: ");
		scanf("%d",&bid);
		write(sock,&bid,sizeof(bid));
		read(sock,&valid,sizeof(valid));
		if(valid)
			printf("\n\tBooking cancelled successfully.\n");
		else
			printf("\n\tCancellation failed.\n");
		return valid;
	}
	else if(choice==5)									
		return -1;
	
}
