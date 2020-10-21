#include <sys/types.h> 
#include <string.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <unistd.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <errno.h>

#define PATH "../"

int writePage(char *page, int fd);
char* path;

int main()
{
	int create_socket,new_socket;
	int create_bind;
	struct sockaddr_in address; 
	int bufferSize=1024;
	char *buffer=malloc(bufferSize);
	char *route;
	socklen_t addrlen=1024;
	char delim[2]="/";
	setvbuf(stdout, NULL, _IONBF, 0);
	/* strcat(path,"../"); */
	//create socket
	if((create_socket=socket(AF_INET,SOCK_STREAM,0))>0)
	{
		printf("Socket created\n");

	}
	else
	{
		perror("Server:Socket");
	}
	//setting bind params
	address.sin_family=AF_INET;
	address.sin_port=htons(8080);
	address.sin_addr.s_addr=INADDR_ANY;
	int one=1;
	setsockopt(create_socket, SOL_SOCKET, SO_REUSEADDR, &one, sizeof(one));
	if((create_bind=bind(create_socket,(struct sockaddr *)&address, sizeof(address)))!=0)
	{
		perror("Server : bind");
		exit(1);
	}
	while(1)
	{
		if (listen(create_socket,10)==0) {
			printf("listening on port 8080\n");
			if((new_socket=accept(create_socket, (struct sockaddr *)&address,&addrlen))>0)
			{
				printf("Accepted \n");
				while(1){
					recv(new_socket,buffer,bufferSize,0);
					/* printf("buffer is:%s",buffer); */
					if(!strncmp(buffer,"GET",3))
					{
						/* printf("GET found \n"); */
						char *modBuffer;
						strncpy(modBuffer,buffer,4);
						route=strtok(modBuffer,delim);
						route=strtok(NULL,delim);
						if(route==NULL)
						{
							writePage("index",new_socket);
						}
					}

				}
			}

			else
			{
				perror("Server:Accept");
				exit(1);
			}

		}
		else
		{
			/* printf("Listen problem\n"); */
			perror("Server:Listen");
			exit(1);
		}
	}
	close(create_socket);
	free(buffer);
}

int writePage(char* page,int fd)
{
	char* fileName;
	char* fullFileName;
	/* strcat(fileName,path); */
	strcat(fileName,page);
	strcat(fileName,".htm");
	/* strcat(fullFileName,fileName); */
	FILE* file=fopen(fileName,"r");
	if(file==NULL)
	{
		perror("server:file");
		exit(1);
	}
	write(fd,"<!DOCTYPE html>\n<html>\n<body>\n<h1>\nHI\n</h1>\n</body>\n</html>",100);
	/* while() */
	/* { */

	/* } */
	return 0;
}
