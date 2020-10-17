//Thnaks to http://blog.manula.org/2011/05/writing-simple-web-server-in-c.html
#include <sys/types.h> 
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <unistd.h>
#include <netinet/in.h>
#include <netinet/ip.h>

int main()
{
	int create_socket,new_socket;
	int create_bind;
	struct sockaddr_in address; 
	socklen_t addrlen=100;
	//create socket
	if((create_socket=socket(AF_INET,SOCK_STREAM,0))>0)
	{
		fprintf(stdout,"Socket created\n");
		fflush(stdout);

	}
	else
	{
		fprintf(stdout,"Socket not created\n");
	}
	fflush(stdout);
	//setting bind params
	address.sin_family=AF_INET;
	address.sin_port=htons(8080);
	address.sin_addr.s_addr=INADDR_ANY;
	if((create_bind=bind(create_socket,(struct sockaddr *)&address, sizeof(address)))!=0)
	{
		fprintf(stdout,"Binding Problem\n");
		exit(1);
	}
	while(1)
	{
		if (listen(create_socket,10)==0) {
			fprintf(stdout,"listening on port 8080\n");
			if((new_socket=accept(create_socket, (struct sockaddr *)&address,&addrlen))>0)
			{
				fprintf(stdout,"Accepted \n");
				fflush(stdout);
			}
			else
			{
				fprintf(stdout,"Problem on Accept");
				exit(1);
			}

		}
		else
		{
			printf("Listen problem\n");
			exit(1);
		}
	}
	printf("End\n");
	sleep(720);
	close(create_socket);
}
