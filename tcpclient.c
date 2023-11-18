#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>

int main() {
	int sd = socket(AF_INET, SOCK_STREAM, 0);
	
	struct sockaddr_in serverAddr;
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(9002);
	serverAddr.sin_addr.s_addr = INADDR_ANY;
	
	connect(sd, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
	
	char serverResponse[256];
	
	recv(sd, &serverResponse, sizeof(serverResponse), 0);
	
	printf("Message is: %s", serverResponse);
	
	close(sd);
	
	return 0;
}
