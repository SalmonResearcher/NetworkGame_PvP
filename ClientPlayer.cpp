#include "ClientPlayer.h"
#include <iostream>
#include <WinSock2.h>
#include <WS2tcpip.h>

#pragma comment( lib, "ws2_32.lib" )

// ポート番号
const unsigned short SERVERPORT = 8888;
// 送受信するメッセージの最大値
const unsigned int MESSAGELENGTH = 1024;

int ClientPlayer::WSASetup()
{
    WSADATA wsaData;
    int ret = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (ret != 0)
    {
        //WSAセットアップ失敗
        return 1;
    }
    return 0;
}

int ClientPlayer::CreateSocket()
{
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0)
    {
        //ソケット作成失敗
        return -1;
    }
    return sock;
}

int ClientPlayer::ConnectToServer(int sock)
{
    struct sockaddr_in serverAddr;
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(SERVERPORT);
    inet_pton(AF_INET, "127.0.0.1", &serverAddr.sin_addr.s_addr);

    if (connect(sock, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) != 0)
    {
        //接続失敗
        return 1;
    }
    return 0;
}

int ClientPlayer::SetSocketNonBlocking(int sock)
{
    unsigned long cmdarg = 0x01;
    int ret = ioctlsocket(sock, FIONBIO, &cmdarg);
    if (ret == SOCKET_ERROR)
    {
        //ノンブロッキングソケット作成失敗
        return 1;
    }
    return 0;
}

void ClientPlayer::SendStruct(int sock)
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

void ClientPlayer::ReceiveStruct(int sock)
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

void ClientPlayer::CleanUp(int sock)
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

