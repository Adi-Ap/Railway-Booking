void login(int client_sock){
	int fd_user = open("db/db_user",O_RDWR);
	int id,type,valid=0,user_valid=0;
	char password[50];
	struct user u;
	read(client_sock,&id,sizeof(id));
	read(client_sock,&password,sizeof(password));
	
	struct flock lock;
	
	lock.l_start = (id-1)*sizeof(struct user);
	lock.l_len = sizeof(struct user);
	lock.l_whence = SEEK_SET;
	lock.l_pid = getpid();

	lock.l_type = F_WRLCK;
	fcntl(fd_user,F_SETLKW, &lock);
	
	while(read(fd_user,&u,sizeof(u))){
		if(u.login_id==id){
			user_valid=1;
			if(!strcmp(u.password,password)){
				valid = 1;
				type = u.type;
				break;
			}
			else{
				valid = 0;
				break;
			}	
		}		
		else{
			user_valid = 0;
			valid=0;
		}
	}
	
	
	if(type!=2){
		lock.l_type = F_UNLCK;
		fcntl(fd_user, F_SETLK, &lock);
		close(fd_user);
	}
	
	
	if(user_valid)
	{
		write(client_sock,&valid,sizeof(valid));
		if(valid){
			write(client_sock,&type,sizeof(type));
			while(menu(client_sock,type,id)!=-1);
		}
	}
	else
		write(client_sock,&valid,sizeof(valid));
	
	
	if(type==2){
		lock.l_type = F_UNLCK;
		fcntl(fd_user, F_SETLK, &lock);
		close(fd_user);
	}
} 



void signup(int client_sock){
	int fd_user = open("db/db_user",O_RDWR);
	int type,id=0;
	char name[50],password[50];
	struct user u,temp;

	read(client_sock, &type, sizeof(type));
	read(client_sock, &name, sizeof(name));
	read(client_sock, &password, sizeof(password));

	int fp = lseek(fd_user, 0, SEEK_END);

	struct flock lock;
	lock.l_type = F_WRLCK;
	lock.l_start = fp;
	lock.l_len = 0;
	lock.l_whence = SEEK_SET;
	lock.l_pid = getpid();


	fcntl(fd_user,F_SETLKW, &lock);

	if(fp==0){
		u.login_id = 1;
		strcpy(u.name, name);
		strcpy(u.password, password);
		u.type=type;
		write(fd_user, &u, sizeof(u));
		write(client_sock, &u.login_id, sizeof(u.login_id));
	}
	else{
		fp = lseek(fd_user, -1 * sizeof(struct user), SEEK_END);
		read(fd_user, &u, sizeof(u));
		u.login_id++;
		strcpy(u.name, name);
		strcpy(u.password, password);
		u.type=type;
		write(fd_user, &u, sizeof(u));
		write(client_sock, &u.login_id, sizeof(u.login_id));
	}
	lock.l_type = F_UNLCK;
	fcntl(fd_user, F_SETLK, &lock);

	close(fd_user);
	
}

