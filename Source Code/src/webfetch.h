#ifndef _WEBFETCH_H
	#define _WEBFETCH_H
	
		#include <stdio.h> 
		#include <netdb.h>
		#include <stdlib.h>
		#include <string.h>
		#include <extend.h>
		#include <sys/socket.h>
		#include <netinet/in.h>
	
		char * web_request(char *, char *, char *, char *, char *, char *);
	
#endif