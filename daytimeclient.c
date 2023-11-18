#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>

#define PORT 9002
#define MAXLINE 30

int main() {
	int sd = socket(AF_INET, SOCK_STREAM, 0);
	
	struct sockaddr_in serverAddress;
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_port = htons(PORT);
	serverAddress.sin_addr.s_addr = INADDR_ANY;
	
	connect(sd, (struct sockaddr*)&serverAddress, sizeof(serverAddress));
	
	char serverResponse[MAXLINE];
	
	recv(sd, serverResponse, MAXLINE-1, 0);
	printf("Time is %s", serverResponse);
	close(sd);
	return 0;
}
