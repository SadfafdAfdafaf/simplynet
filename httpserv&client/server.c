#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>

#define MY_PORT 8080
#define SERVERADDR "127.0.0.2"
#define SERVER_ROOT "C:/Users/FlyCat/Desktop/soket/httpserv"

char response[] = "HTTP/1.1 501 You are nigger's shit\r\n";
char response2[] = "HTTP/1.1 500 What are you doing?\r\n";


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
	char value[4096];
    int client_addr_size = sizeof(client_addr); 
	char *method, *path;
	char get_path[1024] = {0};
	FILE* file;
	size_t sz;
	while (1) {
		client_socket = accept(mysocket, (struct sockaddr *)&client_addr, &client_addr_size);
		if(client_socket < 0)
		{
			perror("Can't accept");
			continue;
		}
		printf("got connection\n");

 		recv(client_socket, value, 4096, 0);
		method = strtok(value, " ");
		path = strtok(NULL, " ");

		strcat(get_path, SERVER_ROOT);
		strcat(get_path, path);
		
		if(strcmp(method, "GET") != 0)
			send(client_socket, response, sizeof(response) - 1, 0);
		else{
			file = fopen(get_path, "r");
			if (!file)
			{
				send(client_socket, response2, sizeof(response2) - 1, 0);				
			}else{
			while((sz = fread(value, 1, 4096, file))>0){
				send(client_socket, value, sz, 0);
			}}
			fclose(file);
		}
		
		memset(get_path,0,1024);
		closesocket(client_socket);
	}
    
    closesocket(mysocket); 
    WSACleanup();
 
    return 0;
}