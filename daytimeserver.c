#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <time.h>

#define PORT 9002
#define BACKLOG 10

int main() {
	time_t currentTime;
	time(&currentTime);
	
	int countClient = 0;
	
	int sd = socket(AF_INET, SOCK_STREAM, 0);
	
	struct sockaddr_in serverAddress;
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_port = htons(PORT);
	serverAddress.sin_addr.s_addr = INADDR_ANY;
	
	bind(sd, (struct sockaddr*)&serverAddress, sizeof(serverAddress));
	
	listen(sd, BACKLOG);
	
	printf("Server Started \n");
	
	while(1) {
		countClient++;
		printf("\n");
		
		int client_socket = accept(sd, NULL, NULL);
		
		printf("Client %d has requested for time at %s", countClient, ctime(&currentTime));
		
		send(client_socket, ctime(&currentTime), 30, 0);
	}
	close(sd);
	return 0;
}
