//Using SDL, SDL_image, standard IO, and, strings
#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <SDL_Net.h>
#include <cstdio>
#include <iostream>
#include <string>

#define PORT 2310
#define MAXUSERS 10

struct Client
{
	std::string name = "DERP";
	Uint32 ipAddr = 0;
	TCPsocket socket = 0;
	IPaddress* remoteIP = 0;
};

std::string GetNameFrom(char* a, int size, int position)
{
		int i;
		std::string s = "";
		for (i = position; i < size; i++) {
			s = s + a[i];
		}
		return s;
}

bool starts_with(const char *string, const char *prefix)
{
	while (*prefix)
	{
		if (*prefix++ != *string++)
			return 0;
	}

	return 1;
}

int main()
{
	// Server Initializations
	printf("Starting server....\n\n");

	if (SDL_Init(0) == -1)
	{
		printf("SDL_INIT FAILED: %s\n", SDL_GetError());
		exit(1);
	}
	if (SDLNet_Init() == -1) {
		printf("SDLNET_INIT FAILED: %s\n", SDLNet_GetError());
		exit(2);
	}

	// While running
	bool running = true;
	
	TCPsocket server;
	int clientAmount = 0;
	IPaddress ip;

	if (SDLNet_ResolveHost(&ip, NULL, PORT) == -1) 
	{
		printf("SDLNET_RESOLVEHOST FAILED: %s\n", SDLNet_GetError());
		exit(1);
	}

	server = SDLNet_TCP_Open(&ip);
	if (!server)
	{
		printf("SDLNET_TCP_OPEN FAILED: %s\n", SDLNet_GetError());
		exit(2);
	}
	
	SDLNet_SocketSet socketSet = SDLNet_AllocSocketSet(MAXUSERS);
	Client* clients = new Client[MAXUSERS];
	
	printf("Server seemed to start properly.\nRunning!");
	while (running)
	{
		printf("\n===========================\nUPDATELOOP\n===========================\n");
		SDLNet_CheckSockets(socketSet, 0);
		/* Process Every connected client*/
		for (int i = 0; i < MAXUSERS; i++)
		{
			printf("\nProcessing slot %i: ", i);
			/* try to accept a connection */
			if (clients[i].socket == NULL)
			{
				clients[i].socket = SDLNet_TCP_Accept(server);
				if (!clients[i].socket) { 
					/* no connection accepted */
					//printf("SDLNet_TCP_Accept: %s\n",SDLNet_GetError());
					//SDL_Delay(100); /*sleep 1/10th of a second */
					//continue;
					printf("NULL");
					continue;
				}

				SDLNet_AddSocket(socketSet, (SDLNet_GenericSocket)clients[i].socket);

				/* get the clients IP and port number */
				clients[i].remoteIP = SDLNet_TCP_GetPeerAddress(clients[i].socket);
				if (!clients[i].remoteIP) {
					printf("SDLNET_TCP_GETPEERADDRESS FAILED: %s\n", SDLNet_GetError());
					continue;
				}

				/* print out the clients IP and port number */
				clients[i].ipAddr = SDL_SwapBE32(clients[i].remoteIP->host);
				printf("Accepted a connection from %d.%d.%d.%d port %hu\n", clients[i].ipAddr >> 24,
					(clients[i].ipAddr >> 16) & 0xff, (clients[i].ipAddr >> 8) & 0xff, clients[i].ipAddr & 0xff,
					clients[i].remoteIP->port);

				clients[i].name = "USER#" + std::to_string(i);

				for (int x = 0; x < MAXUSERS; x++)
				{
					std::string newMessage = "System> " + clients[i].name + " has connected to the chat";
					if (clients[x].socket != 0)
					{
						SDLNet_TCP_Send(clients[x].socket, newMessage.c_str(), newMessage.length());
					}
				}
			}
			else
			{
				if (SDLNet_SocketReady(clients[i].socket))
				{
					/* read the buffer from client */
					char message[1024];
					int len = SDLNet_TCP_Recv(clients[i].socket, message, 1024);
					if (!len) {
						printf("Error or host closed connection\n");

						// Send message of disconnection to all
						for (int x = 0; x < MAXUSERS; x++)
						{
							std::string newMessage = "System> " + clients[i].name + " has left the chat";
							if (clients[x].socket != 0)
							{
								SDLNet_TCP_Send(clients[x].socket, newMessage.c_str(), newMessage.length());
							}
						}
						clients[i].socket = 0;
						clients[i].ipAddr = 0;
						clients[i].remoteIP = 0;
						break;
					}
					/* Read Send message forward */
					//printf("Received: %.*s\n", len, message);
					//if (message[0] == '/') 
					//{
					//	if (message[1] == 'n')
					//	{
					//		strcpy()
					//	}
					//}
					std::string newMessage = clients[i].name + ": "; // Message we return

					// Detect command
					if (message[0] == '/')
					{
						if (starts_with(message, "/nick "))
						{
							clients[i].name = GetNameFrom(message, len, 6);
						}

						newMessage = "Changed userName to = " + clients[i].name;

						SDLNet_TCP_Send(clients[i].socket, newMessage.c_str(), newMessage.length());
						continue;
					}

					for (int x = 0; x < len; x++)
					{
						newMessage += message[x];
					}

					// Send message to everyone
					for (int x = 0; x < MAXUSERS; x++)
					{
						if (clients[x].socket != 0)
						{
							SDLNet_TCP_Send(clients[x].socket, newMessage.c_str(), newMessage.length());
						}
					}
				}
			}
		}

		SDL_Delay(500);

	}
	for (int i = 0; i < MAXUSERS; i++)
	{
		SDLNet_TCP_Close(clients[i].socket);
	}
	return 0;
}