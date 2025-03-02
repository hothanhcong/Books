#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#define PORT 8080

int main(int argc, char const* argv[])
{
	int status, valread, client_fd;
	struct sockaddr_in serv_addr;
	char buffer[1024] = { 0 };
	
	if ((client_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		printf("\n Socket creation error \n");
		return -1;
	}

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(PORT);

	// Convert IPv4 and IPv6 addresses from text to binary form
	if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
		printf("\nInvalid address/ Address not supported \n");
		return -1;
	}

	if ((status = connect(client_fd, (struct sockaddr*)&serv_addr, sizeof(serv_addr))) < 0) {
		printf("\nConnection Failed \n");
		return -1;
	}

	while(1) {
		printf("Client: ");
		fgets(buffer, 1024, stdin);
		if (strncmp(buffer, "exit", 4) == 0) {
			break;
		}
		write(client_fd, buffer, strlen(buffer));
		bzero(buffer, 1024);	
		valread = read(client_fd, buffer, 1024 - 1);
		if (valread <= 0) {
			printf("Server disconnected\n");
			break;
		}
		printf("Server: %s", buffer);
	}

	close(client_fd);
	return 0;
}
