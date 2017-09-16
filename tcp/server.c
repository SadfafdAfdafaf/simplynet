#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>

#define MY_PORT 27015
#define SERVERADDR "99.68.1.115"

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

    client_socket = accept(mysocket, (struct sockaddr *)&client_addr, &client_addr_size);
    if(client_socket < 0)
    {
        printf("Error on accept [%d]\n", WSAGetLastError());
        closesocket(mysocket);
        WSACleanup();
        return -1;
    }
    int value;
    int r = recv(client_socket, (char*)&value, sizeof(value), 0);
    if(r == sizeof(value))
    {
        value = ntohl(value);
        printf("Received value [%d]\n", value);
    }
    closesocket(client_socket);
    closesocket(mysocket);
    WSACleanup();
 
    return 0;
}