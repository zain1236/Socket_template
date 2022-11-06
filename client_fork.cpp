#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <netinet/in.h>
#include <iostream>
#include <arpa/inet.h>
using namespace std;

int main() {
	

	
	// create the socket
	int sock;
	sock = socket(AF_INET, SOCK_STREAM, 0);
	
	//setup an address
	struct sockaddr_in server_address;
	server_address.sin_family = AF_INET;
	server_address.sin_addr.s_addr = inet_addr("172.17.39.195");
	server_address.sin_port = htons(3001);

	connect(sock, (struct sockaddr *) &server_address, sizeof(server_address));
	
	string message="Hi";

	while(message != "exit")
	{
		
		cout<<"\nEnter mssage you want to send to server:";
		getline(cin,message);
		char * msg = &message[0];
		send(sock, msg, strlen(msg), 0);
		char buf[1024];
		int n = recv(sock, &buf, sizeof(buf), 0);
		buf[n] = '\0';
		cout << "\nReceived : " << buf << endl;

	}

	close(sock);

	return 0;
}

