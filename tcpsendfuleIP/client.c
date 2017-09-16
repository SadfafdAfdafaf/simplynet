#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>


#define PORT 27015
#define SERVERADDR "127.0.0.2"
 
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
    char value[256];
    printf("Enter name: ");
    scanf("%s", value);
	FILE* fd = fopen(value, "rb");
	if (!fd)
	{
		printf("Error file\n");
		exit(1);
	}
	
	char value2[256];
    printf("Enter copy name: ");
    scanf("%s", value2);
	send(my_sock, value2, 256, 0);
	
	
	char buf[4096];	
	printf("Sending.....\n");
	size_t sz;
	
	while((sz = fread(buf, 1, 4096, fd))>0){
		send(my_sock, buf, sz, 0);
		printf("send data %d\n", sz);
	}
	
	printf("Succes.\n");
	fclose(fd);
  
    closesocket(my_sock);
    WSACleanup();
    return 0;
}