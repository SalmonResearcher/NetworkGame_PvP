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
    return ret;
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

bool Server::Recv(int sock, IPlayer::SPlayerComp* value)
{
    //IPlayer::DATA recvValue;
    IPlayer::SPlayerComp recvValue[2];	//受信データの格納領域...ネットワークバイトオーダー状態
    int ret;		//成否の判定用

    //受信
    ret = recv(sock, (char*)&recvValue, sizeof(recvValue), 0);

    //失敗
    if (ret != sizeof(recvValue))
    {
        //送られたが、データがなかった時
        if (WSAGetLastError() == WSAEWOULDBLOCK)
        {
            Debug::Log("Recv EMPTY Data!", true);
            return true;
        }
        //そもそも送られもしなかった時
        else
        {
            Debug::Log("Error : Recv!", true);
            return false;
        }
    }

    int size = sizeof(recvValue);
    char* buff = new char[size];

    //
    for()
    {
        for(int l = 0; l < size; l++)
        {
            buff[l] = ;
        }
    }

        //送られたし、データもあっていわゆる成功時の処理
        

        //value->posX = ntohl(recvValue.posX);        //バイトオーダー変換
        //value->posY = ntohl(recvValue.posY);        //バイトオーダー変換
        //value->posZ = ntohl(recvValue.posZ);        //バイトオーダー変換
        //
        //value->rotateY = ntohl(recvValue.rotateY);  //バイトオーダー変換
        //value->attack = ntohl(recvValue.attack);    //バイトオーダー変換
        return true;
}

bool Server::Send(int sock, IPlayer::DATA* value)
{
    IPlayer::DATA sendValue;

    //バイトオーダー変換
    sendValue.posX = htonl(value->posX);
    sendValue.posY = htonl(value->posY);
    sendValue.posZ = htonl(value->posZ);

    sendValue.rotateY = htonl(value->rotateY);
    sendValue.attack = htonl(value->attack);
    
    int ret;
    ret = send(sock, (char*)&sendValue, sizeof(sendValue), 0);
    if (ret != 0)
    {
        OutputDebugString("Error : Send\n");
        return false;
    }
    return 1;
}
