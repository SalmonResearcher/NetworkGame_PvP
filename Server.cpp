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


int Server::InitWinSock(int _ret){
    // WinSock初期化
    WSADATA wsaData;
    _ret = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (_ret != 0)
    {
        //std::cout << "Error: WSAStartup ( ErrorCode:" << ret << " )" << std::endl;
        return 1;
    }
    //std::cout << "Success: WSAStartup" << std::endl;
    return _ret;
    }

int Server::CriateListenSock(int listen) {
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
    //std::cout << "Success: socket()" << std::endl;
    // bind

    struct sockaddr_in bindAddr;	// bind用のソケットアドレス情報
    memset(&bindAddr, 0, sizeof(bindAddr));
    bindAddr.sin_family = AF_INET;
    bindAddr.sin_port = htons(SERVERPORT);
    bindAddr.sin_addr.s_addr = htonl(INADDR_ANY);

    // ソケットアドレス情報設定	※固定のポート番号設定
    if (bind(listenSock, (struct sockaddr*)&bindAddr, sizeof(bindAddr)) != 0)
    {
        // エラーコードを出力
        //std::cout << "Error: bind( ErrorCode: " << WSAGetLastError() << ")" << std::endl;
        // 終了
        return 1;
    }

    //std::cout << "Success: bind()" << std::endl;

    // リスン状態に設定	キューのサイズ:1
    if ((listenSock, 1) != 0)
    {
        // エラーコードを出力
        //std::cout << "Error: listen( ErrorCode: " << WSAGetLastError() << ")" << std::endl;
        // 終了
        return 1;
    }
    //std::cout << "Success: listen()" << std::endl;
    //std::cout << "---wait connect---" << std::endl;
}

int Server::CriateSocket(int sock, int listen) {
    struct sockaddr_in clientAddr;		// 接続要求をしてきたクライアントのソケットアドレス情報格納領域
    int addrlen = sizeof(clientAddr);	// clientAddrのサイズ

    // クライアントからのconnect()を受けて、コネクション確立済みのソケット作成

    sock = accept(listen, (struct sockaddr*)&clientAddr, &addrlen);
    if (sock < 0)
    {
        // エラーコードを出力
        //std::cout << "Error: accept( ErrorCode: " << WSAGetLastError() << ")" << std::endl;
        // 終了
        return 1;
    }
    //std::cout << "Success: accept() " << std::endl;

}

bool Recv(int sock, struct TestStruct* value)
{
    struct TestStruct recvValue;	// 受信データの格納領域...ネットワークバイトオーダー状態
    int ret;		// 成否の判定用
    // 受信
    ret = recv(sock, (char*)&recvValue, sizeof(recvValue), 0);
    // 失敗
    if (ret != sizeof(recvValue))
    {
        return false;
    }

    // 成功時の処理
    strcpy_s(value->name, sizeof(value->name), recvValue.name);	// 文字列のコピー
    value->x = ntohl(recvValue.x);								// int バイトオーダー変換
    value->y = ntohl(recvValue.y);								// int バイトオーダー変換
    value->hp = ntohl(recvValue.hp);							// int バイトオーダー変換
    return true;
}

bool Server::Send(int sock, TestStruct value)
{
    struct TestStruct sendValue;	// 送信データ ... ネットワークバイトオーダーに変換後の値を格納
    strcpy_s(sendValue.name, sizeof(sendValue.name), value.name);	// 文字列のコピー
    sendValue.x = htonl(value.position_.x);									// int バイトオーダー変換
    sendValue.y = htonl(value.y);									// int バイトオーダー変換
    sendValue.hp = htonl(value.hp);									// int バイトオーダー変換

    int ret;		// 成否の判定用
    // 送信
    ret = send(sock, (char*)&sendValue, sizeof(sendValue), 0);
    // 失敗
    if (ret != sizeof(sendValue))
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