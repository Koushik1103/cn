#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

#define h_addr h_addr_list[0]

#define PORT 9002
#define MAX 1000

int main() {
	char serverResp[MAX], clientResp[MAX];
	
	int sd = socket(AF_INET, SOCK_STREAM, 0);
	
	char hostname[MAX], ipaddress[MAX];
	
	struct hostent *hostIP;
	
	if (gethostname(hostname, sizeof(hostname))==0) {
		hostIP = gethostbyname(hostname);
	} else {
		printf("ERROR");
	}
	
	struct sockaddr_in serverAddress;
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_port = htons(PORT);
	serverAddress.sin_addr.s_addr = INADDR_ANY;
	
	connect(sd, (struct sockaddr*)&serverAddress, sizeof(serverAddress));
	
	printf("\nLocalhost: %s\n", inet_ntoa(*(struct in_addr*)hostIP->h_addr));
	printf("Local Port: %d\n", PORT);
	printf("Remote Host: %s\n", inet_ntoa(serverAddress.sin_addr));
	
	while(1) {
		recv(sd, serverResp, sizeof(serverResp), 0);
		printf("Server: %s\n", serverResp);
		printf("Enter message: ");
		scanf("%s", clientResp);
		send(sd, clientResp, sizeof(clientResp), 0);
	}
	close(sd);
	return 0;
}
