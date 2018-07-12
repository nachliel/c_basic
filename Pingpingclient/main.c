#undef UNICODE

#define WIN32_LEAN_AND_MEAN

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <SDL.h>
#include "timing.h"
#include "config.h"
#include "player.h"
#include "ball.h"


#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <signal.h>

// Need to link with Ws2_32.lib
#pragma comment (lib, "Ws2_32.lib")

#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "27015"

// get sockaddr, IPv4 or IPv6:
void *get_in_addr(struct sockaddr *sa)
{
	if (sa->sa_family == AF_INET) {
		return &(((struct sockaddr_in*)sa)->sin_addr);
	}

	return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

void renderer(Player *player1, Player *player2, Ball *ball, SDL_Surface *screen, SDL_Surface *spaceShipSurface) {
	SDL_Rect rect;
	rect.x = (int)player1->Obj.x;
	rect.y = (int)player1->Obj.y;
	rect.h = (int)player1->Obj.h;
	rect.w = (int)player1->Obj.w;
	SDL_FillRect(screen, &rect, SDL_MapRGB(spaceShipSurface->format, 255, 255, 255));

	rect.x = (int)player2->Obj.x;
	rect.y = (int)player2->Obj.y;
	rect.h = (int)player2->Obj.h;
	rect.w = (int)player2->Obj.w;
	SDL_FillRect(screen, &rect, SDL_MapRGB(spaceShipSurface->format, 255, 255, 255));

	rect.x = (int)ball->Obj.x;
	rect.y = (int)ball->Obj.y;
	rect.h = (int)ball->Obj.h;
	rect.w = (int)ball->Obj.w;
	SDL_FillRect(screen, &rect, SDL_MapRGB(spaceShipSurface->format, 255, 255, 255));
}
int main(void)
{
	/*
	Winsock:
	*/
	WSADATA wsaData;

	SOCKET ClientSocket = INVALID_SOCKET;;
	SOCKET ListenSocket = INVALID_SOCKET;

	struct addrinfo *result = NULL, *ptr = NULL, hints;

	char recvbuf[DEFAULT_BUFLEN];
	int iResult, iSendResult;
	int recvbuflen = DEFAULT_BUFLEN;

	// Initialize Winsock
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0) {
		printf("WSAStartup failed: %d\n", iResult);
		return 1;
	}

	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	hints.ai_flags = AI_PASSIVE;

	// Resolve the local address and port to be used by the server
	iResult = getaddrinfo(NULL, DEFAULT_PORT, &hints, &result);
	if (iResult != 0) {
		printf("getaddrinfo failed: %d\n", iResult);
		WSACleanup();
		return 1;
	}

	ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
	if (ListenSocket == INVALID_SOCKET) {
		printf("Error at socket(): %ld\n", WSAGetLastError());
		freeaddrinfo(result);
		WSACleanup();
		return 1;
	}
	iResult = bind(ListenSocket, result->ai_addr, (int)result->ai_addrlen);
	if (iResult == SOCKET_ERROR) {
		printf("bind failed with error: %d\n", WSAGetLastError());
		freeaddrinfo(result);
		closesocket(ListenSocket);
		WSACleanup();
		return 1;
	}
	freeaddrinfo(result);

	if (listen(ListenSocket, SOMAXCONN) == SOCKET_ERROR) {
		printf("Listen failed with error: %ld\n", WSAGetLastError());
		closesocket(ListenSocket);
		WSACleanup();
		return 1;
	}

	printf("Waitting for connection...");
	ClientSocket = accept(ListenSocket, NULL, NULL);
	if (ClientSocket == INVALID_SOCKET) {
		printf("accept failed: %d\n", WSAGetLastError());
		closesocket(ListenSocket);
		WSACleanup();
		return 1;
	}
	// No longer need server socket
	closesocket(ListenSocket);

	/*
	SDL shit...
	*/
	printf("Initalizing Video...\n");
	SDL_Init(SDL_INIT_VIDEO);
	SDL_Window* window = SDL_CreateWindow(WINDOW_TITLE,
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	SDL_Surface *screenSurface = SDL_GetWindowSurface(window);
	SDL_Surface *spaceShipSurface = SDL_CreateRGBSurface(0, CRAFT_WIDTH, CRAFT_HEIGHT, 32, 0, 0, 0, 0);
	SDL_Event e;

	/*
	Players, ball and settings...
	*/
	printf("Creating spacecraft...\n");
	//Setting up Objects:
	Player player1, player2;
	Ball ball;
	Keys keys, networkKeys;
	resetKeyboard(&keys);
	resetKeyboard(&networkKeys);
	newBall(&ball);
	newPlayer(&player1);
	newPlayer(&player2);
	printf("Start Render...\n");

	// Video loop
	double totalTime = 0;
	const double targetInterval = 1000.0 / TARGET_FRAME_RATE;
	double interval = current_time_ms();
	bool gameRunning = true;
	int counter = 0;
	printf("~60 FPS");
	int tick = 0;

	while (gameRunning) {
		// Update Times
		double elapsedMs = current_time_ms();
		float fps = 0;
		tick++;
		totalTime += targetInterval;
		const double dx = sin(totalTime / 1000) * 60;

		// Winsock client handler
		iResult = recv(ClientSocket, recvbuf, recvbuflen, 0);
		if (iResult > 0) {
			printf("Bytes received: %d\n", iResult);

			// Echo the buffer back to the sender
			iSendResult = send(ClientSocket, recvbuf, iResult, 0);

			if (iSendResult == SOCKET_ERROR) {
				printf("send failed: %d\n", WSAGetLastError());
				closesocket(ClientSocket);
				WSACleanup();
				return 1;
			}
			printf("Bytes sent: %d\n", iSendResult);
		}
		

		

		while (SDL_PollEvent(&e)) {
			// Handle incoming events
			switch (e.type) {
			case SDL_QUIT:
				gameRunning = false;
				break;
			case SDL_KEYDOWN: {
				switch (e.key.keysym.sym)
				{
				case SDLK_UP:
					keys.up = true;
					break;
				case SDLK_DOWN:
					keys.down = true;
					break;
				case SDLK_LEFT:
					keys.left = true;
					break;
				case SDLK_RIGHT:
					keys.right = true;
					break;
				default:
					break;
				}
				break;
			}
			case SDL_KEYUP: {
				switch (e.key.keysym.sym)
				{
				case SDLK_UP:
					keys.up = false;
					break;
				case SDLK_DOWN:
					keys.down = false;
					break;
				case SDLK_LEFT:
					keys.left = false;
					break;
				case SDLK_RIGHT:
					keys.right = false;
					break;
				case SDLK_SPACE:
					startMovement(&ball);
					break;
				default:
					break;
				}
				break;
			}
			}
		}
		
		is_collision(&ball, &player1, &player2);
		// Spacecraft movement:
		playerMovement(&player1, keys);
		playerMovement(&player2, networkKeys);
		ballMovement(&ball);
		//ballMovement(&ball);
		// Render Background
		SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0, 0, 0));

		// Render Spacecraft & Enemies
		renderer(&player1, &player2, &ball, screenSurface, spaceShipSurface);

		// Update window
		SDL_UpdateWindowSurface(window);

		// FPS
		if (tick == 60) {
			tick = 0;
			fps = 60 / ((elapsedMs - interval) / 1000);
			printf("\rfps: %.2f , Kicked: %d  ", fps, counter);
			interval = elapsedMs;
		}
		// Delayer: Keep 60 FPS
		elapsedMs = current_time_ms() - elapsedMs;
		const double sleepRequired = targetInterval - elapsedMs;
		if (sleepRequired > 0)
		{
			SDL_Delay(sleepRequired);
		}
	}
	SDL_DestroyWindow(window);
	SDL_Quit();
	// shutdown the send half of the connection since no more data will be sent
	iResult = shutdown(ClientSocket, SD_SEND);
	if (iResult == SOCKET_ERROR) {
		printf("shutdown failed: %d\n", WSAGetLastError());
		closesocket(ClientSocket);
		WSACleanup();
		return 1;
	}

	// cleanup
	closesocket(ClientSocket);
	WSACleanup();
	return EXIT_SUCCESS;
}