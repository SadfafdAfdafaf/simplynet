#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>

#define BUFLEN 512
#define PORT 27015
#define SERVERADDR "127.0.0.1"
 
int main(int argc, char* argv[])
{
    char message[BUFLEN];
    struct sockaddr_in dest_addr;
    WSADATA WsaData;
    SOCKET my_sock;

    printf("UDP CLIENT\n");
 
    
    if(WSAStartup(0x202, &WsaData))
    {
        printf("WSAStart error %d\n", WSAGetLastError());
        return -1;
    }
 
    
    my_sock = socket(AF_INET, SOCK_DGRAM, 0);
    if(my_sock < 0)
    {
        printf("Socket() error %d\n", WSAGetLastError());
        return -1;
    }
    
    dest_addr.sin_family = AF_INET;
    dest_addr.sin_port = htons(PORT);
    dest_addr.sin_addr.S_un.S_addr = inet_addr(SERVERADDR);

     while(1)
    {
        printf("Enter message : ");
        gets(message);
                 
        if (sendto(my_sock, message, strlen(message) , 0 , (struct sockaddr *) &dest_addr, sizeof(dest_addr)) == SOCKET_ERROR)
        {
            printf("sendto() failed with error code : %d" , WSAGetLastError());
            exit(EXIT_FAILURE);
        }
    }
      
    closesocket(my_sock);
    WSACleanup();
    return 0;
}