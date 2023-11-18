#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>

#define PORT 5035
#define MAXLINE 1024

int main() {
	int sd = socket(AF_INET, SOCK_DGRAM, 0);
	int number;
	socklen_t addressLength;
	char message[MAXLINE];
	
	struct sockaddr_in serverAddress, clientAddress;
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_port = htons(PORT);
	serverAddress.sin_addr.s_addr = INADDR_ANY;
	
	bind(sd, (struct sockaddr*)&serverAddress, sizeof(serverAddress));
	printf("Server Running \n");
	
	while(1) {
	addressLength = sizeof(clientAddress);
	number = recvfrom(sd, message, MAXLINE, 0, (struct sockaddr*)&clientAddress, &addressLength);
	printf("Message is: %s", message);
	
	if (number<6)
		perror("Send Error");
		
	sendto(sd, message, MAXLINE, 0 , (struct sockaddr*)&clientAddress, addressLength);
	}
	return 0;
}
