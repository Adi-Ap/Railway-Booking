int menu(int client_sock,int type,int id){
	int choice,ret;


	if(type==0){
		read(client_sock,&choice,sizeof(choice));
		if(choice==1){					
			crud_train(client_sock);
			return menu(client_sock,type,id);	
		}
		else if(choice==2){				
			crud_user(client_sock);
			return menu(client_sock,type,id);
		}
		else if (choice ==3)				
			return -1;
	}
	else if(type==2 || type==1){				
		read(client_sock,&choice,sizeof(choice));
		ret = user_function(client_sock,choice,type,id);
		if(ret!=5)
			return menu(client_sock,type,id);
		else if(ret==5)
			return -1;
	}		
}
