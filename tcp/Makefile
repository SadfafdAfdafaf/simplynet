COMP       := gcc
COMP_FLAGS := -std=c11 -Wall -pedantic 

LIB        := -lws2_32 



client:
	$(COMP) $(COMP_FLAGS) client.c $(LIB)  -o client.exe

server:
	$(COMP) $(COMP_FLAGS) server.c $(LIB) -o server.exe
