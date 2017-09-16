#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>

#define PORT 27015
#define BUFLEN 512

int main(int argc, char* argv[])
{
    char buf[BUFLEN];
    WSADATA WsaData;
    SOCKET mysocket;
    struct sockaddr_in addr;
    struct sockaddr_in client_addr;
     int client_addr_size = sizeof(client_addr);

    printf("STARTING UDP SERVER\n");
 
    if(WSAStartup(0x0202, &WsaData))
    {
        printf("Error WSAStartup %d\n", WSAGetLastError());
        return -1;
    }


    if((mysocket = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        printf("Error socket %d\n", WSAGetLastError());
        WSACleanup();
        return -1;
    }
 
    
    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);
    addr.sin_addr.s_addr = INADDR_ANY;
    

    if(bind(mysocket, (struct sockaddr *)&addr, sizeof(addr)))
    {
        printf("Error bind %d\n", WSAGetLastError());
        closesocket(mysocket);
        WSACleanup();
        return -1;
    }

    while(1){
    printf("Waiting for messenge...\n");   
    fflush(stdout);
   

    int r = recvfrom(mysocket, buf, BUFLEN,0,
     (struct sockaddr *) &client_addr, &client_addr_size);

    if (r == SOCKET_ERROR)
      printf("recvfrom() error: %d\n",   WSAGetLastError());

    printf("Received value [%s]\n", buf);
    }
    
    closesocket(mysocket);
    WSACleanup();
 
    return 0;
}