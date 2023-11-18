#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>

int main() {
	char serverMessage[256] = "Message\n";
	
	int sd = socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in serverAddr;
	
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(9002);
	serverAddr.sin_addr.s_addr = INADDR_ANY;
	
	bind(sd, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
	
	listen(sd,5);
	
	int client_socket = accept(sd, NULL, NULL);
	
	send(client_socket, serverMessage, sizeof(serverMessage), 0);
	
	close(sd);
	
	return 0;
}
