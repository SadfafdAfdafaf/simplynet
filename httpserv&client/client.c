#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>


#define PORT 8080
#define SERVERADDR "127.0.0.2"
 
char get[] = "GET /l4.html HTTP/1.1"; 
 
int main(int argc, char* argv[])
{
    printf("TCP CLIENT\n");
 
    WSADATA WsaData;
    if(WSAStartup(0x202, &WsaData))
    {
        printf("WSAStart error %d\n", WSAGetLastError());
        return -1;
    }
 
    SOCKET my_sock;
    my_sock = socket(AF_INET, SOCK_STREAM, 0);
    if(my_sock < 0)
    {
        printf("Socket() error %d\n", WSAGetLastError());
        return -1;
    }
 
    struct sockaddr_in dest_addr;
    dest_addr.sin_family = AF_INET;
    dest_addr.sin_port = htons(PORT);
 
    if(inet_addr(SERVERADDR) != INADDR_NONE)
        dest_addr.sin_addr.s_addr = inet_addr(SERVERADDR);
    else
    {
        printf("Invalid address %s\n", SERVERADDR);
        closesocket(my_sock);
        WSACleanup();
        return -1;
    }
 
    if(connect(my_sock, (struct sockaddr *)&dest_addr, sizeof(dest_addr)))
    {
        printf("Connect error %d\n", WSAGetLastError());
 
        closesocket(my_sock);
        WSACleanup();
        return -1;
    }
 
    printf("Connected to port %d, type 0 for exit\n", PORT);

	send(my_sock, get, sizeof(get), 0);
	char value[4096];
	int r;
	while((r = recv(my_sock, value, 4096, 0)) > 0){		
		printf("%s", value);
	}
	  
    closesocket(my_sock);
    WSACleanup();
    return 0;
}