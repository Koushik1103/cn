#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>

#define MAX 1000
#define BACKLOG 5

int main() {
	char serverMsg[MAX];
	char clientMsg[MAX];
	
	int sd = socket(AF_INET, SOCK_STREAM, 0);
	
	struct sockaddr_in serverAddress;
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_port = htons(9002);
	serverAddress.sin_addr.s_addr = INADDR_ANY;
	
	bind(sd, (struct sockaddr*)&serverAddress, sizeof(serverAddress));
	listen(sd, BACKLOG);
	
	int client_socket = accept(sd, NULL, NULL);
	
	printf("Server Started\n");
	
	while(1) {
		printf("Enter Message: ");
		scanf("%s", serverMsg);
		
		send(client_socket, serverMsg, sizeof(serverMsg), 0);
		recv(client_socket, &clientMsg, sizeof(clientMsg), 0);
		
		printf("Client: %s", clientMsg);
	}
	close(sd);
	return 0;
}
