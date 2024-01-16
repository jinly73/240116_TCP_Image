#define _CRT_SECURE_NO_WARNINGS
#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <iostream>
#include <WinSock2.h>

#pragma comment(lib, "ws2_32")

int main()
{
	WSAData wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	SOCKET ServerSocket = socket(PF_INET, SOCK_STREAM, 0);
	SOCKADDR_IN ServerSockAddr;
	memset(&ServerSockAddr, 0, sizeof(ServerSockAddr));
	ServerSockAddr.sin_family = AF_INET;
	ServerSockAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	ServerSockAddr.sin_port = htons(18080);

	connect(ServerSocket, (SOCKADDR*)&ServerSockAddr, sizeof(ServerSockAddr));

	FILE* OutputFile = fopen("±è¿ÁÁö.jpg", "wb");

	char Buffer[1] = { 0, };

	size_t WriteSize = 0;
	int RecvByte = 0;
	do
	{
		RecvByte = recv(ServerSocket, Buffer, sizeof(Buffer), 0);
		WriteSize = fwrite(Buffer, sizeof(char), RecvByte, OutputFile);
	} while (RecvByte > 0);

	fclose(OutputFile);
	closesocket(ServerSocket);

	WSACleanup();

	return 0;
}