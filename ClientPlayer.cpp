#include "ClientPlayer.h"
#include <iostream>
#include <WinSock2.h>
#include <WS2tcpip.h>

#pragma comment( lib, "ws2_32.lib" )

// ポート番号
const unsigned short SERVERPORT = 8888;
// 送受信するメッセージの最大値
const unsigned int MESSAGELENGTH = 1024;

int WSASetup()
{
    WSADATA wsaData;
    int ret = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (ret != 0)
    {
        std::cout << "Error: WSAStartup ( ErrorCode:" << ret << " )" << std::endl;
        return 1;
    }
    std::cout << "Success: WSAStartup" << std::endl;
    return 0;
}

int CreateSocket()
{
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0)
    {
        std::cout << "Error: socket( ErrorCode: " << WSAGetLastError() << ")" << std::endl;
        return -1;
    }
    std::cout << "Success: socket()" << std::endl;
    return sock;
}

int ConnectToServer(int sock)
{
    struct sockaddr_in serverAddr;
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(SERVERPORT);
    inet_pton(AF_INET, "127.0.0.1", &serverAddr.sin_addr.s_addr);

    if (connect(sock, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) != 0)
    {
        std::cout << "Error: connect( ErrorCode: " << WSAGetLastError() << ")" << std::endl;
        return 1;
    }
    std::cout << "Success: connect()" << std::endl;
    return 0;
}

int SetSocketNonBlocking(int sock)
{
    unsigned long cmdarg = 0x01;
    int ret = ioctlsocket(sock, FIONBIO, &cmdarg);
    if (ret == SOCKET_ERROR)
    {
        std::cout << "Error: ioctlsocket()" << std::endl;
        return 1;
    }
    std::cout << "Success: ioctlsocket()" << std::endl;
    return 0;
}

void SendMessage(int sock)
{
    char buff[MESSAGELENGTH];
    std::cout << "Input message:";
    std::cin >> buff;

    int ret = send(sock, buff, strlen(buff), 0);

    if (ret != strlen(buff))
    {
        std::cout << "Error: send( ErrorCode: " << WSAGetLastError() << ")" << std::endl;
        exit(1);
    }
}

void ReceiveMessage(int sock)
{
    char buff[MESSAGELENGTH];
    std::cout << "---wait message---" << std::endl;
    int ret = recv(sock, buff, sizeof(buff) - 1, 0);

    if (ret < 0)
    {
        if (WSAGetLastError() == WSAEWOULDBLOCK)
        {
            std::cout << "No data received" << std::endl;
        }
        else
        {
            std::cout << "Error: recv( ErrorCode: " << WSAGetLastError() << ")" << std::endl;

        }
    }
    else
    {
        buff[ret] = '\0';
        std::cout << "Receive message : " << buff << std::endl;
    }
}

void CleanUp(int sock)
{
    if (shutdown(sock, SD_BOTH) != 0)
    {
    }

    if (closesocket(sock) != 0)
    {
    }

    if (WSACleanup() != 0)
    {
    }
}