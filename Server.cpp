#include "Server.h"
#include "IPlayer.h"
#include "Engine/Debug.h"
#include <iostream>
#include <WinSock2.h>
#include <WS2tcpip.h>

#pragma comment( lib, "ws2_32.lib" )

// ポート番号
const unsigned short SERVERPORT = 8888;
// 送受信するメッセージの最大値
const unsigned int MESSAGELENGTH = 1024;


//1，winSock作成
int Server::InitWinSock()
{
    WSADATA wsaData;
    int ret = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (ret != 0)
    {
        Debug::Log("Error: InitWinSock ( ErrorCode:");
        Debug::Log(WSAGetLastError());
        Debug::Log(")", true);
        return 1;	// おーわり！
    }
    Debug::Log("Success: InitWinSock", true);
    return ret + playerID_;
    playerID_++;
}

//2，リスンソケット作成
int Server::UDPSock()
{
    // UDPソケットの作成
    int sock;
    if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        Debug::Log("Error: UDPSock ( ErrorCode:");
        Debug::Log(WSAGetLastError());
        Debug::Log(")", true);
        return 1;	// おーわり！
    }
    Debug::Log("Success: UDPSocket", true);
}

int Server::Bind(int sock)
{
    // 固定アドレスにするためにソケットアドレス情報の割り当て
    struct sockaddr_in bindAddr;
    memset(&bindAddr, 0, sizeof(bindAddr));
    bindAddr.sin_family = AF_INET;
    bindAddr.sin_port = htons(SERVERPORT);
    bindAddr.sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind(sock, (struct sockaddr*)&bindAddr, sizeof(bindAddr)) < 0)
    {
        Debug::Log("Error: bind ( ErrorCode:");
        Debug::Log(WSAGetLastError());
        Debug::Log(" )",true);
        return 1;
    }
    Debug::Log("Success: bind", true);
    // ソケットsockをノンブロッキングソケットにする
        unsigned long cmdarg = 0x01;
    int ret = ioctlsocket(sock, FIONBIO, &cmdarg);
    if (ret == SOCKET_ERROR)
    {
        OutputDebugString("ノンブロッキングソケット化失敗\n");
        closesocket(sock);  // ソケットを閉じる
        return false;
    }

    return true;

}

bool Server::Recv(int sock, IPlayer::SPlayerComp* value1, IPlayer::SPlayerComp* value2)
{
    IPlayer::SPlayerComp recvValue1, recvValue2;
    int ret;

    // データを1バイトずつ受信する
    char* buff1 = reinterpret_cast<char*>(&recvValue1);
    char* buff2 = reinterpret_cast<char*>(&recvValue2);

    // 1つ目のデータを受信
    for (int i = 0; i < sizeof(recvValue1); )
    {
        ret = recv(sock, &buff1[i], sizeof(recvValue1) - i, 0);

        if (ret <= 0)
        {
            Debug::Log("recv1でエラーまたは接続が閉じられました", true);
            return false;
        }

        i += ret;
    }

    // 2つ目のデータを受信
    for (int i = 0; i < sizeof(recvValue2); )
    {
        ret = recv(sock, &buff2[i], sizeof(recvValue2) - i, 0);

        if (ret <= 0)
        {
            Debug::Log("recv2でエラーまたは接続が閉じられました", true);
            return false;
        }

        i += ret;
    }

    //絶対ここじゃないぷれいやーID設定
    recvValue1.PID = 0;
    recvValue2.PID = 1;

    // 受信したデータを引数で指定された構造体にコピー
    *value1 = recvValue1;
    *value2 = recvValue2;

    return true;
}

bool Server::Send(int sock, IPlayer::SPlayerComp* value1, IPlayer::SPlayerComp* value2)
{
    int ret;

    // 1つ目のデータを送信
    ret = send(sock, reinterpret_cast<char*>(value1), sizeof(IPlayer::SPlayerComp), 0);
    if (ret != sizeof(IPlayer::SPlayerComp))
    {
        Debug::Log("Error: Send\n");
        return false;
    }

    // 2つ目のデータを送信
    ret = send(sock, reinterpret_cast<char*>(value2), sizeof(IPlayer::SPlayerComp), 0);
    if (ret != sizeof(IPlayer::SPlayerComp))
    {
        Debug::Log("Error: Send\n");
        return false;
    }

    return true;
}

