#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <extend.h>
#include "webfetch.h"

	void print_usage()
	{
		printf("Usage : -h(host) $ [-l(path) $] [-p(port) $] [-m(method) $] [-d(data) $] [-v(headerdata) '$=$,$=$..'] [-q(responsetype) $]\n");
		exit(-1);
	}

	int main(int argc, char ** argv)
	{
		int long_index = 0, opt = 0, response_type = 0;
		char * host = NULL, * port = NULL, * path = NULL, * method = NULL, * data = NULL, * header_data = NULL, * response = NULL;
		
		static struct option long_options[] = {
			{"host",   		required_argument,  0,  'h' },
			{"path", 		required_argument,  0,  'l' },
			{"port",  		required_argument,	0,  'p' },
			{"method",		required_argument,	0,	'm' },
			{"data",		required_argument,	0,	'd' },
			{"headerdata",	required_argument,	0,	'v' },
			{"responsetype",required_argument,	0,	'q' },
			{0,				0,					0,	0   }
		};
		
		
		while ( (opt = getopt_long(argc, argv, "h:l:p:m:d:v:q:", long_options, &long_index )) != -1 ) 
			switch (opt) 
			{
				case 'h' :
					host = optarg;
					break;
				case 'p' :
					port = optarg;
					break;
				case 'l' : 
					path = optarg;
					break;
				case 'm' : 
					method = optarg;
					break;
				case 'd' : 
					data = optarg;
					break;
				case 'v' : 
					header_data = optarg;
					break;
				case 'q' : 
					response_type = atoi(optarg);
					break;
				default:
					print_usage();
					exit(EXIT_FAILURE);
			}
		
		
		
		if(host == NULL)
			{print_usage(); exit(EXIT_FAILURE);}
		
		if(port == NULL)
			{port = str_merge(port,"80",NULL);}

		if(path == NULL)
			{path = str_merge(path,"/",NULL);}
		
		if(method == NULL)
			{method = str_merge(method,"GET",NULL);}

		if(data == NULL)
		{
			if((data = (char *)malloc(sizeof(char)))==NULL)
				{printf("ERROR:3");exit(-1);}
			*data = '\0';
		}

		if(header_data == NULL)
		{
			if((header_data = (char *)malloc(sizeof(char)))==NULL)
				{printf("ERROR:2");exit(-1);}
			*header_data = '\0';
		}
		
		if(response_type < 0 && response_type > 1)
			{response_type = 0;}

		response = web_request(host, port, path, method, data, header_data);	
		
		if(response!=NULL)	
		{			
			if(response_type == 0)
				printf("%s",response);
			else if(response_type == 1)
				printf("%s",strstr(response,"\r\n\r\n")+4);
		}else
		{
			printf("ERROR:1");
		}

		exit(0);
}