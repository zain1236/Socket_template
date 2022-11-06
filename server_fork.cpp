#include <stdio.h>
#include <stdlib.h>
#include<unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <ctime>
#include<fstream>

#include <sys/wait.h>

#include <netinet/in.h>
#include<iostream>
using namespace std;



int main() {


	// create the server socket
	int server_socket;
	server_socket = socket(AF_INET, SOCK_STREAM, 0);

	
	// define the server address
	struct sockaddr_in server_address;
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(3001);
	server_address.sin_addr.s_addr = INADDR_ANY;

	// bind the socket to our specified IP and port
	bind(server_socket, (struct sockaddr*) &server_address, sizeof(server_address));
	listen(server_socket, 5);

	while(1)
	{
	
		int client_socket;
		client_socket = accept(server_socket, NULL, NULL);
		
		int f_id = fork();
		if(f_id == 0)
		{
			char buf[1024] = "hi";
			while(!(strncmp(buf,"exit",4) == 0) )
			{

				int n = recv(client_socket, &buf, 1024, 0);
				buf[n] = '\0';
				cout << "\nReceived : " << buf << endl;
				
				char * msg = "received your message";
				//cout << "\nsending : " << msg;
				send(client_socket, msg, strlen(msg), 0);	
			}
			close(client_socket);	

		}		
		else
		{

			close(client_socket);
		}
	}
	
	// close the socket
	close(server_socket);
	
	return 0;
}
