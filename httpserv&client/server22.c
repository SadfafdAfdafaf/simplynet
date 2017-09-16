#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>

#define MY_PORT 8080
#define SERVERADDR "127.0.0.2"

char response[] = "HTTP/1.1 200 OK\r\n"
"Content-Type: text/html; charset=UTF-8\r\n\r\n"
"<!DOCTYPE html><html><head><title>Bye-bye baby bye-bye</title>"
"<style>body { background-color: #111 }"
"h1 { font-size:4cm; text-align: center; color: black;"
" text-shadow: 0 0 2mm red}</style></head>"
"<body><h1>Goodbye, world!</h1></body></html>\r\n";

int main(int argc, char* argv[])
{
    printf("STARTING TCP SERVER\n");
    WSADATA WsaData;
 
    if(WSAStartup(0x0202, &WsaData))
    {
        printf("Error WSAStartup %d\n", WSAGetLastError());
        return -1;
    }

    SOCKET mysocket;
    if((mysocket = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("Error socket %d\n", WSAGetLastError());
        WSACleanup();
        return -1;
    }
 
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(MY_PORT); 
    if(inet_addr(SERVERADDR) != INADDR_NONE)
        addr.sin_addr.s_addr = inet_addr(SERVERADDR);
    else
    {
        printf("Invalid address %s\n", SERVERADDR);
        closesocket(mysocket);
        WSACleanup();
        return -1;
    }

    if(bind(mysocket, (struct sockaddr *)&addr, sizeof(addr)))
    {
        printf("Error bind %d\n", WSAGetLastError());
        closesocket(mysocket);
        WSACleanup();
        return -1;
    }
 
    if(listen(mysocket, 10))
    {
        printf("Error listen %d\n", WSAGetLastError());
        closesocket(mysocket);
        WSACleanup();
        return -1;
    }
 
    printf("Waiting for connection...\n");

	SOCKET client_socket;   
    struct sockaddr_in client_addr; 

    int client_addr_size = sizeof(client_addr); 
	while (1) {
		client_socket = accept(mysocket, (struct sockaddr *)&client_addr, &client_addr_size);
		if(client_socket < 0)
		{
			perror("Can't accept");
			continue;
		}
		printf("got connection\n");

		send(client_socket, response, sizeof(response) - 1, 0);
		closesocket(client_socket);
	}
    
    closesocket(mysocket); 
    WSACleanup();
 
    return 0;
}