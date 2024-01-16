#define _CRT_SECURE_NO_WARNINGS
#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <iostream>
#include <WinSock2.h>

#pragma comment(lib, "ws2_32")
int main()
{
	WSAData wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	SOCKET ListenSocket = socket(PF_INET, SOCK_STREAM, 0);
	SOCKADDR_IN ListenSockAddr;
	memset(&ListenSockAddr, 0, sizeof(ListenSockAddr));
	ListenSockAddr.sin_family = AF_INET;
	ListenSockAddr.sin_addr.s_addr = INADDR_ANY;
	ListenSockAddr.sin_port = htons(18080);
	bind(ListenSocket, (SOCKADDR*)&ListenSockAddr, sizeof(ListenSockAddr));
	listen(ListenSocket, 0);

	SOCKADDR_IN ClientSockAddr;
	memset(&ClientSockAddr, 0, sizeof(ClientSockAddr));
	int ClientSockAddrLength = sizeof(ClientSockAddr);
	SOCKET ClientSocket = accept(ListenSocket, (SOCKADDR*)&ClientSockAddr, &ClientSockAddrLength);

	FILE* InputFile = fopen("TCPFighter.zip", "rb");

	char Buffer[1000000] = { 0, };
	size_t ReadSize = 0;
	int SendSize = 0;

	do // 한번만 돌게
	{
		ReadSize = fread(Buffer, sizeof(char), sizeof(Buffer), InputFile); // 한 칸짜리 Buffer크기만큼 읽어주세요
		SendSize = send(ClientSocket, Buffer, (int)ReadSize, 0);
	} while (ReadSize > 0);

	fclose(InputFile);
	closesocket(ClientSocket);
	closesocket(ListenSocket);

	return 0;
}