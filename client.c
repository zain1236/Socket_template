// Client side implementation of UDP client-server model
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define PORT	 8080
#define MAXLINE 1024

// Driver code
int main() {
	int sockfd;
	char buffer[MAXLINE];

	struct sockaddr_in	 servaddr;

	// Creating socket file descriptor
	if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
		perror("socket creation failed");
		exit(EXIT_FAILURE);
	}

	//memset(&servaddr, 0, sizeof(servaddr));
	
	// Filling server information
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(PORT);
	servaddr.sin_addr.s_addr = inet_addr("172.17.39.195");
	

	while(1)
	{
		int n=0, len;
		len = sizeof(servaddr); //len is value/resuslt
		char hello[1024];
		printf("Enter message : ");
		fgets(hello,1024,stdin);


		sendto(sockfd, (const char *)hello, strlen(hello),
			0, (const struct sockaddr *) &servaddr,
				sizeof(servaddr));
				
						
		printf("message sent %s\n",hello);
			
		n = recvfrom(sockfd, (char *)buffer, MAXLINE,
					0, (struct sockaddr *) &servaddr,
					&len);
		buffer[n] = '\0';
		printf("Server : %s\n", buffer);
		printf("Bytes received : %d \n",n);

	}
	
	close(sockfd);
	return 0;
}