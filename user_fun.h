int user_function(int client_sock,int choice,int type,int id){
	int valid=0;
	if(choice==1){						
		crud_train(client_sock);
		struct flock lockt;
		struct flock lockb;
		struct train tdb;
		struct booking bdb;
		int fd_train = open("db/db_train", O_RDWR);
		int fd_book = open("db/db_booking", O_RDWR);
		int tid,seats;
		read(client_sock,&tid,sizeof(tid));		
				
		lockt.l_type = F_WRLCK;
		lockt.l_start = tid*sizeof(struct train);
		lockt.l_len = sizeof(struct train);
		lockt.l_whence = SEEK_SET;
		lockt.l_pid = getpid();
		
		lockb.l_type = F_WRLCK;
		lockb.l_start = 0;
		lockb.l_len = 0;
		lockb.l_whence = SEEK_END;
		lockb.l_pid = getpid();
		
		fcntl(fd_train, F_SETLKW, &lockt);
		lseek(fd_train,tid*sizeof(struct train),SEEK_SET);
		
		read(fd_train,&tdb,sizeof(tdb));
		read(client_sock,&seats,sizeof(seats));

		if(tdb.train_number==tid)
		{		
			if(tdb.available_seats>=seats){
				valid = 1;
				tdb.available_seats -= seats;
				fcntl(fd_book, F_SETLKW, &lockb);
				int fp = lseek(fd_book, 0, SEEK_END);
				
				if(fp > 0){
					lseek(fd_book, -1*sizeof(struct booking), SEEK_CUR);
					read(fd_book, &bdb, sizeof(struct booking));
					bdb.booking_id++;
				}
				else 
					bdb.booking_id = 0;

				bdb.type = type;
				bdb.uid = id;
				bdb.tid = tid;
				bdb.seats = seats;
				write(fd_book, &bdb, sizeof(struct booking));
				lockb.l_type = F_UNLCK;
				fcntl(fd_book, F_SETLK, &lockb);
			 	close(fd_book);
			}
		
		lseek(fd_train, -1*sizeof(struct train), SEEK_CUR);
		write(fd_train, &tdb, sizeof(tdb));
		}

		lockt.l_type = F_UNLCK;
		fcntl(fd_train, F_SETLK, &lockt);
		close(fd_train);
		write(client_sock,&valid,sizeof(valid));
		return valid;		
	}
	
	else if(choice==2){							
		struct flock lock;
		struct booking bdb;
		int fd_book = open("db/db_booking", O_RDONLY);
		int no_of_bookings = 0;
	
		lock.l_type = F_RDLCK;
		lock.l_start = 0;
		lock.l_len = 0;
		lock.l_whence = SEEK_SET;
		lock.l_pid = getpid();
		
		fcntl(fd_book, F_SETLKW, &lock);
	
		while(read(fd_book,&bdb,sizeof(bdb))){
			if (bdb.uid==id)
				no_of_bookings++;
		}

		write(client_sock, &no_of_bookings, sizeof(int));
		lseek(fd_book,0,SEEK_SET);

		while(read(fd_book,&bdb,sizeof(bdb))){
			if(bdb.uid==id){
				write(client_sock,&bdb.booking_id,sizeof(int));
				write(client_sock,&bdb.tid,sizeof(int));
				write(client_sock,&bdb.seats,sizeof(int));
			}
		}
		lock.l_type = F_UNLCK;
		fcntl(fd_book, F_SETLK, &lock);
		close(fd_book);
		return valid;
	}

	else if (choice==3){							
		int choice = 2,bid,val;
		user_function(client_sock,choice,type,id);
		struct booking bdb;
		struct train tdb;
		struct flock lockb;
		struct flock lockt;
		int fd_book = open("db/db_booking", O_RDWR);
		int fd_train = open("db/db_train", O_RDWR);
		read(client_sock,&bid,sizeof(bid));

		lockb.l_type = F_WRLCK;
		lockb.l_start = bid*sizeof(struct booking);
		lockb.l_len = sizeof(struct booking);
		lockb.l_whence = SEEK_SET;
		lockb.l_pid = getpid();
		
		fcntl(fd_book, F_SETLKW, &lockb);
		lseek(fd_book,bid*sizeof(struct booking),SEEK_SET);
		read(fd_book,&bdb,sizeof(bdb));
		lseek(fd_book,-1*sizeof(struct booking),SEEK_CUR);
		
		lockt.l_type = F_WRLCK;
		lockt.l_start = (bdb.tid)*sizeof(struct train);
		lockt.l_len = sizeof(struct train);
		lockt.l_whence = SEEK_SET;
		lockt.l_pid = getpid();

		fcntl(fd_train, F_SETLKW, &lockt);
		lseek(fd_train,(bdb.tid)*sizeof(struct train),SEEK_SET);
		read(fd_train,&tdb,sizeof(tdb));
		lseek(fd_train,-1*sizeof(struct train),SEEK_CUR);

		read(client_sock,&choice,sizeof(choice));
	
		if(choice==1){							
			read(client_sock,&val,sizeof(val));
			if(tdb.available_seats>=val){
				valid=1;
				tdb.available_seats -= val;
				bdb.seats += val;
			}
		}
		else if(choice==2){						
			valid=1;
			read(client_sock,&val,sizeof(val));
			tdb.available_seats += val;
			bdb.seats -= val;	
		}
		
		write(fd_train,&tdb,sizeof(tdb));
		lockt.l_type = F_UNLCK;
		fcntl(fd_train, F_SETLK, &lockt);
		close(fd_train);
		
		write(fd_book,&bdb,sizeof(bdb));
		lockb.l_type = F_UNLCK;
		fcntl(fd_book, F_SETLK, &lockb);
		close(fd_book);
		
		write(client_sock,&valid,sizeof(valid));
		return valid;
	}
	else if(choice==4){							
		int choice = 2,bid;
		user_function(client_sock,choice,type,id);
		struct booking bdb;
		struct train tdb;
		struct flock lockb;
		struct flock lockt;
		int fd_book = open("db/db_booking", O_RDWR);
		int fd_train = open("db/db_train", O_RDWR);
		read(client_sock,&bid,sizeof(bid));

		lockb.l_type = F_WRLCK;
		lockb.l_start = bid*sizeof(struct booking);
		lockb.l_len = sizeof(struct booking);
		lockb.l_whence = SEEK_SET;
		lockb.l_pid = getpid();
		
		fcntl(fd_book, F_SETLKW, &lockb);
		lseek(fd_book,bid*sizeof(struct booking),SEEK_SET);
		read(fd_book,&bdb,sizeof(bdb));
		lseek(fd_book,-1*sizeof(struct booking),SEEK_CUR);
		
		lockt.l_type = F_WRLCK;
		lockt.l_start = (bdb.tid)*sizeof(struct train);
		lockt.l_len = sizeof(struct train);
		lockt.l_whence = SEEK_SET;
		lockt.l_pid = getpid();

		fcntl(fd_train, F_SETLKW, &lockt);
		lseek(fd_train,(bdb.tid)*sizeof(struct train),SEEK_SET);
		read(fd_train,&tdb,sizeof(tdb));
		lseek(fd_train,-1*sizeof(struct train),SEEK_CUR);

		tdb.available_seats += bdb.seats;
		bdb.seats = 0;
		valid = 1;

		write(fd_train,&tdb,sizeof(tdb));
		lockt.l_type = F_UNLCK;
		fcntl(fd_train, F_SETLK, &lockt);
		close(fd_train);
		
		write(fd_book,&bdb,sizeof(bdb));
		lockb.l_type = F_UNLCK;
		fcntl(fd_book, F_SETLK, &lockb);
		close(fd_book);
		
		write(client_sock,&valid,sizeof(valid));
		return valid;
		
	}
	else if(choice==5)										
		return 5;

}
