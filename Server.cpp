//インクルードライブラリ
#include <iostream>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include "Server.h"
#include "Engine/Text.h"
#include "IPlayer.h"

#pragma comment( lib, "ws2_32.lib" )

// ポート番号
const unsigned short SERVERPORT = 8888;
// 送受信するメッセージの最大値
const unsigned int MESSAGELENGTH = 1024;


int Server::InitWinSock(){
    // WinSock初期化
    WSADATA wsaData;
    int ret = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (ret != 0)
    {
        //WSADATAセットアップ　失敗！
        return 1;
    }
    //WSADATAのセットアップ完了
    return ret;
    }

int Server::CriateListenSock() {
    // リスンソケットの作成
    int listenSock;
    listenSock = socket(AF_INET, SOCK_STREAM, 0);	// 0で自動設定
    // リスンソケット作成失敗
    if (listenSock < 0)
    {
        // エラーコードを出力
        //std::cout << "Error: socket( ErrorCode: " << WSAGetLastError() << ")" << std::endl;
        // 終了
        return 1;
    }
    //ソケットの作成完了

    struct sockaddr_in bindAddr;	// bind用のソケットアドレス情報
    memset(&bindAddr, 0, sizeof(bindAddr));
    bindAddr.sin_family = AF_INET;
    bindAddr.sin_port = htons(SERVERPORT);
    bindAddr.sin_addr.s_addr = htonl(INADDR_ANY);

    // ソケットアドレス情報設定	※固定のポート番号設定
    if (bind(listenSock, (struct sockaddr*)&bindAddr, sizeof(bindAddr)) != 0)
    {
        //バインド失敗
        // 終了
        return 1;
    }

    //バインド完了

    // リスン状態に設定	キューのサイズ:1
    if ((listenSock, 1) != 0)
    {
        // エラーコードを出力
        //std::cout << "Error: listen( ErrorCode: " << WSAGetLastError() << ")" << std::endl;
        // 終了
        return 1;
    }
    //リスンソケットOK
    //相手方の接続待ち

}

int Server::CriateSocket(int listen) {
    struct sockaddr_in clientAddr;		// 接続要求をしてきたクライアントのソケットアドレス情報格納領域
    int addrlen = sizeof(clientAddr);	// clientAddrのサイズ

    // クライアントからのconnect()を受けて、コネクション確立済みのソケット作成

    int sock = accept(listen, (struct sockaddr*)&clientAddr, &addrlen);
    if (sock < 0)
    {
        // エラーコードを出力
        //std::cout << "Error: accept( ErrorCode: " << WSAGetLastError() << ")" << std::endl;
        // 終了
        return 1;
    }
    //std::cout << "Success: accept() " << std::endl;

}

bool Recv(int sock, struct IPlayer* playerID)
{
    IPlayer recvplayerID;	// 受信データの格納領域...ネットワークバイトオーダー状態
    int ret;		// 成否の判定用
    // 受信
    ret = recv(sock, (char*)&recvplayerID, sizeof(recvplayerID), 0);
    // 失敗
    if (ret != sizeof(recvplayerID))
    {
        return false;
    }

    // 成功時の処理
    recvplayerID.comp.pos.x = ntohl(playerID->comp.pos.x);
    recvplayerID.comp.pos.y = ntohl(playerID->comp.pos.y);
    recvplayerID.comp.pos.z = ntohl(playerID->comp.pos.z);

    return true;
}

bool Server::Send(int sock, IPlayer* playerID)
{
    struct IPlayer sendplayerID;	// 送信データ ... ネットワークバイトオーダーに変換後の値を格納

    // 送信
    int ret = send(sock, (char*)&sendplayerID, sizeof(sendplayerID), 0);
    // 失敗
    if (ret != sizeof(sendplayerID))
    {
        return false;
    }

    // 成功
    return true;
}

int Server::Shutdown(int sock, int listen,int ret){
    // 送受信ともに切断
    // shutdown(sock, 0x02);
    if (shutdown(sock, SD_BOTH) != 0)
    {
        // エラーコードを出力
        //std::cout << "Error: shutdown( ErrorCode: " << WSAGetLastError() << ")" << std::endl;
    }
    //std::cout << "Success: shutdown() " << std::endl;


    // ソケットの破棄
    if (closesocket(sock) != 0)
    {
        // エラーコードを出力
        //std::cout << "Error: closesocket( ErrorCode: " << WSAGetLastError() << ")" << std::endl;
    }
    //std::cout << "Success: closesocket() " << std::endl;

    if (closesocket(listen) != 0)
    {
        // エラーコードを出力
        //std::cout << "Error: closesocket( ErrorCode: " << WSAGetLastError() << ")" << std::endl;
    }
    //std::cout << "Success: closesocket() " << std::endl;

    // WinSock終了処理
    if (WSACleanup() != 0)
    {
        //std::cout << "Error: WSACleanup ( ErrorCode:" << ret << " )" << std::endl;
    }
    //std::cout << "Success: WSACleanup" << std::endl;




    return 0;
}