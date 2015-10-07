#include "webfetch.h"

	char * web_request(char * host, char * port, char * path, char * method, char * data, char * header_data)
	{
		struct hostent * server;
		struct sockaddr_in serv_addr;
		int sockfd, bytes, sent, received, total;
		char * response = NULL,* message = NULL,* header = NULL,* body = NULL, **header_parts = NULL, buffer[1];
		if(header_data != NULL)
			if( strstr(header_data,"=") != NULL)
				header_parts = str_split (header_data,'=');	
		
		message = str_merge(6,str_uppercase(method)," ",path," HTTP/1.0\r\nHost: ",host,"\r\n");

		if(header_parts!=NULL)
			message = str_merge(5,message
								,header_parts[0],": "
								,header_parts[1],"\r\n");

		message = str_merge(5,message,"Content-Type: application/json\r\nContent-Length: "
							,num_tostr((int)strlen(data)),"\r\n\r\n"
							,data
							);		

		sockfd = socket(AF_INET, SOCK_STREAM, 0);
		
		if (sockfd < 0) 
			return NULL;
		
		server = gethostbyname(host);
		if (server == NULL)
			return NULL;
		
		memset(&serv_addr,0,sizeof(serv_addr));
		serv_addr.sin_family = AF_INET;
		serv_addr.sin_port = htons(atoi(port));
		memcpy(&serv_addr.sin_addr.s_addr,server->h_addr,server->h_length);
		
		if (connect(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr)) < 0)
			return NULL;
		
		total = strlen(message);
		
		sent = 0;
		do 
		{
			bytes = write(sockfd,message+sent,total-sent);
			if (bytes < 0)
				return NULL;
			if (bytes == 0) 
				break;
			sent+=bytes;
		} while (sent < total);
		
		memset(buffer, 0, sizeof(buffer));
		total = sizeof(buffer)-1;
		received = 0;
		do 
		{
			bytes = recv(sockfd, buffer, 1, 0);
			if (bytes < 0)
				return NULL;
			if (bytes == 0)
				break;
			received+=bytes;
			if( (response = (char *) realloc(response,received*sizeof(char))) == NULL) 
				return NULL;
			*(response+(received-1))=buffer[0];
		} while (1);
		
		if( (response = (char *) realloc(response,(received+1)*sizeof(char))) == NULL) 
			return NULL;
		
		*(response+received)='\0';
		
		return response;
	}